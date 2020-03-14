#!/bin/bash
echo >>making executable;
make all | grep !"";
echo >>lets begin...;

touch outtemp

for inputFile in "testV+E"/*
do
    echo Testes: $inputFile
    for i in {0..10};do 
    ./p1Exe <$inputFile | grep "ms" >outtemp; 
    sed 's/ms//' outtemp
    done
done;

make clean | grep !"";
rm outtemp
echo "All Done!";