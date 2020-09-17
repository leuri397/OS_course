#!/bin/bash
#Search module, implements task 2.3
if [[ $# -eq 2 ]]
then
	if [ -d "$2" ]
	then
		result="$(grep -r "$1" "$2")"
		if [[ $? -ne 0 ]]
		then exit 6 #in case of error of other programm return 6
		else echo "$result"
		exit 0
		fi
	else exit 5
	fi
else exit 1
fi
exit 0
#checking if dir exists and if its exists search in it, else return 1
