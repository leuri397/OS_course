#!/bin/bash
emails=$(grep -rohIE "[[:alnum:]]+\@[[:alnum:]]+\.[[:alnum:]]+" /etc/* | tr "\n" ", ")
echo $emails > lab1/default/email.lst
