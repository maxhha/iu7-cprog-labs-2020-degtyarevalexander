#!/bin/env bash

PROG=$1
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ ! -f $PROG ]
then
    echo "No programm file"
    exit 1
fi

if [ $DIR/make_tests.sh -nt $DIR/pos_01_in.txt ]
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

        if [[ -f $in_file ]]
        then
            cat $in_file | $PROG 2> .log 1> .result
            rc=$?

            [[ "pos" = $prefix ]] && [[ $rc = 0 ]] && cmp -s $out_file .result
            pass_pos=$?
            [[ "neg" = $prefix ]] && [[ ! $rc = 0 ]]
            pass_neg=$?

            if [ $pass_pos = 0 ] || [ $pass_neg = 0 ]
            then
                echo -e "\033[0;32m[ ok ] ${line}\033[0m"
            else
                cat .log
                echo -e "\033[0;31m[erro] ${line}\033[0m"
                echo
                echo Return code: $rc
                diff -u --color=always $(realpath --relative-to="." $out_file)  .result
                echo
            fi

            rm -f .result
            rm -f .log

        else
            echo -e "\033[0;37m[skip] ${line}\033[0m"
        fi
    fi
done
