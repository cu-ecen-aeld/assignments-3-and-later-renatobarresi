#!/bin/sh

filesdir=$1 
searchstr=$2
numOfMatchingLines=0 #Store the ocurranses of the word
numOfFiles=0

# validate inputs 
if [ -z "$filesdir" ] || [ -z "$searchstr" ]; then 
    echo "You have to specify both parameters" 
    exit 1
fi

# validate the directory
eval ls $filesdir &> /dev/null
if [ $? != 0 ]; then
	echo "This is not a directory"
	exit 1
fi

# parse the directory
#dirPath=$(dirname $filesdir)

numOfFiles=$(ls $filesdir -1 | wc -l)
fileArray=$(ls $filesdir -1)

# count the number of lines
cd $filesdir
for t in $fileArray; do
   val=$(grep -c $searchstr $t)
   numOfMatchingLines=$(( $val + $numOfMatchingLines ))
done
echo "The number of files are $numOfFiles and the number of matching lines are $numOfMatchingLines" 
