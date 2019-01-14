#!/bin/bash
for file in $(ls)
do
	if test -s $file 
	then 
		echo -n  '.'
	
        else
		echo "$file 大小为0 停止程序"
		break
	fi
done
exit 0
