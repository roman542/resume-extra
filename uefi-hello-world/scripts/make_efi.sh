#!/usr/bin/bash

check_pe_magic() {
	# PE/COFF
	local magic="$(< "$1" tail -c +129 | head -c 4 | base64)"
	if [[ $magic != "UEUAAA==" ]]; then
		echo "Error: Invalid magic"
		return 1
	fi
	# PE32+
	magic="$(< "$1" tail -c +153 | head -c 2 | base64)"
	if [[ $magic != "CwI=" ]]; then
		echo "Error: Invalid format"
		return 1
	fi
	return 0
}

check_pe_magic "$1"
if (($? > 0)); then
	echo Error
	exit 1;
fi

gen_patched() {
	head -c 220 "$1"
	echo -en '\x0a\x00'
	tail -c +223 "$1"
}

gen_patched "$1" > "$1.tmp"
mv "$1.tmp" "$1"


