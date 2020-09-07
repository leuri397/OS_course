#!/bin/bash
info_messages="$(cat /var/log/anaconda/X.log | awk '$3 = "(II)"{print $0}')"
warning_messages="$(cat /var/log/anaconda/X.log | awk '$3 = "(WW)"{print $0}')"
echo "${warning_messages//"(WW)"/"Warning: "}" > lab1/default/info.log
echo "${info_messages//"(II)"/"Information: "}" >> lab1/default/info.log
