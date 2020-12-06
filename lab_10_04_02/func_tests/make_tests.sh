## Позитивные тесты
#- 01 - перевод числа в список
cat > pos_01_in.txt <<EOF
out
123432
EOF
cat > pos_01_out.txt <<EOF
139 1 37 1 3 1 2 3 1
EOF

#- 02 - перевод 1 в список
cat > pos_02_in.txt <<EOF
out
1
EOF
cat > pos_02_out.txt <<EOF
1
EOF

#- 03 - умножение 2-х чисел
cat > pos_03_in.txt <<EOF
mul
4216
846
EOF
cat > pos_03_out.txt <<EOF
47 1 31 1 17 1 3 2 2 4 1
EOF

#- 04 - умножение на 1
cat > pos_04_in.txt <<EOF
mul
4216
1
EOF
cat > pos_04_out.txt <<EOF
31 1 17 1 2 3 1 1
EOF

#- 05 - квадрат
cat > pos_05_in.txt <<EOF
sqr
18
EOF
cat > pos_05_out.txt <<EOF
3 4 2 2 1
EOF

#- 06 - деление на число с общими простыми
cat > pos_06_in.txt <<EOF
div
4216
62
EOF
cat > pos_06_out.txt <<EOF
17 1 2 2 1
EOF

#- 07 - деление на число с разными простыми
cat > pos_07_in.txt <<EOF
div
4216
42
EOF
cat > pos_07_out.txt <<EOF
5 2 2 2 1
EOF

#- 08 - деление на большее число;
cat > pos_08_in.txt <<EOF
div
42
46
EOF
cat > pos_08_out.txt <<EOF
(NO OUT, ERROR)
EOF

#- 09 - деление результат 1;
cat > pos_09_in.txt <<EOF
div
32
32
EOF
cat > pos_09_out.txt <<EOF
1
EOF

## Негативные тесты
#- 01 - перевод отрицательного числа
cat > neg_01_in.txt <<EOF
out
-103
EOF
echo > neg_01_out.txt

#- 02 - умножение на 0
cat > neg_02_in.txt <<EOF
mul
10
0
EOF
echo > neg_02_out.txt

#- 03 - квадрат отрицательного
cat > neg_03_in.txt <<EOF
sqr
-1
EOF
echo > neg_03_out.txt

#- 04 - деление на 0
cat > neg_04_in.txt <<EOF
div
10
0
EOF
echo > neg_04_out.txt

#- 05 - неправильная операция
cat > neg_05_in.txt <<EOF
ss
EOF
echo > neg_05_out.txt

# Добавить список тестов в readme
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

DATA=$( cat $DIR/readme.md | sed -zE "s/## Позитивные тесты.*//g" )
echo "$DATA" > $DIR/readme.md

DATA=$(
    cat ${BASH_SOURCE[0]} |
    grep -e "^#[#-]" |
    sed -e "s/##/\n##/g" |
    sed -ze "s/^\n//g" |
    sed -e "s/^#-/-/g" )

echo -e "\n$DATA" >> $DIR/readme.md
