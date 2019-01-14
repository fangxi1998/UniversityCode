#!/bin/bash
echo "menu"
echo "a:date"
echo "b:user"
echo "c:working directory"
echo "d:content"
echo "enter a,b,c,d"
read in
echo 
case "$in" in
	a) date;;
	b) who;;
	c) pwd;;
	d) ls;;
	*) echo "ERROR"
esac

