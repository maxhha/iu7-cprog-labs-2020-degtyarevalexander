function echocmd () {
	local cmd="$*"
	echo -e "\u001b[38;5;245m$ $cmd \u001b[0m"
	eval $cmd
	return $?
}
echocmd gcc --std=c99 -Wall -Werror -g -pg -lm main.c &&
echocmd '
    echo "100000" |
    python3 generate_test.py |
    sed "s/[^ 0-9]/ /g" |
    ./a.out > /dev/null
' &&
echocmd "gprof a.out gmon.out > report.txt"
