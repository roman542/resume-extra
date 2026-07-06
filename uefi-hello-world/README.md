This hello world does not switch framebuffer to text mode, thus if you run it in graphics mode set prior to loading this program nothing will be displayed on older EFIs.

The latest at the time of writing this code UEFI spec doesn't have a single mention of mode switching, which makes me think it should happen automatically, but doesn't on somewhat older efis.

To change screen into text mode, you can try booting via boot select screen, uefi shell, or refind bootloader.

Dependencies:

1. mingw-w64
2. qemu-system-x86_64 (to run)

Build qemu image:

    make

Building the qemu image requires root.

Build efi file only:

    make bootx64.efi

Check some things:

    make conf_tests   
