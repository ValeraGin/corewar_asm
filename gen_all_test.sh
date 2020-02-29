#!/bin/zsh
# Author ValeraGin (aka hmathew)

find ./test/ -type f -name "*.cor" -delete
find ./test/ -type f -name "*.my_cor" -delete

for f in ./test/*.s; do
	echo "-----------------------------------"
	echo "Processing file by MY asm - $f"
	# take action on each file. $f store current file name
	./asm $f
	echo "-----------------------------------"
	echo ""
done

for f in ./test/*.cor; do
	mv "$f" "${f%.*}.my_cor"
done

for f in ./test/*.s; do
	echo "-----------------------------------"
	echo "Processing file by ORIG asm - $f"
	# take action on each file. $f store current file name
	./orig_asm $f
	echo "-----------------------------------"
	echo ""
done

for f in ./test/*.cor; do
	echo "-----------------------------------"
	echo "Processing diff - $f"
	# take action on each file. $f store current file name
	diff $f "${f%.*}.my_cor"

	if [ $? -eq 0 ]
	then
		echo "\e[32m[Success]\e[39m file $f and ${f%.*} identically"
	else
		echo "\e[91[Failure]\e[39m file $f and ${f%.*} identically"
	fi

	echo "-----------------------------------"
	echo ""
done


