#!/usr/bin/bash

# 7. Write a bash script that calculates the sum of the sizes (in bytes)
# of all regular files in a folder given as a parameter.(use test to
# check if the folder exists and if a given file is a regular file)

if test $# -eq 0; then
	echo "no files given"
	exit 1
fi

if test ! -e $1; then
	echo "this is not a folder!"
	exit 1
fi

all_files=`find`
total=0
for file in $all_files; do
	if test -f $file; then
		b=`du -b $file | cut -f1`
		total=$((total+$b))
	fi
done

echo "total bytes: " $total
