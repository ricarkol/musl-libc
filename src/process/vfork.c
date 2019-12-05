#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include "syscall.h"

#define KML
#ifdef KML
extern unsigned long __sysinfo;

/* Can't make this pure assembly as it can't use __sysinfo from it. */
pid_t vfork(void)
{
	__asm__ __volatile__ ("popq %%rcx; call *%0; pushq %%rcx; movq %%rax,%%rdi; jmp __syscall_ret"
			:: "r"(__sysinfo), "a"(SYS_vfork) : "rcx", "r11", "memory", "rdi");
}
#else
pid_t vfork(void)
{
	/* vfork syscall cannot be made from C code */
#ifdef SYS_fork
	return syscall(SYS_fork);
#else
	return syscall(SYS_clone, SIGCHLD, 0);
#endif
}
#endif
