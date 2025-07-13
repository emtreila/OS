#!/usr/bin/bash

#2. Write a bash script that counts all the lines of code in the C files
#  from the directory given as command-line argument, excluding lines
#  that are empty or contain only spaces.

dir_name=$1

if test -z $1; then
	echo "No directory given!"
	exit 1
fi

if test ! -d $dir_name; then
	echo "This is not a directory!"
	exit 1
fi
total=0
c_files=`find $dir_name -name "*.c"`
for file in $c_files; do
	nr_lines=`cat $file| grep -E -c -v "^[[:space:]]*$"`
	echo $file "-" $nr_lines "lines"
	total=$((total+nr_lines))
done

echo "Total lines: " $total

