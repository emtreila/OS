#!/usr/bin/bash

# 4.  Write a bash script that receives any number of command line 
#  arguments and prints on the screen, for each argument, if it is a 
#  file, a directory, a number or something else.

if test $# -eq 0; then
	echo "No arguments given!"
	exit 1
fi

for arg in $*; do
	if test -d  $arg; then
		echo $arg " = is a directory "
	elif test -f $arg; then
		echo $arg " = is a file "
	elif echo $arg | grep -E -q "^[0-9]+&"; then
		echo $arg " = is a number "
	else
		echo $arg " = something else "
	fi
done
