#!/usr/bin/bash

# 4) Find recursively in a given directory all the symbolic links,
# and report those that point to files/directories that no longer exist.
# Use operator -L to test if a path is a symbolic link, and operator -e
# to test if it exists (will return false if the target to which the link
#  points does not exist)

dir_name=$1
if test ! -d $dir_name; then
	echo "Oh no! This isn't a directory!"
	exit 1
fi

names=`find $dir_name`
for name in $names; do
	if test -L $name;then
		if test ! -e $name; then
			echo $name
		fi
	fi
done


