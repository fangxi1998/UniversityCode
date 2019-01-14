#!/bin/bash
let flag=1;
for((i=2;i<=100;i++))
do
	let flag=1
	for((j=2;j<i;j++))
	do
		if ((i%j==0))
		then 
			flag=0
			break
		fi
	done
	if ((flag==1))
	then 
		echo -n " $i"
	fi

done
