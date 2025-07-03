#!/bin/bash

#Write a bash script that receives as command-line arguments pairs
# consisting of a directory name D (or path) and a number N.
# Calculate the size in bytes of the contents of directory D (du), 
#and print a warning message if that size is greater than 90% of N but 
#less than N, and a different warning message if that size is greater 
#than N. If the argument that is supposed to be a directory is not, 
#in fact, a directory, skip that pair and print a corresponding message.

while test $# -ge 2; do
	if !test -d $1; then
		echo "The argument $1 is not a directory"
	else
		size=0
		size='ls -l $1 | awk 'BEGIN{storage=0} {storage+=$5} END {print size}'`

		

