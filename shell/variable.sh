#!/bin/bash
myvar="Hello World!"
echo $myvar
echo "$myvar"
echo '$myvar'
echo \$myvar
echo "Enter some test"
read myvar
echo '$myvar' now equals $myvar
