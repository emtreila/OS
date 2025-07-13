#!/usr/bin/bash

# Sa se scrie un script care numara cate fisiere din directorul dat ca
# prim parametru contin cel putin unul din cuvintele date ca urmatori 
# parametri. Si cu validari!

dir_name=$1
if test ! -d $dir_name; then
	echo "This isn't a directory!"
	exit 1	
fi

if test $# -le 1; then
	echo  "Not enough arguments!"
	exit 1
fi
i=1
files=`find "$dir_name" -type f`
for file in $files; do
	i=$((i+1))
	while test $i -le $#; do
		echo $i
	done 
done
