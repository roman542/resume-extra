#include <asm/unistd.h>

void sys3(long num, long arg1, long arg2, long arg3) {
	long ret1, ret2;
	asm volatile ("syscall"
	: "=a"(ret1), "=b"(ret2)
      	: "a" (num),
	  "D" (arg1),
	  "S" (arg2),
	  "d" (arg3)
        : "memory");
}

void main() {
	sys3(__NR_write, 1, (long)"hello world from main.c!\n", sizeof("hello world from main.c!\n") - 1);
	sys3(__NR_exit, 0, 0, 0);
}
