EFICC ?= x86_64-w64-mingw32-gcc

all: sizes.exe
	./check.sh

sizes.exe: sizes.c ../include/uefi_types.h
	$(EFICC) sizes.c -O2 -o sizes.exe -I ../include

.PHONY: all clean

clean:
	-rm sizes.exe


