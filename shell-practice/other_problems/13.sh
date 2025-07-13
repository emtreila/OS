#!/usr/bin/bash

# 13. . Find recursively in a given directory all the symbolic links, and
#  report those that point to files/directories that no longer exist. 
#  Use option -L to test if a path is a symbolic link, and option -e to 
#  test if it exists (will return false if the target to which the link 
#  points does not exist) 


files=`find -type l $1`
for link in $files; do 
	if test ! -e $link; then
		echo "Link $link is not valid"
	fi
done
