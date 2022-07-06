CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat:
	$(CC) ${CFLAGS} s21_cat.c -o s21_cat

test: s21_cat
	bash cat_test.sh

clean:
	rm -rf s21_cat.o
	rm -rf s21_cat
	rm -rf log.txt

rebuild: clean all

check: cppcheck cpp_lint leak

cpp_lint:	
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c s21_cat.c s21_cat.h
	rm CPPLINT.cfg
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config s21_cat.c
leak:
	make s21_cat
	leaks --atExit -- ./s21_cat -set bytes.txt