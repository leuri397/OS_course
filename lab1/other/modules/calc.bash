#!/bin/bash
# Calculator unit. Made for doing task 2.2
if [[ "$#" -ne 3 ]]
then exit 1 # Exit with code 1 if argument count is not 3
else
if ! [[ $2 =~ ^[0-9]+$ ]] || ! [[ $3 =~ ^[0-9]+$ ]]
then exit 2
fi
case $1 in
	sum)
	echo $(($2+$3))
	exit 0
	;;
	sub)
	echo $(($2-$3))
	exit 0
	;;
	mul)
	echo $(($2*$3))
	exit 0
	;;
	div)
	([[ $3 -eq 0 ]] && exit 3 || echo $(($2/$3))) #if we try to divide by 0 then exit with code 3
	;;
	*)
	exit 2 #if we can't find matching argument (it is not sum/mul/sub/div) exit with code 2
	;;
esac
fi

