#ifndef S21_GREP_H_
#define S21_GREP_H_

#define parametrsNumber 10
#define flags                                       \
  {                                                 \
    "-e", "-i", "-v", "-c", "-l", "-n", "-h", "-s", \
        "-f"                                        \
        "-o"                                        \
  }

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  int e, i, v, c, l, n, h, s, f, o, name;
} parametrs;

void zanul(parametrs *params, int kol_e, int *adress_e);
void pars(parametrs *params, int argc, char *argv[]);
void finish(parametrs *params, char **argv, int *adress_e, int kol_e, int i);
int fun_kol_e(int argc, char **argv);
void func_adress_e(int argc, char **argv, int *adress_e, int kol_e);
void prin(parametrs *params, int n_str, char *strA, char **argv, int i);
#endif  // SRC_CAT_S21_GREP_H_
