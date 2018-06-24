#!/bin/bash 
filepath="/home/sysinfo/ylzplan"
filename=`ls $filepath/temp/ | sort -r | sed -n '1p'`
cat $filepath/temp/$filename | sed -n '/userName/p' | awk 'BEGIN{FS="userName="} {print $2}' | awk 'BEGIN{FS="&userPass="} {print $1,$2}' | awk 'BEGIN{FS="&x="} {print $1}' > $filepath/.tmp
sort -u $filepath/.tmp >> $filepath/test.txt
rm $filepath/.tmp
