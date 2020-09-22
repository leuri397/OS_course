#!/bin/bash
if [[ $# -eq 2 ]]
	then
	if [[ -e $1 ]]
		then
		if >> "$2"
			then
			result=$(tac $1) 2> /dev/null
			echo "$result" | rev> $2
			if [[ $? -eq 0 ]]
				then
				exit 0
				else
				exit 6
			fi
			else
			exit 7
		fi
		else exit 5
	fi
	else exit 1
fi
