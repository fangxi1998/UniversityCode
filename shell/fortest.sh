#!/bin/bash
for a in x1 x2 20
do
	echo $a
done


for file in $(ls *.sh)
do
	echo $file
done

exit 0

