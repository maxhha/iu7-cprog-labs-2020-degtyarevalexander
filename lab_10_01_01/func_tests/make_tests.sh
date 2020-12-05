## Позитивные тесты
#- 01 - поиск записей
cat > pos_01_args.txt <<EOF
func_tests/pos_01_in.txt .result f
EOF
cat > pos_01_in.txt <<EOF
2020-12-31;200;table
2020-12-31;300;door
2020-12-31;100;cat
EOF
cat > pos_01_out.txt <<EOF
2020-12-31;300;door
EOF

#- 02 - поиск записей. равная сумма
cat > pos_02_args.txt <<EOF
func_tests/pos_02_in.txt .result f
EOF
cat > pos_02_in.txt <<EOF
2020-12-31;100;table
2020-12-31;300;cat
2020-12-31;100;mushroom
EOF
cat > pos_02_out.txt <<EOF
2020-12-31;300;cat
EOF

#- 03 - поиск записей. несколько ответов
cat > pos_03_args.txt <<EOF
func_tests/pos_03_in.txt .result f
EOF
cat > pos_03_in.txt <<EOF
2020-12-31;100;table
2020-12-31;300;bag
2020-12-31;200;rose
EOF
cat > pos_03_out.txt <<EOF
2020-12-31;300;bag
2020-12-31;200;rose
EOF

#- 04 - взять первый элемент
cat > pos_04_args.txt <<EOF
func_tests/pos_04_in.txt .result 1
EOF
cat > pos_04_in.txt <<EOF
2020-12-31;100;table
2020-12-31;300;bag
2020-12-31;200;rose
EOF
cat > pos_04_out.txt <<EOF
2020-12-31;100;table
EOF

#- 05 - взять первый элемент
cat > pos_05_args.txt <<EOF
func_tests/pos_05_in.txt .result 1
EOF
cat > pos_05_in.txt <<EOF
2020-12-31;100;table
EOF
cat > pos_05_out.txt <<EOF
2020-12-31;100;table
EOF

#- 06 - записать список в обратном порядке
cat > pos_06_args.txt <<EOF
func_tests/pos_06_in.txt .result r
EOF
cat > pos_06_in.txt <<EOF
2020-12-31;100;table
2020-12-31;300;bag
2020-12-31;200;rose
EOF
cat > pos_06_out.txt <<EOF
2020-12-31;200;rose
2020-12-31;300;bag
2020-12-31;100;table
EOF

#- 07 - сортировать по дате
cat > pos_07_args.txt <<EOF
func_tests/pos_07_in.txt .result d
EOF
cat > pos_07_in.txt <<EOF
2021-07-31;100;table
2020-12-31;300;bag
2020-12-01;200;rose
EOF
cat > pos_07_out.txt <<EOF
2020-12-01;200;rose
2020-12-31;300;bag
2021-07-31;100;table
EOF

## Негативные тесты
#- 01 - неправильное количество аргументов
cat > neg_01_args.txt <<EOF
func_tests/neg_01_in.txt
EOF
cat > neg_01_in.txt <<EOF
1
2
3
EOF
echo > neg_01_out.txt

#- 02 - несуществующий файл
cat > neg_02_args.txt <<EOF
func_tests/neg_02_in.txt .result f
EOF
echo > neg_02_out.txt

#- 03 - неправильная операция
cat > neg_03_args.txt <<EOF
func_tests/neg_03_in.txt .result o
EOF
cat > neg_03_in.txt <<EOF
1
2
3
EOF
echo > neg_03_out.txt

#- 04 - пустой файл
cat > neg_04_args.txt <<EOF
func_tests/neg_04_in.txt .result f
EOF
printf "" > neg_04_in.txt
echo > neg_04_out.txt

#- 05 - не полная запись
cat > neg_05_args.txt <<EOF
func_tests/neg_05_in.txt .result f
EOF
cat > neg_05_in.txt <<EOF
bla bla bla
EOF
echo > neg_05_out.txt

#- 06 - пустое поле суммы
cat > neg_06_args.txt <<EOF
func_tests/neg_06_in.txt .result f
EOF
cat > neg_06_in.txt <<EOF
2020-12-31;;bla bla bla
EOF
echo > neg_06_out.txt

#- 07 - поиск записей. нет найденных
cat > neg_07_args.txt <<EOF
func_tests/neg_07_in.txt .result f
EOF
cat > neg_07_in.txt <<EOF
2020-12-31;300;table
2020-12-31;100;bag
2020-12-31;200;rose
EOF
echo > neg_07_out.txt

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
