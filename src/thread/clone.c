#define _GNU_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include "pthread_impl.h"

#include <sched.h>

extern unsigned long __sysinfo;

/* This is like the regular __syscall5, except that it includes
setting the return IP on rcx for the child to know where to return to. */
long syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret = -1;
        register long r10 __asm__("r10") = a4;
        register long r8 __asm__("r8") = a5;
        __asm__ __volatile__ ("popq %%rcx; call *%1; pushq %%rcx" : "=a"(ret) : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2),
                              "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
        return ret;
}

int __clone(int (*func)(void *), void *stack, int flags, void *arg, ...)
{
        va_list ap;
        pid_t *ptid, *ctid;
        void  *tls;
	long s = ((unsigned long)stack & -16L)-8UL;
	int pid;

        va_start(ap, arg);
        ptid = va_arg(ap, pid_t *);
        tls  = va_arg(ap, void *);
        ctid = va_arg(ap, pid_t *);
        va_end(ap);

	pid = syscall5(SYS_clone, flags, s, ptid, ctid, tls);
	if (pid == 0) {
		func(stack);
		__syscall1(SYS_exit, 0);
	}
	return pid;
}
