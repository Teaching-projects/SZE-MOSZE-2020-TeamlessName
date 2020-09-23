#!/bin/bash

FILE=output.txt

if test -f $FILE
then
	rm $FILE
fi

for u1 in units/* 
do
	for u2 in units/*
	do
		if [ $u1 != $u2 ]
		then
			./a.out $u1 $u2 >> $FILE
		fi
	done
done
