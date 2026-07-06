#!/usr/bin/bash
s=$(wine sizes.exe -s)

if [[ $s != "1 8 8 1 1 2 2 4 4 8 8 16 16 1 2 1 16 8 8 8 8 8 6 4 16 16 " ]]; then
	echo "Error: sizes mismatch"
	echo "EXP: '1 8 8 1 1 2 2 4 4 8 8 16 16 1 2 1 16 8 8 8 8 8 6 4 16 16'"
	echo "GOT: '$s'"
	exit 1
fi
