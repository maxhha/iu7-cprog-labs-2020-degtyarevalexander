## Позитивные тесты
#- 01 - одна запись
cat > pos_01_args.txt <<EOF
func_tests/pos_01_in.txt title
EOF
cat > pos_01_in.txt <<EOF
first film
some name
2009
EOF
cat > pos_01_out.txt <<EOF
first film
some name
2009
EOF

#- 02 - две записи
cat > pos_02_args.txt <<EOF
func_tests/pos_02_in.txt title
EOF
cat > pos_02_in.txt <<EOF
first film
some name
2009
second film
some name
1999
EOF
cat > pos_02_out.txt <<EOF
first film
some name
2009
second film
some name
1999
EOF

#- 03 - сортировка 2-х записией по году
cat > pos_03_args.txt <<EOF
func_tests/pos_03_in.txt year
EOF
cat > pos_03_in.txt <<EOF
first film
some name
2009
second film
some name 2
1999
EOF
cat > pos_03_out.txt <<EOF
second film
some name 2
1999
first film
some name
2009
EOF

#- 04 - сортировка 3-х записией по имени режиссёра
cat > pos_04_args.txt <<EOF
func_tests/pos_04_in.txt name
EOF
cat > pos_04_in.txt <<EOF
first film
some name
2009
second film
some name 2
1999
second film 2
Jhon Union
2005
EOF
cat > pos_04_out.txt <<EOF
second film 2
Jhon Union
2005
first film
some name
2009
second film
some name 2
1999
EOF

#- 05 - сортировка 3-х записией по имени режиссёра
cat > pos_05_args.txt <<EOF
func_tests/pos_05_in.txt name
EOF
cat > pos_05_in.txt <<EOF
first film
some name
2009
second film
some name 2
1999
second film 2
Jhon Union
2005
EOF
cat > pos_05_out.txt <<EOF
second film 2
Jhon Union
2005
first film
some name
2009
second film
some name 2
1999
EOF

#- 06 - поиск фильма по году
cat > pos_06_args.txt <<EOF
func_tests/pos_06_in.txt year 2006
EOF
cat > pos_06_in.txt <<EOF
first film
some name
2009
second film
some name 2
1999
second film 2
Jhon Union
2006
EOF
cat > pos_06_out.txt <<EOF
second film 2
Jhon Union
2006
EOF

#- 07 - поиск несуществующего фильма по названию
cat > pos_07_args.txt <<EOF
func_tests/pos_07_in.txt title "undefined film"
EOF
cat > pos_07_in.txt <<EOF
first film
some name
2009
second film
some name 2
1999
second film 2
Jhon Union
2007
EOF
cat > pos_07_out.txt <<EOF
Not found
EOF

#- 08 - поиск среди 50 фильмов
cat > pos_08_args.txt <<EOF
func_tests/pos_08_in.txt title "Target Film"
EOF
python3 -c '
import random

random.seed(202010311126)

N = 50

TITLE_WORDS = [
  [
    "",
    "",
    "",
    "Green ",
    "Stingy ",
    "Incredible ",
    "Nebulous ",
    "Hot ",
    "Muddled ",
    "Gifted ",
    "Male ",
    "Parallel ",
    "Deranged ",
    "Foreign ",
  ],
  [
    "Director",
    "Failure",
    "Contract",
    "Mood",
    "Difficulty",
    "Security",
    "Union",
    "Funeral",
    "Clothes",
    "Bathroom",
  ],
]

PRODUCER_NAMES = [
  [
    "Patrica",
    "Anna",
    "Olivia",
    "Trent",
    "Gertrude",
    "Millicent",
    "Milford",
    "Latisha",
    "Anthony",
    "Miguel",
  ],
  [
    "Jefferson",
    "Roy",
    "Ortega",
    "Ellis",
    "Lane",
    "Klein",
    "Strickland",
    "Hahn",
    "Jacobson",
    "Humphrey",
  ],
]

TARGET_I = random.randrange(0, N)

choice = random.choice

for i in range(N):
  if i == TARGET_I:
    print("Target Film")
    print("name")
    print("2020")
  else:
    print(f"{choice(TITLE_WORDS[0])}{choice(TITLE_WORDS[1])}")
    print(f"{choice(PRODUCER_NAMES[0])} {choice(PRODUCER_NAMES[1])}")
    print(random.randint(1990, 2020))

' > pos_08_in.txt
cat > pos_08_out.txt <<EOF
Target Film
name
2020
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

#- 02 - несуществующий файл
cat > neg_02_args.txt <<EOF
func_tests/neg_02_in.txt title
EOF

#- 03 - неправильное поле
cat > neg_03_args.txt <<EOF
func_tests/neg_03_in.txt tite
EOF
cat > neg_03_in.txt <<EOF
1
2
3
EOF

#- 04 - пустой файл
cat > neg_04_args.txt <<EOF
func_tests/neg_04_in.txt title
EOF
printf "" > neg_04_in.txt
echo > neg_04_out.txt

#- 05 - нет года фильма
cat > neg_05_args.txt <<EOF
func_tests/neg_05_in.txt title
EOF
cat > neg_05_in.txt <<EOF
title
name
EOF
echo > neg_05_out.txt

#- 06 - год фильма отрицательный
cat > neg_06_args.txt <<EOF
func_tests/neg_06_in.txt year
EOF
cat > neg_06_in.txt <<EOF
title
name
-2020
EOF
echo > neg_06_out.txt

#- 07 - пустое поле названия фильма
cat > neg_07_args.txt <<EOF
func_tests/neg_07_in.txt title
EOF
cat > neg_07_in.txt <<EOF

2020
EOF
echo > neg_07_out.txt

#- 08 - пустое поле названия режиссёра
cat > neg_08_args.txt <<EOF
func_tests/neg_08_in.txt title
EOF
cat > neg_08_in.txt <<EOF
title

2020
EOF
echo > neg_08_out.txt

#- 08 - неправильный ключ для поля год
cat > neg_09_args.txt <<EOF
func_tests/neg_09_in.txt year year
EOF
cat > neg_09_in.txt <<EOF
title
name
2020
EOF
echo > neg_09_out.txt

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
