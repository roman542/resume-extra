#!/usr/bin/bash

# Create efi image

dd if=/dev/zero of=disk.img bs=1M count=50
echo "$(cat << EOF
label: gpt
label-id: D1DC8D9C-F2F8-4DC5-932C-294CD320C429
device: disk.img
unit: sectors
first-lba: 2048
last-lba: 102366
sector-size: 512

disk.img1 : start=        2048, size=       98304, type=C12A7328-F81F-11D2-BA4B-00A0C93EC93B, uuid=94C37169-88B1-458A-879A-8E48A8B1435E
EOF
)" | sfdisk disk.img

script=$(cat << EOF
loop=\$(losetup -f disk.img --show)
partprobe \$loop
mkfs.fat -F32 \${loop}p1

mkdir mnt
mount \${loop}p1 mnt

mkdir -p mnt/EFI/BOOT
cp $1 mnt/EFI/BOOT/

umount mnt

losetup -d \$loop
EOF
)

sudo bash -c "$script"

qemu-img dd -f raw -O qcow2 if=disk.img of=disk.qcow2

rm disk.img
