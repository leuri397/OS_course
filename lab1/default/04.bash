#!/bin/bash
if [[ $PWD == *"$HOME"* ]]
then
echo $HOME
exit 0
else
exit 1
fi
