#!/bin/bash
#1
./s21_cat bytes.txt >> s21_cat.txt
cat bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#2 -b
./s21_cat -b bytes.txt >> s21_cat.txt
cat -b bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#3 -e
./s21_cat -e bytes.txt >> s21_cat.txt
cat -e bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#4 -n
./s21_cat -n bytes.txt >> s21_cat.txt
cat -n bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#5 -s
./s21_cat -s bytes.txt >> s21_cat.txt
cat -s bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#6 -t
./s21_cat -t bytes.txt >> s21_cat.txt
cat -t bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#7 -ne
./s21_cat -ne bytes.txt >> s21_cat.txt
cat -ne bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#8 -bet
./s21_cat -be bytes.txt >> s21_cat.txt
cat -b -e bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#9 -set
./s21_cat -set bytes.txt >> s21_cat.txt
cat -set bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#10 -sv
./s21_cat -sv bytes.txt >> s21_cat.txt
cat -sv bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#11 -sn
./s21_cat -sn bytes.txt >> s21_cat.txt
cat -sn bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#12 -sb
./s21_cat -sb bytes.txt >> s21_cat.txt
cat -sb bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#13 -nb
./s21_cat -nb bytes.txt >> s21_cat.txt
cat -nb bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#14 -v
./s21_cat -v bytes.txt >> s21_cat.txt
cat -v bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
#15 -ne
./s21_cat -n bytes.txt bytes.txt >> s21_cat.txt
cat -n bytes.txt bytes.txt >> cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
