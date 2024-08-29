#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flags;

static struct option longFlags[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0},
};

void fileReader(char *argv[], Flags *flags);
int flagReader(int argc, char *argv[], Flags *flags);
void fileOutput(FILE *file, Flags *flags);

#endif  // S21_CAT_H