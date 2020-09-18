#!/bin/bash
if [[ -e "/var/log/anaconda/X.log" ]]
	then
	warnings="$(cat /var/log/anaconda/X.log | awk '{if(($3 == "(WW)") && ($1 == "["))print $0}')"
	information="$(cat /var/log/anaconda/X.log | awk '{if(($3 == "(II)") && ($1 == "[")) print $0}')"
	echo -e "${warnings//"(WW)"/"\e[33mWarning:\e[0m"}"
	echo -e "${information//"(II)"/"\e[94mInformation:\e[0m"}"
	else exit 5
fi
