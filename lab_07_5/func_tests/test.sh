#!/bin/env bash

PROG=$1
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ ! -f $PROG ]
then
    echo "No programm file"
    exit 1
fi

if [ $DIR/pos_01_args.txt -nt $DIR/make_tests.sh ]
then
    (
        cd $DIR
        rm -f *.txt
        . ./make_tests.sh
    )
fi

DATA=$(cat $DIR/readme.md | grep -E "(тесты)|(- [0-9]+? -)")

prefix=""
IFS=$'\n'
for line in $DATA
do
    if [ ! -z $(echo $line | grep "тесты") ]
    then
        echo -e "\n\033[0;33m##\n${line}\n##\033[0m"
        if [ ! -z $(echo $line | grep "Поз") ]
        then
            prefix="pos"
        else
            prefix="neg"
        fi
    else
        num=$(echo $line | sed -Ee "s/- ([0-9]+?) - .*/\1/g")

        in_file="$DIR/${prefix}_${num}_in.txt"
        args_file="$DIR/${prefix}_${num}_args.txt"
        out_file="$DIR/${prefix}_${num}_out.txt"

        if [[ -f $args_file ]]
        then
            cat $args_file | xargs $PROG
            rc=$?

            if cmp -s $out_file .result &&
                [[ $rc = 0 && "pos" == $prefix || "neg" == $prefix ]]
            then
                echo -e "\033[0;32m[ ok ] ${line}\033[0m"
            else
                echo -e "\033[0;31m[erro] ${line}\033[0m"
                echo
                echo Return code: $rc
                diff -u $out_file .result
                echo
            fi

            rm -f .result

        else
            echo -e "\033[0;37m[skip] ${line}\033[0m"
        fi
    fi
done
