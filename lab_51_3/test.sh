function echocmd () {
	local cmd="$*"
	echo -e "\u001b[38;5;245m$ $cmd \u001b[0m"
	eval $cmd
	return $?
}
echocmd gcc --std=c99 -Wall -Werror -Wfloat-equal -Wfloat-conversion -Wpedantic -O0 --coverage *.c && (
    echocmd ./a.out
    echocmd ./a.out c
    echocmd ./a.out c 1
    echocmd ./a.out c f _f.bin
    echocmd ./a.out c 1 _f.bin
	echocmd ./a.out c 10 _f.bin
	rm -f _f.bin

	echocmd ./a.out p
	echocmd ./a.out p _f.bin
	echocmd ./a.out c 10 _f.bin
	echocmd ./a.out p _f.bin
	rm -f _f.bin

	echocmd ./a.out s
	echocmd ./a.out s _f.bin
	echocmd ./a.out c 10 _f.bin
	echocmd ./a.out p _f.bin
	echocmd ./a.out s _f.bin
	echocmd ./a.out p _f.bin
	rm -f _f.bin
	echo > _f.bin
	echocmd ./a.out s _f.bin
	echo "1" > _f.bin
	echocmd ./a.out s _f.bin
	rm -f _f.bin

	echo
	echocmd ./a.out h
	echo
    gcov *.gcda
)
