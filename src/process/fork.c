#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "syscall.h"
#include "libc.h"
#include "pthread_impl.h"

#define KML
#ifdef KML
extern unsigned long __sysinfo;
#endif

static void dummy(int x)
{
}

weak_alias(dummy, __fork_handler);

#if 0
__attribute__ ((noinline)) long __vfork()
{
	unsigned long ret = -1;
        __asm__ __volatile__ ("popq %%rdx; call *%1; pushq %%rdx" : "=a"(ret) : "r"(__sysinfo), "a"(SYS_vfork) : "rcx", "r11", "memory");
        return ret;
}

/*
 * This does not work, we need the return PC to be in rdx. Basically, we need the exact same code
 * as in src/process/x86_64/vfork.s
 */
pid_t vfork(void)
{
	pid_t ret = __vfork();
	return __syscall_ret(ret);
}
#endif

pid_t vfork(void)
{
	__asm__ __volatile__ ("popq %%rdx; call *%0; pushq %%rdx" :: "r"(__sysinfo), "a"(SYS_vfork) : "rcx", "r11", "memory", "rdx");
}

pid_t fork(void)
{
	pid_t ret;
	sigset_t set;
	__fork_handler(-1);
	__block_all_sigs(&set);
#ifdef SYS_fork
	ret = __syscall(SYS_fork);
#else
	ret = __syscall(SYS_clone, SIGCHLD, 0);
#endif
	if (!ret) {
		pthread_t self = __pthread_self();
		self->tid = __syscall(SYS_gettid);
		self->robust_list.off = 0;
		self->robust_list.pending = 0;
		self->next = self->prev = self;
		__thread_list_lock = 0;
		libc.threads_minus_1 = 0;
	}
	__restore_sigs(&set);
	__fork_handler(!ret);
	return __syscall_ret(ret);
}
