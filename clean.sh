#!/usr/bin/env bash
for i in $(ls); do
	if [ -d "$i" ]; then
		echo "$i";
		(cd "$i"; make clean)
	fi
done
