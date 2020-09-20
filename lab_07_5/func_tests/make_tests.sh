## Позитивные тесты
#- 01 - сортированный массив
cat > pos_01_args.txt <<EOF
func_tests/pos_01_in.txt .result
EOF
cat > pos_01_in.txt <<EOF
0
1
2
3
EOF
cat > pos_01_out.txt <<EOF
0
1
2
3
EOF

#- 02 - сортированный в обратном порядке массив
cat > pos_02_args.txt <<EOF
func_tests/pos_02_in.txt .result
EOF
cat > pos_02_in.txt <<EOF
3
2
1
0
EOF
cat > pos_02_out.txt <<EOF
0
1
2
3
EOF

#- 03 - массив с отриц значениями
cat > pos_03_args.txt <<EOF
func_tests/pos_03_in.txt .result
EOF
cat > pos_03_in.txt <<EOF
-3
-2
-1
0
EOF
cat > pos_03_out.txt <<EOF
-3
-2
-1
0
EOF


#- 04 - случайный массив
cat > pos_04_args.txt <<EOF
func_tests/pos_04_in.txt .result
EOF
cat > pos_04_in.txt <<EOF
231
43
1
9
7
-4
-78
7324
2
EOF
cat > pos_04_out.txt <<EOF
-78
-4
1
2
7
9
43
231
7324
EOF

#- 05 - фильтрация массива
cat > pos_05_args.txt <<EOF
func_tests/pos_05_in.txt .result f
EOF
cat > pos_05_in.txt <<EOF
1
100
100
20
7
3
2
1
EOF
cat > pos_05_out.txt <<EOF
2
7
20
100
EOF


#- 06 - сортировка большого массива
cat > pos_06_args.txt <<EOF
func_tests/pos_06_in.txt .result f
EOF
python3 > pos_06_in.txt <<EOF
import random
for i in range(10000):
    print(random.randint(0, 100))
EOF
cat pos_06_in.txt | sort > pos_06_out.txt

## Негативные тесты
#- 01 - недостаточно аргументов
cat > neg_01_args.txt <<EOF
func_tests/neg_01_in.txt
EOF

#- 02 - файл не существует
cat > neg_02_args.txt <<EOF
func_tests/neg_02_in.txt .result
EOF

#- 03 - файл пустой
cat > neg_03_args.txt <<EOF
func_tests/neg_03_in.txt .result
EOF
echo > neg_03_in.txt

#- 04 - файл c буквой в числе
cat > neg_04_args.txt <<EOF
func_tests/neg_04_in.txt .result
EOF
cat > neg_04_in.txt <<EOF
1
2
3
5a
EOF

#- 05 - файл c буквой в числе
cat > neg_05_args.txt <<EOF
func_tests/neg_05_in.txt .result
EOF
cat > neg_05_in.txt <<EOF
1
2
3
5a
6
EOF

#- 06 - неправильный третий аргумент
cat > neg_06_args.txt <<EOF
func_tests/neg_06_in.txt .result err
EOF
cat > neg_06_in.txt <<EOF
1
2
3
5
EOF

#- 07 - отфильтрованы все элементы
cat > neg_07_args.txt <<EOF
func_tests/neg_07_in.txt .result f
EOF
cat > neg_07_in.txt <<EOF
3
2
1
1
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
