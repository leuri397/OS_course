#!/bin/bash
echo "$(awk -F: '{print $3 ": " $1}' /etc/passwd | sort -nk 1)"
