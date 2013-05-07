#!/bin/sh

for file in `ls *.c | sed -e 's/\.c$//'`
do
	for opt in "-O0" "-O" "-O3"
	do
		for cc in "gcc" "llvm-gcc"
		do
			rm -f ${file}${opt}-${cc}
			rm -f ${file}${opt}-${cc}.time
			rm -f ${file}${opt}-${cc}.s
		done
	done
done

