#!/bin/bash

FILEPATH="$(dirname -- "$(realpath "$0")")"

function help {
HELPPATH="$FILEPATH"
if [[ "$#" -eq 0 ]]
then echo "$(cat $HELPPATH/help)"
else echo "$(cat $HELPPATH/modules/$1_help)"
fi
}

function module_call { # Calling module [MODULE_NAME] [MODULE_ARGS (0-3)]
MODULESPATH="$FILEPATH/modules/"
result="$($MODULESPATH$1.bash "$2" $3 $4 $5 $6)"
return_code=$?
if [[ $return_code -eq 0 ]]
then
	echo "$result"
	exit 0
else
	case $return_code in
	1) echo "Wrong amount of arguments" >&2
	;;
	2) echo "Wrong meaning of arguments" >&2
	;;
	3) echo "Imposiible operation" >&2
	;;
	4) echo "Unknown argument" >&2
	;;
	5) echo "Directory or file does not exists" >&2
	;;
	6) echo "Internal comand error" >&2
	;;
	esac
	echo "$(help $1)"
	exit 1
fi
}

function interactive_start {
possible_actions=("${existing_module_list[@]}"  "help" "exit" )
while :
do
echo "Choose one of the options below by typing its number or name:"
index="0"
	for module in ${possible_actions[@]}
	do
	echo "$index. $module"
	index=$(($index + 1))
	done
read option
if [[ $option =~ ^[0-9]+$ ]]
then
	if [[ $option -lt ${#possible_actions[@]} ]] && [[ $option -ge 0 ]]
	then module=${possible_actions[$option]}
	else echo "Invalid option. Try again"
	continue
	fi
else
	if [[ ${possible_actions[@]} =~ ("$option") ]]
	then module="$option"
	else echo "Unknown option. Try again"
	continue
	fi
fi
no_arg=( "log" "exit" "help")
if ! [[ ${no_arg[@]} =~ ("$module") ]]
then echo "Enter arguments"
read arg1 arg2 arg3 arg4
fi
case $module in
"exit")
	exit 0
	;;
help)
	help
	;;
calc|search|reverse|log)
	echo "$(module_call $module $arg1 $arg2 $arg3 $arg4)"
	continue
	;;
esac
done
}

if ! [[ -e "$FILEPATH/modules_list" ]]
then echo "Missing list of modules. Program is terminating">&2
exit -1
else
	for module in $(cat $FILEPATH/modules_list)
	do
		if [[ -e "$FILEPATH/modules/$module.bash" ]]
		then
		existing_module_list+=( "$module" )
		else
		missing_module_list+=( "$module" )
		fi
	done
fi
if ! [[ -z "$missing_module_list" ]]
then echo "There are some missing modules: ${missing_module_list[@]}">&2
fi

if [[ $# -eq 0 ]]
then
	help
	exit -2
fi
case $1 in
calc|search|reverse|strlen|log)
	if [[ $# == 1 ]] && [[ $1 != "log" ]]
	then help $1 
	exit -2
	fi
	if [[ ${existing_module_list[@]} =~ ($1) ]]
	then result="$(module_call $1 "$2" $3 $4 $5 $6)"
		if [[ $? -eq 0 ]]
		then echo "$result"
		else exit -2
		fi
	else echo "Attempt to call non-existing module">&2
	exit -2
	fi
	;;
"exit")
	([[ $# -eq 1 ]] && exit 0 || ([[ $2 -eq "X" ]] && help "exit" || exit 0))
	;;
help)
	help
	exit 0
	;;
interactive)
	interactive_start
	exit $?
	;;
esac
