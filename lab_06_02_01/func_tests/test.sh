PROG=$1

if [ ! -f $PROG ]
then
    echo "No program path"
    exit
fi

DATA=$(cat readme.md | grep -E "(тесты)|(- [0-9]+? -)")

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
        args_file="${prefix}_${num}_args.txt"
        out_file="${prefix}_${num}_out.txt"

        if [[ -f $args_file ]]
        then
            cat $args_file | xargs $PROG > .result

            if ( cmp -s $out_file .result )
            then
                echo -e "\033[0;32m[ ok ] ${line}\033[0m"
            else
                echo -e "\033[0;31m[erro] ${line}\033[0m"
                echo
                diff -u $out_file .result
                echo
            fi

            rm -f .result

        else
            echo -e "\033[0;37m[skip] ${line}\033[0m"
        fi
    fi
done
