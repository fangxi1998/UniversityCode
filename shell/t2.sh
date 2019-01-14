#!/bin/bash
echo "input word 1"
read wordone
echo "input word 2"
read wordtwo
if [ $wordone = $wordtwo ]
then
	echo "Match"
fi
echo "End of program"
exit 0
