#!/bin/bash

#Checks if there are 2 elements after the executable
if [ ! $# -eq 2 ];then
	echo "Wrong format!"
	echo "Correct form: ./runTests.sh inputFolder outputFolder"
	exit 1
fi

#Inputs
inputdir=$1
outputdir=$2

#Scrpit
if [ ! -d "tecnicofs-*" ]; then
	make all | grep !""
fi

mkdir -p $2


for inputFile in "$inputdir"/*
do
	echo "InputFile = ​${inputFile/"$inputdir/"/""}"
	auxFile=${inputFile/"$inputdir"/$outputdir}
	auxFile=${auxFile%.*}
	outFile="$auxFile.out"
	./p1Exe <$inputFile >$outFile
	diff $outFile ${outFile/"$outputdir"/"outputTests/"}
done

#make clean | grep !""
exit 0
