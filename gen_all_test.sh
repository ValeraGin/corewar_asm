#!/bin/zsh
# Author ValeraGin (aka hmathew)

find ./test/ -type f -name "*.cor" -delete
find ./test/ -type f -name "*.my_cor" -delete
find ./test/ -type f -name "*.s_my" -delete
find ./test/ -type f -name "*.hex" -delete

# for f in ./test/*.s; do
# 	echo "-----------------------------------"
# 	echo "Processing file by MY asm - $f"
# 	# take action on each file. $f store current file name
# 	./asm $f
# 	echo "-----------------------------------"
# 	echo ""
# done

# for f in ./test/*.cor; do
# 	mv "$f" "${f%.*}.my_cor"
# done

# for f in ./test/*.s; do
# 	echo "-----------------------------------"
# 	echo "Processing file by ORIG asm - $f"
# 	# take action on each file. $f store current file name
# 	./orig_asm $f
# 	echo "-----------------------------------"
# 	echo ""
# done

# for f in ./test/*.cor; do
# 	echo "-----------------------------------"
# 	echo "Processing diff - $f"
# 	# take action on each file. $f store current file name
# 	xxd $f > $f.hex
# 	xxd "${f%.*}.my_cor" > "${f%.*}.my_cor.hex"

# 	diff $f.hex "${f%.*}.my_cor.hex"

# 	if [ $? -eq 0 ]
# 	then
# 		echo "\e[32m[Success]\e[39m file $f and ${f%.*} identically"
# 	else
# 		echo "\e[91[Failure]\e[39m file $f and ${f%.*} identically"
# 	fi

# 	echo "-----------------------------------"
# 	echo ""
# done

# for f in ./test/*.cor; do
# 	echo "-----------------------------------"
# 	echo "Processing diasm - $f"
# 	# take action on each file. $f store current file name
# 	./asm $f
# 	echo "-----------------------------------"
# 	echo ""
# done