#!/bin/bash

# Write a  bash script that receives as command line arguments names of 
# either files or directories
# - if the argument is a regular file then display the first 10 lines from it
# - if the arg is a directory, create a file with the same name as the directory + ".info"
# inside the directory and put the output of the ls -l command for that directory in it
# - if it is neither a file nor a directory, display a message

while test $# -ge 1; do
	if test -f $1; then
		echo "regular file"
		#sed -n '1,10p' $1
		#head -n 10 $1
		awk 'NR < 11 {print $0}' $1
	elif test -d $1; then
		echo "directory"
		#d_name=basename ceva
		d_name=`echo "$1" | awk -F/ '{print $NF}'`
		#d_name=$(echo "$1" | awk -F/ '{print $NF}')
		f_name="${1}/$d_name.info"
		ls -l $1 > ${f_name}
	else
		echo "The argument $1 is neither a regular file nor a directory"

	fi
	shift
done
