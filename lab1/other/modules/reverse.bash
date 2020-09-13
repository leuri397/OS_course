#!/bin/bash
if [[ $# -eq 2 ]]
	then
	if [[ -e $1 ]]
		then
		echo "$(tac $1 | rev)" >> $2
		else exit 5
		fi
	else exit 1
	fi
