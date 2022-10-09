#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b, e, n, s, t, v, T, E;
} parametrs;

void parsr_flag(parametrs* parametr, int argc, char** argv);

void zanul(parametrs* params);

// int fun_prov_flag(int argc, const char** argv, parametrs* params);

void prin(parametrs* params, char** argv, int i);

#endif  // SRC_CAT_S21_CAT_H_
