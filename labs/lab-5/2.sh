#!/bin/bash

# Write a bash script that receives as command line arguments pairs of 
# arguments A and B. For each pair, if argument A contains argument B,
# display them

#!!!!!!!!!!!!!!!!!!!!!!!!!!!
# (for test) [] = need to have white spaces after the open [ and before ]
# = whitespaces between = will crash 


while test $# -ge 2; do
	a=$1
	b=$2
	if echo "$a" | grep -E -q "$b"; then
		echo "String $b is found in string $a"
	fi
	shift 2
done

if test $# -gt 0; then
	echo "Incomplete pair: $1 - $2"
fi

