#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define buffer_size 5000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

struct flag {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
};

void INIT_STRUCT(struct flag *flags);
int INDICATE_FLAG(struct flag *flags, char c, int *point_e, int *point_f);
int PARSER(struct flag *flags, char *str, int* point_e, int* point_f);
void PROCESS(struct flag *flags, FILE *fp, regex_t reg, char *file, int file_count);
void OPEN_FILE(struct flag *flags, char *pattern, char *filename, int file_count);
int FLAG_f_DO(struct flag *flags, char *pattern, char *filename);
void GREP_FILE(struct flag *flags, int argc, char **argv, char *buff, int number_flags);

#endif  // SRC_GREP_S21_GREP_H_
