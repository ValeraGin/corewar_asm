#!/bin/zsh
# Author ValeraGin (aka hmathew)

PATH_TESTS=./tests/asm

find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.cor" -delete
find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.my_cor" -delete
find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.s_my" -delete
find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.hex" -delete

for f in $(find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.s"  ) ; do
	echo ""
	echo "--------       $f "
	./asm $f

	if [ -f "${f%.*}.cor" ]; then
		mv "${f%.*}.cor" "${f%.*}.my_cor"
		./asm "${f%.*}.my_cor"
	fi

	./orig_asm $f


	if [ -f "${f%.*}.cor" ]; then

		./asm "${f%.*}.cor"
		./asm "${f%.*}.diasm.s"

		xxd "${f%.*}.diasm.cor" > "${f%.*}.diasm.cor.hex"
		xxd "${f%.*}.cor" > "${f%.*}.cor.hex"
		diff "${f%.*}.diasm.cor.hex" "${f%.*}.cor.hex"

		if [ $? -eq 0 ]; then
			echo "\e[32m[FILES OUTPUTS IDENT]\e[39m file "${f%.*}.my_cor.hex" and "${f%.*}.cor.hex" identically"
		else
			echo "\e[91m[FILES OUTPUTS NOOOOOO IDENT]\e[39m file "${f%.*}.my_cor.hex" and "${f%.*}.cor.hex" not identically"
		fi
	fi
	echo ""
done


# for f in $(find $PATH_TESTS -mindepth 0 -maxdepth 5 -type f -name "*.diasm.cor"  ) ; do
# 	echo ""
# 	echo "--------       $f "

# 	xxd $f > "${f%.*}.hex"

# 	xxd "${f%.*}.cor" > "${f%.*}.cor.hex"

# 	valgrind ./asm $f
# done

