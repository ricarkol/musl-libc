#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#define TESTKML
#undef KML
#ifdef TESTKML
/* #include <stdio.h> */
/* #include <string.h> */
extern unsigned long __sysinfo;
typedef long (*syscall0_t)(void);
typedef long (*syscall1_t)(long a1);    
typedef long (*syscall2_t)(long a1, long a2);
typedef long (*syscall3_t)(long a1, long a2, long a3);
typedef long (*syscall4_t)(long a1, long a2, long a3, long a4);
typedef long (*syscall5_t)(long a1, long a2, long a3, long a4, long a5);
typedef long (*syscall6_t)(long a1, long a2, long a3, long a4, long a5, long a6);
/* static __inline long djw_debug(long i, long n) */
/* { */
/*     char msg[20]; */
/*     unsigned long ret; */
/*     long a0 = 1; */
/*     long a1 = 1; */
/*     long a2 = (long)msg; */
/*     long a3 = 20; */
/*     memset(msg, 0, 20); */
/*     sprintf(msg, "syscall%d %d\n", i, n); */
/*     __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(a0), "D"(a1), "S"(a2), */
/* 						  "d"(a3) : "rcx", "r11", "memory"); */
    
/*     return ret; */
/* } */
#endif


static __inline long __syscall0(long n)
{
	unsigned long ret;

    /* syscall0_t *syscall_table0 = (syscall0_t *)__sysinfo; */
    /* return syscall_table0[n](); */

    if (__sysinfo) {
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n) : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }

    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;

    /* if (!__sysinfo) { */
    /*     __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory"); */
    /*     return ret; */
    /* } */
    /* syscall1_t *syscall_table1 = (syscall1_t *)__sysinfo; */
    /* printf("sysinfo is at 0x%lx\n", __sysinfo); */
    /* printf("syscall_table1 is at 0x%lx\n", syscall_table1); */
    /* printf("calling 0x%p\n", syscall_table1[n]); */
    /* return syscall_table1[n](a1); */

    if (__sysinfo) {
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1) : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }
    
    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;

    /* if (__sysinfo) */
    /*     return ((syscall2_t *)__sysinfo)[n](a1, a2); */

    if (__sysinfo) {
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2)
                              : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }

    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
                          : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;

    /* if (__sysinfo) */
    /*     return ((syscall3_t *)__sysinfo)[n](a1, a2, a3); */

    if (__sysinfo) {
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2),
                              "d"(a3) : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }

    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;

    /* if (__sysinfo) */
    /*     return ((syscall4_t *)__sysinfo)[n](a1, a2, a3, a4); */

    if (__sysinfo) {
        register long r10 __asm__("r10") = a4;
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2),
                              "d"(a3), "r"(r10): "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }
    
    register long r10 __asm__("r10") = a4;
    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;

    /* if (__sysinfo) */
    /*     return ((syscall5_t *)__sysinfo)[n](a1, a2, a3, a4, a5); */

    if (__sysinfo) {
        register long r10 __asm__("r10") = a4;
        register long r8 __asm__("r8") = a5;
        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2),
                              "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }

    register long r10 __asm__("r10") = a4;
    register long r8 __asm__("r8") = a5;
    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");

	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;

    /* if (__sysinfo) */
    /*     return ((syscall6_t *)__sysinfo)[n](a1, a2, a3, a4, a5, a6); */

    if (__sysinfo) {
        register long r10 __asm__("r10") = a4;
        register long r8 __asm__("r8") = a5;
        register long r9 __asm__("r9") = a6;

        __asm__ __volatile__ ("call *%0" : : "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2),
                              "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
        __asm__ __volatile__ ("movq %%rax, %0" : "=r" (ret));
        return ret;
    }

    register long r10 __asm__("r10") = a4;
    register long r8 __asm__("r8") = a5;
    register long r9 __asm__("r9") = a6;
    __asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");

	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"

#define IPC_64 0
