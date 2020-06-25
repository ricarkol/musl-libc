#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#define CONFIG_NOMMU

#ifdef CONFIG_NOMMU
extern unsigned long __sysinfo;
#endif

static __inline long __syscall0(long n)
{
	unsigned long ret = -1;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret = -1;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret = -1;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
			: "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret = -1;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2), "d"(a3)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
			"d"(a3) : "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret = -1;
	register long r10 __asm__("r10") = a4;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
			"d"(a3), "r"(r10): "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret = -1;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
			"d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
#endif
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret = -1;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;
#ifdef CONFIG_NOMMU
	if (__sysinfo)
		__asm__ __volatile__ ("call *%1" : "=a"(ret)
			: "r"(__sysinfo), "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "r"(r9)
			: "rcx", "r11", "memory");
#else
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
			"d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
#endif
	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"

#define IPC_64 0
