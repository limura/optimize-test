#!/bin/sh

for file in `ls *.c | sed -e 's/\.c$//'`
do
	for opt in "-O0" "-O" "-O3"
	do
		for cc in "gcc" "llvm-gcc"
		do
			$cc $file.c -o ${file}${opt}-${cc} $opt -lm
		done
	done
done

