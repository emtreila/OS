#!/usr/bin/bash

# 6. Write a bash script that sorts the file given as command line 
# arguments in ascending order according to their file size in bytes.


if test $# -eq 0; then
	echo "No arguments!"
	exit 1
fi

for file in $*; do
	if test -f $file ; then
		du $file
	fi
done | sort -n
