#include "s21_cat.h"

int main(int argc, char **argv) {
  parametrs params;
  zanul(&params);
  parsr_flag(&params, argc, argv);
  if (params.b == 1) {
    params.n = 0;
  }
  for (int i = optind; i < argc; i++) {
    prin(&params, argv, i);
  }
  return 0;
}
void prin(parametrs *params, char **argv, int i) {
  FILE *file;
  int flag_emptyline = 0;

  if ((file = fopen(argv[i], "r")) != NULL) {
    char str[4096] = "";
    int k = 1;
    int k1 = 0;
    while (fgets(str, 4096, file) != NULL) {
      char dest[4096] = "";
      if (params->v == 1) {
        k1 = 0;
        for (int k = 0; str[k] != '\0'; k++) {
          if (str[k] < -96) {
            dest[k1] = 'M';
            k1++;
            dest[k1] = '-';
            k1++;
            dest[k1] = '^';
            k1++;
            dest[k1] = str[k] + 192;
          } else if (str[k] < 0) {
            dest[k1] = 'M';
            k1++;
            dest[k1] = '-';
            k1++;
            dest[k1] = str[k] + 128;
          } else if (str[k] == 9 || str[k] == 10) {
            dest[k1] = str[k];
          } else if (str[k] < 32) {
            dest[k1] = '^';
            k1++;
            dest[k1] = str[k] + 64;
          } else if (str[k] < 127) {
            dest[k1] = str[k];
          } else {
            dest[k1] = '^';
            k1++;
            dest[k1] = '?';
          }
          k1++;
        }
        strcpy(str, dest);
      }
      if (params->t == 1 || params->T == 1) {
        k1 = 0;
        for (int k = 0; str[k] != '\0'; k++) {
          if (str[k] == '\t') {
            dest[k1] = '^';
            k1++;
            dest[k1] = 'I';
          } else {
            dest[k1] = str[k];
          }
          k1++;
        }
        strcpy(str, dest);
      }

      if (params->e == 1 || params->E == 1) {
        for (int ek = 0; str[ek] != '\0'; ek++) {
          if (str[ek] == '\n') {
            str[ek] = '$';
            str[ek + 1] = '\n';
            break;
          }
        }
      }
      if (params->s == 1) {
        if (flag_emptyline == 0 &&
            (str[0] == '\n' || (str[0] == '$' && str[1] == '\n'))) {
          printf("%s", str);
          flag_emptyline = 1;
        } else if (str[0] != '\n' && (str[0] != '$' && str[1] != '\n')) {
          flag_emptyline = 0;
        }
      }
      if (params->b == 1) {
        if (str[0] != '\n' && str[0] != '$') {
          printf("%6d\t%s", k, str);
          k++;
        } else if (flag_emptyline == 0) {
          printf("%s", str);
        }
      } else if (params->n == 1 && flag_emptyline == 0) {
        printf("%6d\t%s", k, str);
        k++;
      } else if (flag_emptyline == 0) {
        printf("%s", str);
      }
      memset(str, 0, 4096);
    }
    fclose(file);
  } else {
    printf("s21_cat: %s No such file or directory\n", argv[i]);
  }
}

void parsr_flag(parametrs *params, int argc, char **argv) {
  int res = 0, option_index = 0;
  char *short_options = "benstETv";
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"show-ends", 0, NULL, 'E'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {"show-tabs", 0, NULL, 'T'},
                                  {"show-nonprinting", 0, NULL, 'v'},
                                  {NULL, 0, NULL, 0}};
  while ((res = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (res) {
      case 'b': {
        params->b = 1;
        break;
      }
      case 'e': {
        params->e = 1;
        params->v = 1;
        break;
      }
      case 'n': {
        params->n = 1;
        break;
      }
      case 's': {
        params->s = 1;
        break;
      }
      case 't': {
        params->t = 1;
        params->v = 1;
        break;
      }
      case 'v': {
        params->v = 1;
        break;
      }
      case 'E': {
        params->e = 1;
        break;
      }
      case 'T': {
        params->T = 1;
        break;
      }
      case '?':
      default: {
        printf("unknown option\n");
        break;
      }
    }
  }
}
void zanul(parametrs *params) {
  params->b = 0;
  params->e = 0;
  params->n = 0;
  params->s = 0;
  params->t = 0;
  params->v = 0;
  params->T = 0;
  params->E = 0;
}
