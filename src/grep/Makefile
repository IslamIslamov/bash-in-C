FLAGS = -Wall -Wextra -Werror -std=c11

all: s21_grep

s21_grep: s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep

check:
	clang-format -style=Google -n *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep