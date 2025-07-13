#!/usr/bin/bash

# 3) Find recursively in a directory, all the files with the extension
#   ".log" and sort their lines (replace the original file with the 
#   sorted content).

dir_name=$1
if test ! -d $dir_name; then
	echo "This isn't a directory!"
	exit 1
fi

log_files=`find $dir_name -name "*.log"`

for file in $log_files; do
	cat $file | sort -o $file
done

