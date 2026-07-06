EFI_CC ?= x86_64-w64-mingw32-gcc
EMPTY :=
EFI_CFLAGS ?= $(EMPTY) -fshort-wchar -mno-red-zone
EFI_LDFLAGS ?= -nostdlib -static -lgcc -e efi_main

all: disk.qcow2

disk.qcow2: bootx64.efi
	./scripts/mkimg.sh bootx64.efi

bootx64.efi: hello_world.c
	$(EFI_CC) $(EFI_CFLAGS) $(EFI_LDFLAGS) -I include hello_world.c -o bootx64.efi
	./scripts/make_efi.sh bootx64.efi

check: conf_tests;:

conf_tests:
	cd sys_tests; make

clean: sys_tests_clean
	-rm bootx64.efi disk.qcow2
	-if [ -d mnt ]; then sudo rm -rf mnt; fi

sys_tests_clean:
	cd sys_tests; make clean

.PHONY: all clean sys_tests_clean check conf_tests


