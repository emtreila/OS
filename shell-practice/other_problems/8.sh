#!/usr/bin/bash

# 8. Write a script that reads filenames until the word "stop" is 
# entered. For each filename, check if it is a text file and if it is,
# print the number of words on the first line.(Hint: test command to 
# check if regular file; file command to check if text file)

while true; do
	read -p "Enter the file name: " filename

	if test "$filename" = "stop" ; then
		echo "i stop"
		exit 1
	fi

	if test -f $filename; then
		if test "*.txt"=$filename; then
			nr=`head -n1 $filename | wc -w`
			echo "file: " $filename  " words: " $nr
		fi
	fi
done

