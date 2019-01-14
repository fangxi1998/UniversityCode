#!/bin/bash
echo "please input the password."
read pas
while [ $pas != 123 ]
do
	echo 'try again!'
	read pas
done
echo 'yes'
exit 0
