#!/bin/bash

read -p "Enter the file path: " FILE

if [ -f "$FILE" ]
  then
    echo "$FILE is a file"
elif [ -d "$FILE" ]
  then
    echo "$FILE is a directory"
    N=$(ls $FILE/*.txt | wc -l)
    echo $N
fi

