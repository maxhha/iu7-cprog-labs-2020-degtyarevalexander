# Тесты для лабораторной работы №06

## Входные данные
Аргументы: имя входного файла и префикс.  
Входной файл: описасние предметов `<название>\n<вес>\n<объем>\n`

## Выходные данные
`<название> <вес> <объем>`

## Позитивные тесты
- 01 - длина названия 25 символов
- 02 - сортировка 2-х предметов
- 03 - сортировка 15 предметов
- 04 - вывод 15 предметов
- 05 - префикс 15 предметов

## Негативные тесты
- 01 - нет аргументов
- 02 - 3 аргумента
- 03 - входной файл не существует
- 04 - входной файл пустой
- 05 - длина названия 0 символов
- 06 - длина названия больше 25 символов
- 07 - в описании предмета нет объёма
- 08 - в описании предмета вес содержит букву
- 09 - в описании предмета объем содержит букву
- 10 - в описании предмета вес отрицательный
- 11 - в описании предмета объем отрицательный
- 12 - нет предметов с указанным префиксом
- 13 - предметов больше 15-и