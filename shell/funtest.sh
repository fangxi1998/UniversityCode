#!/bin/bash
fun(){

echo " the first paramter is $1"
echo " the second paramter is $2"
return 0

}
echo "ready call"
fun 12 34
if [ $? = 0 ]
then 
	echo "execute success"
fi
echo "call end"
exit 0 

