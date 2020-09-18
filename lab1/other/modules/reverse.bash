#!/bin/bash
if [[ $# -eq 2 ]]
	then
	if [[ -e $1 ]]
		then
		tac $1 | rev 1> $2 2> /dev/null
		if [[ $? -eq 0 ]]
		then
		exit 0
		else
		exit 6
		fi
		else exit 5
		fi
	else exit 1
	fi
