#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define MAX_PATTERN_LEN 10240

typedef struct Options {
  int e, i, v, c, l, n, h, s;
  char pattern[MAX_PATTERN_LEN];
  int countFiles;
  FILE *currentFile;
} Options;

void printFile(int countFiles, char *filename, regex_t regularExpression,
               FILE *file, Options *options);
void printResult(Options *options, int argc, char *argv[]);
int setOptions(Options *options, int argc, char *argv[]);
void patternsInit(char *pattern, const char *optarg);
void output(Options *options, int argc, char *argv[]);
void filesCount(Options *options, int argc, char *argv[]);
int strLenght(char input[MAX_PATTERN_LEN]);
void checkPrintN(char input[MAX_PATTERN_LEN]);

#endif  // S21_GREP_H
