#!/bin/bash 
datafile=`date "+%Y%m%d_%H-%M-%S"`
datafile=$datafile".txt"
filepath="/home/sysinfo/ylzplan"
filename=`ls $filepath/temp/ | sort -r | sed -n '1p'`
cat $filepath/temp/$filename | sed -n '/userPass/p'  | awk 'BEGIN{FS="userName="} {print $2}' | awk 'BEGIN{FS="&userPass="} {print $1,$2}'  | awk 'BEGIN{FS="&x="} {print $1}'      > $filepath/.tmp
cat $filepath/temp/$filename | sed -n '/DDDDD=/p'    | awk 'BEGIN{FS="DDDDD="} {print $2}'    | awk 'BEGIN{FS="&upass="} {print $1,$2}'     | awk 'BEGIN{FS="&0MKKey="} {print $1}' >> $filepath/.tmp
cat $filepath/temp/$filename | sed -n '/username=/p' | awk 'BEGIN{FS="username="} {print $2}' | awk 'BEGIN{FS="&password="} {print $1,$2}'  | awk 'BEGIN{FS="&lt="} {print $1}'     >> $filepath/.tmp

sort -u $filepath/.tmp > $filepath/$datafile 
rm $filepath/.tmp
