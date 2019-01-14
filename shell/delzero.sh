#!/bin/bash
if [ $# -ne 1 ];then
	echo '请输入一个参数'
	exit 0
fi
dir=$1
for file in $(ls $dir)
do
	f=$dir/$file
	set $(du -b $f)
	if [ $1 = 0 ];then 
		echo "delete $f"
		rm $f
	fi

done
exit 0 
