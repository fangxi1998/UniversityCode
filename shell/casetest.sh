#!/bin/bash
echo "Is now morning?"
read timeofday
case "$timeofday" in
	yes) echo "good morning";;
	y|s) echo "answer error";;
	no)  echo "good bye";;
	*)   echo "good bye";;
esac
exit 0
