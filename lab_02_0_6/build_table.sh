#!/bin/bash
header=1
rm -f table.md
for R in 10 100 1000 10000; do
    for N in 10 100 1000 10000; do
        echo "$header $R $N" |
        python3 generate_test.py |
        sed "s/[^ 0-9]/ /g" |
        ./a.out |
        grep -v -E "Enter|Show" >> table.md
        header=0
    done
done
