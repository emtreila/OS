#!/usr/bin/bash

# 2) Find recursively in a directory all ".c" files having more than
#   500 lines. Stop after finding 2 such files. 

dir_name=$1

if test ! -d $dir_name; then
	echo "This isn't a directory!"
	exit 1
fi

c_files=`find $dir_name -name "*.c"`
i=1
for file in $c_files; do
	if test $(cat $file | wc -l) -gt 500; then
		if test $i -le 2; then
			i=$(($i+1))
			echo $file
		else
			exit 0
		fi
	fi
done


