#!/bin/bash

FILE1=Genoutput1.txt
FILE2=Genoutput2.txt

if test -f $FILE1
then
	rm $FILE1
fi

if test -f $FILE2
then
	rm $FILE2
fi

./a.out ./units/scenario1.json >> $FILE1
./a.out ./units/scenario2.json >> $FILE2