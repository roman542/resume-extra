

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
