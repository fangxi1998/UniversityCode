#!/bin/bash
let count=0;
for file in $(ls)
do
	echo $file
	((count++))

done
echo "总文件数量为:$count"
exit 0 
