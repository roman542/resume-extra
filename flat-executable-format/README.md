# Flat executable format

Runs on linux x64.

Running: `make`.

This will build and run the sample programs.

## Executor

[main.c](./main.c): The executor, mmaps a file provided and calls it.

[bin.ld]('./bin.ld'): linker script that produces the executable in the required format.

[crt.s]('./crt.s'): C runtime; must precede all other objects, a simple jmp to main.

## Assembly sample

[hello/main.S](./hello/main.S): a hello world written in asm.

## C sample

[hello2/main.c](./hello2/main.c): a hello world written in C.

## GCC build flags

1. `-fPIE`: make executable position-independent.
2. `-static-pie`: do not use PLT (we don't have a dynamic linker to populate it).
3. `-nostdlib`: don't link standard libraries (disables libgcc as well).
4. `-lgcc`: link libgcc (static library).
