#!/usr/bin/bash

# 1) Write a bash script that counts all the C files from a given 
#  directory and all of its subdirectories.

dir_name=$1

if test ! -d $dir_name; then
	echo "This is not a directory!"
	exit 1
fi

files=`find $dir_name -type f -name "*.c" | wc -l `
echo $files
