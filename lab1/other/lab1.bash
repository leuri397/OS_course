#!/bin/bash
function help {
FILEPATH="$(dirname -- "$(realpath "$0")")"
if [[ "$#" -eq 0 ]]
then echo "$(cat $FILEPATH/help)"
else echo "$(cat $FILEPATH/modules/$1_help)"
fi
}

help
help calc

