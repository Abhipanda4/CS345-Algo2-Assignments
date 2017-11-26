#!/bin/bash

for i in {10..500..10}
do
	echo "Running for n = "$i
	echo $i > inp_file
	j=`echo "2*"$i | bc -l`
	for (( x=1; x<=j; x++ ))
	do
		shuf -i 1-10000 -n `expr 2\*$n`>> inp_file
	done
	./linear < inp_file >> linear.log
	./brute < inp_file >> brute.log
	if cmp -s "linear.log" "brute.log"
	then
		continue
	else
		exit 0
	fi
done
