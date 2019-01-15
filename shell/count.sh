#!/bin/bash
let count=0;
for((i=1;i<=50;i++))
do
	if ((i%7==0))
	then 
		((count=count+i))
		echo $i
	fi
done
echo $count
exit 0
