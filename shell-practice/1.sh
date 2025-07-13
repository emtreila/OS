#!/usr/bin/bash

#  1) Display a report showing the full name of all the users currently 
# connected, and the number of processes belonging to each of them.

users=`cat who.fake| cut -d" " -f1`
echo $users

for user in $users; do
	#name=`cat passwd.fake| grep -E "^$user"| cut -d: -f5`
	p=`cat ps.fake| grep -E -c "^$user"`
	echo "$user - $p processes"
done
