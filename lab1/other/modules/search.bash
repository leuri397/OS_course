#!/bin/bash
#Search module, implements task 2.3
if [[ $# -eq 2 ]]
then
	if [ -d "$2" ]
	then
		grep -r "$1" "$2" 2> /dev/null 1>&1
	else exit 5
	fi
else exit 1
fi
exit 0
#checking if dir exists and if its exists search in it, else return 1
