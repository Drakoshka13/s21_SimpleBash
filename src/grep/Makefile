CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep:
	$(CC) ${CFLAGS} s21_grep.c -o s21_grep

test: s21_grep
	bash grep_test.sh

clean:
	rm -rf s21_grep.o
	rm -rf s21_grep
	rm -rf log.txt

rebuild: clean all

check: cppcheck cpp_lint leak

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config s21_grep.c
	
cpp_lint:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c s21_grep.c s21_grep.h
	rm CPPLINT.cfg

leak:	
	make s21_grep
	leaks --atExit -- ./s21_grep -f find.txt s21_grep.h
