#!/usr/bin/bash

# 11.  Write a script that extracts from all the C source files given as
#  command line arguments the included libraries and saves them in a file.
output="FILE11"
:>"$output"
touch "FILE11"
for arg in $@; do
	if [[ -f "$arg" && "$arg" == *.c ]] ; then
		grep "^#include[[:space:]]*<.*>$" $arg >> "$output"
	fi
done
