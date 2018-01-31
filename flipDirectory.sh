#!/bin/bash
FILES=input/*
for f in $FILES
do
  echo "Processing $f file..."
  filename="${f##*/}"
  echo $filename
  ./divideImage $f "output/$filename"
  
done