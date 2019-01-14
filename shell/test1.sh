#!/bin/bash
if [ $# != 1 ]
then
	echo "请输入一个参数"
	exit 0
fi
dir=$1

for file in $(ls $dir)
do
	f=$dir/$file
	
	if [ -f $f ]
	then 
		echo " $file is file"

	elif [ -d $f ]
	then 
		echo "$file is directory"
	fi
done
exit 0
