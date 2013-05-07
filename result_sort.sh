#!/bin/sh

for file in `ls *.c | sed -e 's/\.c$//'`
do
	for opt in "-O0" "-O" "-O3"
	do
		for cc in "gcc" "llvm-gcc"
		do
			target_name="${file}${opt}-${cc}"
			num=`grep user ${target_name}.time | wc -l`
			result=`grep user ${target_name}.time | sed -e 's/user.*//' | awk 'BEGIN{OFMT="%.6f";total=0;}{total += $1}END{print total / '$num';}'`
			all="$all\n$result ${target_name}"
		done
	done
done
echo $all | sort -n
