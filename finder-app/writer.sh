#!/bin/bash
writefile=$1
writestr=$2

if [ ! "$#" -eq  2  ]
then
	exit 1
elif [  "$#" -eq 1 ]
then
	echo "Missing one of arguments"
fi
writefile1="${writefile%/*}"
#echo $writefile1
mkdir -p $writefile1
echo "$writestr" > "$writefile"

if [ ! "$?" ]
then 
	echo "File cannot be created"
	exit 1
fi