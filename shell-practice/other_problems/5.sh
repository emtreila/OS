#!/usr/bin/bash

# 5. Write a bash script that keeps reading strings from the keyboard 
# until the name of a readable regular file is given.

file_name=""
read -p "Enter a file name: " file_name
while test ! -f "$file_name"; do
	read -p "Enter another file name: " file_name
done

