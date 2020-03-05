### [RU][1] Описание проекта на русском
[1]: https://github.com/udraugr/42sh#42sh-%D0%BF%D1%80%D0%B8%D0%B2%D0%B5%D1%82-%D0%BF%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%BD%D0%BE%D0%BC%D1%83-%D0%B4%D0%B5%D0%B1%D0%B0%D0%B3%D1%83 "RU"
### [EN][2] Description of the project in English
[2]: https://github.com/udraugr/42sh#42sh-hello-to-the-constant-debug "EN"

# 42sh
42sh - это оболочка в стиле bash, которую мы разработали в школе программирования 21 на языке Cи. Школа Программирования 21 (филиал французкой школы "Ecole 42") позволяет изучать низкоуровневые подходы к разработке (в том числе некоторые ассемблеры) с целью выработать глубокое понимание того, что происходит под капотом.

# Сборка проекта:
Для компиляции потребуется скачать библиотеку termcap. 
Для того, чтобы собрать проект, необходимо зайти в корневой каталог проекта и в терминале прописать команду **make**

# Запус проекта:
**./42sh**

# Функционал:
В проекте были запрещены обработки строк через регулярные выражения и другие инструменты; обработка ввода была одной из трудных задач проекта. 42sh может запускать бинарники по абсолютному и относительному пути, а также изменять переменные окружения (ENV) через команды export и unset.
Возможности 42sh:
* Перенаправление: >, >>, <, <<, |, >&, &> , <>, <<<
* Логичиские операторы: &&, ||
* Экранирование и кавычки: \\, ', "
* Subshells: (), {}
* Подстановка результата команды: $()
* Подстановка под шаблоны: *, ?, ., []
* Расширенная работа с переменными окружения: ${arg1:+arg2} и другие
* Калькулятор: $(())
* Псевдонимы (alias)
* Хэш-таблица
* команда *test* для проверки условий вида *str1 -e str2* 

### Примечание:
Этот проект полностью написан в школе программирования 21, и принадлежит ей.


# 42sh
42sh is a bash-style shell that we developed in School 21 using C programming language. School 21 (a branch of the French programming school "Ecole 42"), which allows us to study low-level subjects (including some assemblers) so that we can deeply understand what is happening under the hood.

# Build the project:
To compile, you will need to download the termcap library.
In order to build the project, you need to go to the root directory of the project and in the terminal type the command **make**

# Run the project:
**./42sh**

# Functionality:
String processing through regular expressions and other tools was forbidden in the project. Input processing was one of the project's difficult tasks. 42sh can run binaries in the absolute and relative paths, and can also change ENVs through the export and unset commands.
Features 42sh:
* Redirects: >, >>, <, <<, |,> &, &>, <>, <<<
* Logical operators: &&, ||
* Escape and quotation marks: \\, ', "
* Subshells: (), {}
* Substitution of the result of the command: $()
* Substitution for patterns: *, ?, ., []
* Extended work with environment variables: ${arg1:+arg2} and others
* Calculator: $(())
* Aliases
* Hash table
* command *test* to test conditions like *str1 -e str2*

### Note:
This project is completely written in programming school 21, and belongs to her.
