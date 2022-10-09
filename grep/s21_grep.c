#include "s21_grep.h"

int main(int argc, char *argv[]) {
  parametrs params;
  int adress_e[100];
  int kol_e = fun_kol_e(argc, argv);
  zanul(&params, kol_e, adress_e);
  int ret = 0;
  pars(&params, argc, argv);
  if (params.f != 1) {
    func_adress_e(argc, argv, adress_e, kol_e);
    int adress_f_1 = adress_e[0] + kol_e;
    if (argc - adress_f_1 > 1) {
      params.name = 1;
    }
    if (params.l == 1) {
      params.c = 0;
    }
    for (int i = adress_f_1; i < argc; i++) {
      finish(&params, argv, adress_e, kol_e, i);
    }
  }
  return ret;
}
void func_adress_e(int argc, char **argv, int *adress_e, int kol_e) {
  int prev_adres = 0;

  for (int i = 1; i < argc; i++) {
    if ((argv[i])[0] != 45) {
      prev_adres = i;
      break;
    }
  }
  for (int i = 0; i < kol_e; i++) {
    adress_e[i] = prev_adres + i;
  }
}
void pars(parametrs *params, int argc, char *argv[]) {
  int res = 0;
  char *short_options = "eivclnhsfo";

  struct option long_options[] = {{"--exclude", 0, NULL, 'e'},
                                  {"--ignore-case", 0, NULL, 'i'},
                                  {"--invert-match", 0, NULL, 'v'},
                                  {"--count", 0, NULL, 'c'},
                                  {"--files-with-matches", 0, NULL, 'l'},
                                  {"--line-number", 0, NULL, 'n'},
                                  {NULL, 0, NULL, 0}};

  while ((res = getopt_long(argc, argv, short_options, long_options,
                            &optind)) != -1) {
    switch (res) {
      case 'e': {
        params->e = 1;
        break;
      }
      case 'i': {
        params->i = 1;
        break;
      }
      case 'v': {
        params->v = 1;
        break;
      }
      case 'c': {
        params->c = 1;
        break;
      }
      case 'l': {
        params->l = 1;
        break;
      }
      case 'n': {
        params->n = 1;
        break;
      }
      case 'h': {
        params->h = 1;
        break;
      }
      case 's': {
        params->s = 1;
        break;
      }
      case 'f': {
        params->f = 1;
        break;
      }
      case 'o': {
        params->o = 1;
        break;
      }
      case '?':
      default: {
        printf("unknown\n");
        break;
      }
    }
  }
}

void zanul(parametrs *params, int kol_e, int *adress_e) {
  params->e = 0;
  params->i = 0;
  params->v = 0;
  params->c = 0;
  params->l = 0;
  params->n = 0;
  params->h = 0;
  params->s = 0;
  params->f = 0;
  params->o = 0;
  params->name = 0;
  for (int i = 0; i < kol_e; i++) {
    adress_e[i] = 0;
  }
}

void finish(parametrs *params, char **argv, int *adress_e, int kol_e, int i) {
  FILE *fp;
  int cmp = REG_NOMATCH;
  if ((fp = fopen(argv[i], "r")) != NULL) {
    char strA[20000] = "";
    int n_str = 0;
    int num_str = 0;
    while (fgets(strA, 10000, fp) != NULL) {
      regex_t regex;
      n_str++;
      for (int h = 0; h < kol_e; h++) {
        if (params->i == 1) {
          regcomp(&regex, argv[adress_e[h]], REG_ICASE);
        } else {
          regcomp(&regex, argv[adress_e[h]], REG_EXTENDED);
        }
        cmp = regexec(&regex, strA, 0, NULL, 0);
        regfree(&regex);
        if (params->v == 1) {
          if (cmp != 0) {
            prin(params, n_str, strA, argv, i);

            num_str++;
            break;
          }
        } else {
          if (cmp == 0) {
            prin(params, n_str, strA, argv, i);
            num_str++;
            break;
          }
        }
      }
    }
    if (params->c == 1) {
      if (params->name == 1 && params->h == 0) {
        printf("%s:%d\n", argv[i], num_str);
      } else {
        printf("%d\n", num_str);
      }
    }
    if (params->l == 1 && num_str != 0) {
      printf("%s\n", argv[i]);
    }
    fclose(fp);
  } else {
    if (params->s == 0) {
      printf("s21_grep: %s No such file or directory\n", argv[i]);
    }
  }
}

int fun_kol_e(int argc, char **argv) {
  int kol_vo_e = 0;
  for (int i = 0; i < argc; i++) {
    int e = strcmp(argv[i], "-e");
    if (e == 0) {
      kol_vo_e++;
    }
  }
  if (kol_vo_e == 0) {
    kol_vo_e = 1;
  }
  return kol_vo_e;
}

void prin(parametrs *params, int n_str, char *strA, char **argv, int i) {
  if (params->name == 1 && params->c == 0 && params->l == 0 && params->h == 0) {
    if (!(params->o == 1 && params->v == 1)) {
      printf("%s:", argv[i]);
    }
  }
  if (params->c == 0 && params->l == 0) {
    if (params->n == 1) {
      if (params->o == 1) {
        int place = 0;
        char *p;
        while ((p = strstr(&strA[place], argv[optind])) != NULL) {
          place = (int)(p - strA + 1);
          printf("%d:%s\n", n_str, argv[optind]);
        }

      } else {
        printf("%d:%s", n_str, strA);
      }
    } else {
      if (params->o == 1) {
        int place = 0;
        char *p;
        while ((p = strstr(&strA[place], argv[optind])) != NULL) {
          place = (int)(p - strA + 1);
          printf("%s\n", argv[optind]);
        }

      } else {
        printf("%s", strA);
      }
    }
  }
}
