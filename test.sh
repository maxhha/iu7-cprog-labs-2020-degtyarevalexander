rm -f *.gcda &&
gcc99v *.c && (
    for file in $( ls in_* )
    do
        echo -e "\n$file:"
        cat $file
        cat $file |
        ./a.out
    done
) &&
gcov *.gcda
