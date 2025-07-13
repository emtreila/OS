#!/usr/bin/bash

# 5) Write a script that receives dangerous program names as command
#  line arguments. The script will monitor all the processes in the system,
#  and whenever a program known to be dangerous is run, the script will
#  kill it and display a message.

if test $# -eq 0;then
	echo "No names given!"	
	exit 1
fi
processes=`cat ps.fake | awk 'NR > 1 {printf "%s ", $2; for (i=8; i<=NF; i++) printf "%s ", $i; print ""}'
for name in $*; do
	match=`echo $processes | grep $name`
	if test -n $match; then
		pid=cut -d" " -f1
		kill -9 $pid
		echo "Killed the dangerous program!"
	fi
done
