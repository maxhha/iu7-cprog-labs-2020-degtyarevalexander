## Позитивные тесты
#- 01 - матрицы из 1-го элемента
cat > pos_01_in.txt <<EOF
1 1
1

1 1
3

1 1
EOF
cat > pos_01_out.txt <<EOF
3
EOF

#- 02 - удаление наибольшего элемента
cat > pos_02_in.txt <<EOF
1 2
2 1

1 1
5 1

1 1
EOF
cat > pos_02_out.txt <<EOF
5
EOF

#- 03 - удаление наибольшего при обходе по столбцам
cat > pos_03_in.txt <<EOF
2 4
0 2 0 2
1 0 1 0

2 2
1 0
0 1

1 1
EOF
cat > pos_03_out.txt <<EOF
0 0
1 1
EOF

#- 04 - удаление наибольшего при обходе по столбцам
cat > pos_04_in.txt <<EOF
2 4
0 2 0 2
1 0 1 0

2 2
1 0
0 1

1 1
EOF
cat > pos_04_out.txt <<EOF
0 0
1 1
EOF

#- 05 - добавление строк и столбцов
cat > pos_05_in.txt <<EOF
2 4
0 4 3 4
1 0 1 0

3 3
1 0 0
0 1 0
0 0 1

1 1
EOF
cat > pos_05_out.txt <<EOF
0 3 0
1 1 1
0 2 0
EOF

#- 06 - возведение в 0 степень
cat > pos_06_in.txt <<EOF
2 4
0 4 3 4
1 0 1 0

3 3
1 0 0
0 1 0
0 0 1

0 1
EOF
cat > pos_06_out.txt <<EOF
1 0 0
0 1 0
0 0 1
EOF

#- 07 - возведение в 2 степень
cat > pos_07_in.txt <<EOF
3 3
1 2 3
1 0 -1
3 2 1

3 3
1 0 0
0 1 0
0 0 1

2 1
EOF
cat > pos_07_out.txt <<EOF
12 8 4
-2 0 2
8 8 8
EOF

## Негативные тесты
#- 01 - отрицательный размер матрицы
cat > neg_01_in.txt <<EOF
-1 9
EOF

#- 02 - буква в размере матрицы
cat > neg_02_in.txt <<EOF
1a 9
EOF

#- 03 - буква в элементе
cat > neg_03_in.txt <<EOF
2 1
1a 1
EOF

#- 04 - отрицательная степень
cat > neg_04_in.txt <<EOF
1 1
1

1 1
1

-1 9
EOF

#- 05 - буква в степени
cat > neg_05_in.txt <<EOF
1 1
1

1 1
1

1а 9
EOF

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
