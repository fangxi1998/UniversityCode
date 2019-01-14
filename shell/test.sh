#!/bin/bash

let count=0;
for file in $(ls)
do
	
	if [ -s $file ]
	then
	    let count=count+1
        
	fi
done
echo "$count"
exit 0
