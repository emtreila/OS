#!/usr/bin/bash

# 14. Write a bash script that receives a folder name as an argument. 
# Find recursively in the folder the number of times each file name is 
# repeated.

find "$1" -type f | awk -F/ '{printf $NF} | sort | unique -c
