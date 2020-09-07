#!/bin/bash
# This is the task number I in lab 01

if [ "$1" -gt "$2" ] && [ "$1" -gt "$3" ]
then echo "$1"
else	if [ "$2" -gt "$1" ] && [ "$2" -gt "$3" ]
	then echo "$2"
	else echo "$3"
	fi
fi
exit 0

