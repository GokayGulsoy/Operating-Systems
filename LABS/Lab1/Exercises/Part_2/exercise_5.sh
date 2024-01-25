#!/bin/bash

FILES=$(ls *.txt)
echo $FILES
for FILE in $FILES
  do
    echo "Rename $FILE to new$FILE"
    mv $FILE "new_"$FILE
  done

