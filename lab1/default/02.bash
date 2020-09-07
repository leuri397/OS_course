#!/bin/bash

read written_line
while [[ "$written_line" != "q" ]]
do result="$result$written_line"
read written_line 
done

echo $result
exit 0
