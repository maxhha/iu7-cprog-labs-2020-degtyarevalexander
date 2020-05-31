function echocmd () {
	local cmd="$*"
	echo -e "\u001b[38;5;245m$ $cmd \u001b[0m"
	eval $cmd
	return $?
}

echocmd gcc --std=c99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic -D_XOPEN_SOURCE=500 -O0 --coverage main.c parse.c setget.c create.c sort.c find.c utils.c delete.c && (
    echocmd ./a.out
    echocmd ./a.out 1

	echocmd ./a.out cb

	for f in a in_0.txt in_1.txt in_2.txt in_3.txt; do
		echocmd cat $f
	    echocmd "./a.out cb .tmp < $f"
	    echocmd rm -f .tmp
		echo
	done

	echocmd ./a.out st

	for f in a in_0.txt in_1.txt in_2.txt in_3.txt in_4.txt in_5.txt; do
		echocmd cat $f
		echocmd "./a.out st $f"
		echo
	done

	echocmd ./a.out sb

	for f in a in_0 in_1 in_2 in_3 in_4 in_5; do
		echocmd cat $f.txt
		echocmd cp $f.bin .tmp
		echocmd "./a.out sb .tmp"
		echocmd rm -f .tmp
		echo
	done

	echocmd ./a.out ft
	echocmd ./a.out ft 0.txt
	echocmd ./a.out ft 0.txt .tmp

	for f in a in_0.txt in_1.txt in_2.txt in_3.txt in_4.txt in_5.txt; do
		echocmd cat $f
		echocmd "./a.out ft $f .tmp Aa"
		echocmd cat .tmp
		echocmd rm -f .tmp
		echo
	done

	echocmd ./a.out fb
	echocmd ./a.out fb 0.bin
	echocmd ./a.out fb 0.bin .tmp

	for f in a in_0 in_1 in_2 in_3 in_4 in_5; do
		echocmd cat $f.txt
		echocmd "./a.out fb $f.bin .tmp Aa"
		echocmd rm -f .tmp
		echo
	done

	echocmd ./a.out dt

	for f in a in_0.txt in_1.txt in_2.txt in_3.txt in_4.txt in_5.txt; do
		echocmd cat $f
		echocmd cp $f .tmp
		echocmd "./a.out dt .tmp"
		echocmd cat .tmp
		echocmd rm -f .tmp
		echo
	done

	echocmd ./a.out db

	for f in a in_0 in_1 in_2 in_3 in_4 in_5; do
		echocmd cat $f.txt
		echocmd cp $f.bin .tmp
		echocmd "./a.out db .tmp"
		echocmd rm -f .tmp
		echo
	done

    echocmd gcov *.gcda
    echocmd rm -f *.gcda *.gcno
)
