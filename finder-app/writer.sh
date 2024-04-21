#!/bin/sh

filepath=$1
stringToWrite=$2

# validate inputs 
if [ -z "$filepath" ] || [ -z "$stringToWrite" ]; then 
    echo "No parameters specified" 
    exit 1
fi

# get the path and filename
dirPath=$(dirname $filepath)
fileName=$(basename $filepath)

# validate the directory
eval ls $dirPath &> /dev/null

# if directory doesn't exist, create the directory
if [ $? != 0 ]; then
    echo "The directory: $dirPath doesn't exist, creating it"
    dirPath=${filepath//"$fileName"/}
    mkdir -p $dirPath  
fi

cd $dirPath
touch $fileName
echo $stringToWrite > $fileName

exit 0
