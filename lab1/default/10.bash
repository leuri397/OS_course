#!/bin/bash
echo "$(man bash | tr -s " " | tr ' ' '\n' | grep -E '...+'| awk '{print tolower($0)}' | sort -i | uniq -ic | sort -rnk 1 | head -n 3 | awk '{print $2}')"

