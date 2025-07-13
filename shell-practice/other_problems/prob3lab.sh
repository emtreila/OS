#!/usr/bin/bash

# Write a bash script that receives as command-line arguments filenames 
# (or paths to files). The script will print the size in bytes and the 
# filename for each argument, sorted in descending order by size and 
# removing duplicate entries. If any of the arguments are not regular 
# files, the script will ignore them. Consider that duplicates must be
#  exact matches by name and size (e.g. file and ./file are different)

for arg in $*; do
	if test -f $arg; then
		size=`du -b $arg | cut -f1`
		echo "size: " $size " , file: " $arg 
	fi
done | sort -r | uniq
