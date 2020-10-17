gcc99m && (
    for i in 01 02 03 04 05 06 07 08 09 10 11 12;
    do
        cat test$i.txt | ./a.out
    done
)
