#include "s21_cat.h"

int main(int argc, char** argv) {
    int test = 1;
    if (argc > 1) {
        struct flag flags;
        INIT_STRUCT(&flags);
        int last_flag_index = 0;
        for (int i = 1; (i < argc) && (test = 1); i++) {
            if (argv[i][0] == '-') {
                last_flag_index = i;
                if (!PARSER(&flags, argv[i])) test = 0;
            } else {
                break;  // test = 0
                }
        }
        if (test) {
            for (int i = last_flag_index+1; i < argc; i++) {
              //  if (argv[i][0] != '-')
                    OPEN_FILE(argv[i], &flags);
            }
        }
    }
}

int INDICATE_FLAG(struct flag *flags, char c) {
    int success = 1;
    switch (c) {
        case 'e':
            flags->E = 1;
            flags->v = 1;
            break;
        case 'E':
            flags->E = 1;
            break;
        case 'n':
            flags->n = 1;
            break;
        case 't':
            flags->T = 1;
            flags->v = 1;
            break;
        case 'T':
            flags->T = 1;
            break;
        case 's':
            flags->s = 1;
            break;
        case 'b':
            flags->b = 1;
            break;
        case 'v':
            flags->v = 1;
            break;
        default:
        printf("cat: illegal option -- %c\n", c);
        printf("usage: cat [-benstuv] [file ...]\n");
        success = 0;
    }
    return success;
}

int GNU_PARSER(struct flag *flags, char *str) {
    int result = 1;
    if (!strcmp(str, "--number-nonblank")) flags->b = 1;
    else if (!strcmp(str, "--number")) flags->n = 1;
    else if (!strcmp(str, "--squeeze-blank")) flags->s = 1;
    else
    result = 0;
    return result;
}

int PARSER(struct flag *flags, char *str) {
    int success = 1;
    if (!GNU_PARSER(flags, str)) {
    str++;
    while ((*str != '\0') && (success == 1)) {
        if (INDICATE_FLAG(flags, *str)) {
            str++;
        } else {
        success = 0;
        }
    }
    }
    return success;
}

void INIT_STRUCT(struct flag *flags) {
    flags->E = 0;
    flags->v = 0;
    flags->n = 0;
    flags->T = 0;
    flags->s = 0;
    flags->b = 0;
}

void FLAG_b_DO(struct flag *flags, char last_sym, char sym, int *str_number) {
    if ((flags->b == 1) && (last_sym == '\n') && (sym != '\n')) {
        *str_number+=1;
        printf("%6d\t", *str_number);
    }
}

void FLAG_n_DO(struct flag *flags, char last_sym, int *str_number) {
    if ((flags->b == 0) && (last_sym == '\n') && (flags->n == 1)) {
        *str_number+=1;
        printf("%6d\t", *str_number);
    }
}


void FLAG_v_DO(struct flag *flags, char *sym) {
    if (flags->v == 1) {
        if (((*sym >= 0) && (*sym < 9)) || ((*sym > 10) && (*sym < 32))) {
            printf("^");
            *sym = *sym + 64;
        }
        if (*sym == 127) {printf("^"); *sym = '?';}
    }
}

void FLAG_T_DO(struct flag *flags, char *sym) {
    if (flags->T == 1) {
        if (*sym == '\t') {
            printf("^");
            *sym = 'I';
        }
    }
}

void FLAG_E_DO(struct flag *flags, char *sym) {
    if (flags->E == 1) {
        if (*sym == '\n') {
            printf("$");
        }
    }
}

int FLAG_s_DO(struct flag *flags, char sym, char last_sym, int *empty_str) {
    int test = 0;
    if ((sym == '\n') && (last_sym == '\n')) {
        *empty_str+=1;
    } else {
        *empty_str = 0;
    }
    if ((*empty_str > 1) && (flags->s == 1)) test = 1;
    return test;
}

void OPEN_FILE(char *name, struct flag *flags) {
    FILE *file;
    file = fopen(name, "r");
    if (file != NULL) {
        char sym;
        char last_sym = '\n';
        int str_number = 0;
        int empty_str = 0;
        while ((sym = getc(file)) != EOF) {
            if (FLAG_s_DO(flags, sym, last_sym, &empty_str)) continue;
            FLAG_b_DO(flags, last_sym, sym, &str_number);
            FLAG_n_DO(flags, last_sym, &str_number);
            last_sym = sym;
            FLAG_v_DO(flags, &sym);
            FLAG_T_DO(flags, &sym);
            FLAG_E_DO(flags, &sym);
            printf("%c", sym);
        }
    } else {
        printf("cat: %s: No such file or directory\n", name);
    }
    fclose(file);
}


