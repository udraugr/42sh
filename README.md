### [RU][1] Описание проекта на русском
[1]: https://github.com/udraugr/42sh#42sh-%D0%BF%D1%80%D0%B8%D0%B2%D0%B5%D1%82-%D0%BF%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%BD%D0%BE%D0%BC%D1%83-%D0%B4%D0%B5%D0%B1%D0%B0%D0%B3%D1%83 "RU"
### [EN][2] Description of the project in English
[2]: https://github.com/udraugr/RTv1/blob/master/README.md#rtv1---team-project-on-computer-graphics "EN"

# 42sh: Привет постоянному дебагу.
42sh - это оболочка в стиле bash, которую мы разработали в школепрограммирования 21 на языке Cи. Школа Программирования 21 (филиал французкой школы "Ecole 42"), которая позволяет нам изучать низкоуровневые предметы (в том числе некоторые ассемблеры), чтобы мы могли глубоко понять, что происходит под капотом.

# Сборка проекта:
Для компиляции потребуется скачать библиотеку termcap. 
Для того, чтобы собрать проект, необходимо зайти в корневой каталог проекта и в терминале прописать команду **make**

# Запус проекта:
**./42sh**

# Функционал:
В проекте нам были запрещены обработки строк через регулярные выражения и другие инструменты встроенные в язык, поэтому если они требовались мы писали их сами.
42sh может запускать бинарники, по абсолютному и относительному пути. Так же мы может работать с ENV через команды export и unset.
Наш проект может работать с многими видами перенаправления:
основные >,>>,<,<<,| , логичискими операторами && ||, еще у нас есть встроенные модели типа обработки экранирования, $(()), () {}, $(), обработка шаблонов типа *?.[], и расширенная работа с перемеными типа ${arg1:+arg2},
alias, hash-table.

### Примечание:
Этот проект полностью написан в школе программирования 21, и принадлежит ей.


# 42sh: Hello to the constant debug.
42sh is a bash-style shell that we developed in C programming school 21. School of Programming 21 (a branch of the French school "Ecole 42"), which allows us to study low-level subjects (including some assemblers) so that we can deeply understand what is happening under the hood.
