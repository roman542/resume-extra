.intel_syntax noprefix

.section .rodata
msg:
	.ascii "hello world from main.S!\n"
.set msglen, . - msg

.section .text
.global _start

_start:
mov edi, 1
lea rsi, [rip + msg]
mov edx, msglen
mov eax, 1 # write
syscall
mov edi, 0
mov eax, 60 # exit
syscall
hlt
