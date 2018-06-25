#!/bin/bash
datafile=`date "+%Y%m%d_%H-%M-%S"`
datafile=$datafile".tmp"
tcpdump -i $1 -v host 219.217.20.123 or host 172.16.6.3 or host 202.198.192.45 and tcp[32:2]=0x504f > /home/sysinfo/ylzplan/temp/$datafile
