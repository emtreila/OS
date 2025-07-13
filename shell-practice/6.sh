#!/usr/bin/bash

# 6) Find recursively in a directory, all the files that have write
# permissions for everyone. Display their names, and the permissions 
# before and after removing the write permission for everybody. 
# You will need to use chmod's symbolic permissions mode, instead of the 
# octal mode we have used in class. The the chmod manual for details.

dir_name=$1
if test ! -d $dir_name; then
	echo "This is not a directory!"
	exit 1
fi

file_names=`find $dir_name`
for name in $file_names; do
	permissions=`ls -l $name | awk '{print $1}'| grep ........w.`
	for p in $permissions; do
		echo $p " " $name
		chmod g-w $name
		new=`ls -l $name | awk '{print $1}'`
		echo $new " " $name
	done

done
