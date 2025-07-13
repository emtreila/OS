#!/usr/bin/bash

# 10. Write a bash script that sorts all files given as command 
# line arguments descending by size.

for arg in $@; do
	if test -f $arg; then
		size=$(du -b $arg | cut -f1)
		echo "$size with file $arg"
	fi
done | sort -nr
