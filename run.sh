#!/bin/sh

loop_count=100000
try_num=5

for file in `ls *.c | sed -e 's/\.c$//'`
do
	for opt in "-O0" "-O" "-O3"
	do
		for cc in "gcc" "llvm-gcc"
		do
			for n in `seq 1 1 $try_num`
			do
				time ./${file}${opt}-${cc} $loop_count 2>> ${file}${opt}-${cc}.time
			done
		done
	done
done

