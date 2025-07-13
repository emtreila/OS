#!/usr/bin/bash

# 9. Write a script that receives as command line arguments pairs 
# consisting of a filename and a word. For each pair, check if the given 
# word appears at least 3 times in the file and print a corresponding 
# message.

FILE=$1
WORD=$2

COUNT=`grep -c "$WORD" $FILE`
if test $COUNT -lt 3; then
	echo "not enough times"
else
	echo "ok!"
fi
