#include "s21_grep.h"

int main(int argc, char** argv) {
    int test = 1;
    int number_flags = 0;
    char buff[buffer_size] = {0};
    if (argc > 2) {
        struct flag flags;
        INIT_STRUCT(&flags);
        for (int i = 1; i < argc; i++) {
            if ((argv[i][0] == '-') && (strcmp(argv[i-1], "-e"))) {
                int point_e = 0;
                int point_f = 0;
                if (!(PARSER(&flags, argv[i], &point_e, &point_f))) {
                  test = 0;
                } else {
                  number_flags++;
                  if ((point_e) || (point_f)) {
                    snprintf(buff, buffer_size, argv[i+1]);  //  записываем все в буфф
                  }
                }
            } else { continue; }
        }
        //  printf("%d flags\n", number_flags);
        //  printf("buff: %s\n", buff);
        if (test) {
          GREP_FILE(&flags, argc, argv, buff, number_flags);
        }
    }
}

void INIT_STRUCT(struct flag *flags) {
    flags->e = 0;
    flags->i = 0;
    flags->v = 0;
    flags->c = 0;
    flags->l = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->f = 0;
    flags->o = 0;
}

int INDICATE_FLAG(struct flag *flags, char c, int *point_e, int *point_f) {
    int success = 1;
    switch (c) {
         case 'e':
            flags->e = 1;
            *point_e = 1;
            break;
        case 'i':
            flags->i = 1;
            break;
        case 'v':
            flags->v = 1;
            break;
        case 'c':
            flags->c = 1;
            break;
        case 'l':
            flags->l = 1;
            break;
        case 'n':
            flags->n = 1;
            break;
        case 'h':
            flags->h = 1;
            break;
        case 's':
            flags->s = 1;
            break;
        case 'f':
            flags->f = 1;
            *point_f = 1;
            break;
        case 'o':
            flags->o = 1;
            break;
        default:
        printf("grep: invalid option -- %c\n", c);
        printf("usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n"
               "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
               "\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n"
               "\t[--null] [pattern] [file ...]");
        success = 0;
    }
    return success;
}

int PARSER(struct flag *flags, char *str, int* point_e, int* point_f) {
    int success = 1;
    str++;
    while ((*str != '\0') && (success == 1)) {
        if (INDICATE_FLAG(flags, *str, point_e, point_f)) {
            str++;
        } else {
        success = 0;
        }
    }
    return success;
}

void PROCESS(struct flag *flags, FILE *fp, regex_t reg, char *file, int file_count) {  // обработка файла
  char text[buffer_size] = {0};
  regmatch_t pmatch[1];  // подготавливаем слово к поиску
  int line_matches = 0, number_line = 1;
  while (fgets(text, buffer_size - 1, fp) != NULL) {
    int match = 0;
    int success = regexec(&reg, text, 1, pmatch, 0);  // ищем слово
    if (strchr(text, '\n') == NULL)
        strcat(text, "\n");
    if (success == 0 && !flags->v)
        match = 1;
    if (success == REG_NOMATCH && flags->v)  // invert
        match = 1;
  // выводим названия файлов, если файлов больше 1, нет -h, нет -l
    if (match && file_count && !flags->h && !flags->l) printf("%s:", file);
    if (match && !flags->l && !flags->c && flags->n)  // print number of line
        printf("%d:", number_line);
    if (match && !flags->l && !flags->c && !flags->o)
        printf("%s", text);
    if (match && flags->o) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
      printf("%c", text[i]);
      }
      printf("\n");
     }
    line_matches += match;
    number_line++;
  }
  if (flags->l && line_matches > 0)
    printf("%s\n", file);
  if (flags->c && !flags->l)
    printf("%d\n", line_matches);
}


void OPEN_FILE(struct flag *flags, char *pattern, char *filename, int file_count) {
  int cflags = REG_EXTENDED;
  regex_t reg;
  FILE *file;
  file = fopen(filename, "r");
  if (flags->i)
    cflags = REG_ICASE;
  if (file != NULL) {
    regcomp(&reg, pattern, cflags);
    PROCESS(flags, file, reg, filename, file_count);
    regfree(&reg);
    fclose(file);
  } else {
    if (!flags->s) {
    printf("grep: %s: No such file or directory\n", filename);
    }
  }
}

int FLAG_f_DO(struct flag *flags, char *pattern, char *filename) {  // обработка f флага
  FILE *file;
  file = fopen(filename, "r");
  int i = 0;
  if (file != NULL) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == 13 || ch == 10) pattern[i++] = '|';  //  возврат каретки или подача линии
      if (ch != 13 && ch != 10) pattern[i++] = ch;
    }
  } else {
    if (!flags->s) {
    printf("grep: %s: No such file or directory\n", filename);  // файла нет
    }
    i = -1;
  }
  if (pattern[i - 1] == '|')  // последний символ заменяем на "\0"
    pattern[i - 1] = '\0';
  fclose(file);
  return i;
}

void GREP_FILE(struct flag *flags, int argc, char **argv, char *buff, int number_flags) {
  char pattern[buffer_size] = {0};
  int f_patt = 0;
  int find_index = 0;
  if (flags->f)
    f_patt = FLAG_f_DO(flags, pattern, buff);  // записываем файл в шаблон, возвращается кол-во символов
  if (!flags->f && flags->e)
    snprintf(pattern, buffer_size, buff);  //  записываем шаблон , лежит в buff ??
  if (!flags->f && !flags->e) {  // если подается строка для поиска, а не файл или шаблон
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        snprintf(pattern, buffer_size, argv[i]);
        find_index = i;
        break;   // первое слово без флага
      }
    }
  }
  if (f_patt != -1) {  //  файл существует
    int file_count = 0;  //  тестовое значение
    if (argc - 2 - number_flags > 1) file_count = 1;  // если кол-во файлов больше 1
    for (int i = 1; i < argc; i++) {
      if ((argv[i][0] != '-') && (find_index != i) && (strcmp(argv[i], buff))) {
      OPEN_FILE(flags, pattern, argv[i], file_count);
      }
    }
  }
}




