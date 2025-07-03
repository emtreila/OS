#!/bin/bash

echo "arg count: $#"
echo "all arguments: $@"

for a in $#; do
	echo "For arg: $a"
done

echo "before cmd args: $@"
shift
echo "after cmd args: $@"

while test $# -ge 1; do
	i=$((i+1))
	echo "Arg nr $i: $1"
	shift
done
