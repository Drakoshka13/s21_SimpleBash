#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

struct flag {
    int b;
    int s;
    int n;
    int v;
    int E;
    int T;
};

void INIT_STRUCT(struct flag *flags);
int INDICATE_FLAG(struct flag *flags, char c);
int GNU_PARSER(struct flag *flags, char *str);
int PARSER(struct flag *flags, char *str);
void FLAG_b_DO(struct flag *flags, char last_sym, char sym, int *str_number);
void FLAG_n_DO(struct flag *flags, char last_sym, int *str_number);
void FLAG_v_DO(struct flag *flags, char *sym);
void FLAG_T_DO(struct flag *flags, char *sym);
void FLAG_E_DO(struct flag *flags, char *sym);
int FLAG_s_DO(struct flag *flags, char sym, char last_sym, int *empty_str);
void OPEN_FILE(char *name, struct flag *flags);

#endif  // SRC_CAT_S21_CAT_H_
