#!/bin/bash

cat /var/log/anaconda/syslog | awk '$2 = "INFO"' > lab1/default/info.log
