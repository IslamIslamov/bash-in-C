#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Options options = {0};
  int isOptionsValid = setOptions(&options, argc, argv);
  if (isOptionsValid && argc >= 3) {
    printResult(&options, argc, argv);
  }
  return 0;
}

int setOptions(Options *options, int argc, char *argv[]) {
  int isOptionsValid = 1;
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhs")) != -1) {
    switch (opt) {
      case 'e': {
        options->e = 1;
        patternsInit(options->pattern, optarg);
        break;
      }
      case 'i': {
        options->i = REG_ICASE;
        break;
      }
      case 'v': {
        options->v = 1;
        break;
      }
      case 'c': {
        options->c = 1;
        break;
      }
      case 'l': {
        options->l = 1;
        break;
      }
      case 'n': {
        options->n = 1;
        break;
      }
      case 'h': {
        options->h = 1;
        break;
      }
      case 's': {
        options->s = 1;
        break;
      }
      default: {
        isOptionsValid = 0;
        break;
      }
    }
  }
  return isOptionsValid;
}

void patternsInit(char *pattern, const char *optarg) {
  if (pattern[0] == 0) {
    strcpy(pattern, optarg);
  } else if (strcmp(pattern, ".*") != 0) {
    strcat(pattern, "|");
    strcat(pattern, optarg);
  }
}

void printResult(Options *options, int argc, char *argv[]) {
  if (options->e == 0) {
    strcpy(options->pattern, argv[optind]);
    optind += 1;
  }
  filesCount(options, argc, argv);
  output(options, argc, argv);
}

void filesCount(Options *options, int argc, char *argv[]) {
  for (int i = optind; i < argc; i++) {
    if ((options->currentFile = fopen(argv[i], "r")) != NULL) {
      options->countFiles++;
      fclose(options->currentFile);
    } else {
      if ((options->s) == 0)
        fprintf(stderr, "grep: %s No such file or directory\n", argv[i]);
      options->countFiles++;
    }
  }
}

void output(Options *options, int argc, char *argv[]) {
  for (int i = optind; i < argc; i++) {
    if ((options->currentFile = fopen(argv[i], "r")) != NULL) {
      regex_t regex;
      regcomp(&regex, options->pattern, options->i);
      printFile(options->countFiles, argv[i], regex, options->currentFile,
                options);
      regfree(&regex);
      fclose(options->currentFile);
    }
  }
}

void printFile(int countFiles, char *filename, regex_t regularExpression,
               FILE *file, Options *options) {
  int lineNumber = 0;
  int fileMatch = 0;
  char input[MAX_PATTERN_LEN];
  regmatch_t matches[10];

  while (fgets(input, sizeof(input), file) != NULL) {
    lineNumber++;
    int status = regexec(&regularExpression, input, 1, matches, 0);
    if ((status == 0 && options->v == 0) ||
        (status == REG_NOMATCH && options->v == 1)) {
      if (options->c == 1) {
        fileMatch++;
      } else if (options->l == 1) {
        printf("%s\n", filename);
        break;
      } else if (options->n == 1) {
        if (countFiles == 1 || options->h == 1) {
          printf("%d:%s", lineNumber, input);
          checkPrintN(input);
        } else {
          printf("%s:%d:%s", filename, lineNumber, input);
          checkPrintN(input);
        }
      } else {
        if (countFiles == 1 || options->h == 1) {
          printf("%s", input);
          checkPrintN(input);
        } else {
          printf("%s:%s", filename, input);
          checkPrintN(input);
        }
      }
    }
  }
  if (options->c == 1) {
    if (countFiles == 1 || options->h == 1) {
      printf("%d\n", fileMatch);
    } else if (options->l == 1 && fileMatch > 0) {
      { printf("%s:1\n", filename); }
    } else {
      printf("%s:%d\n", filename, fileMatch);
    }
  }
  if (options->l == 1 && fileMatch > 0) {
    printf("%s\n", filename);
  }
}

int strLenght(char input[MAX_PATTERN_LEN]) {
  int len = 0;
  while (input[len] != '\0') {
    len++;
  }
  return len;
}

void checkPrintN(char input[MAX_PATTERN_LEN]) {
  if (input[strLenght(input) - 1] != '\n') {
    printf("\n");
  }
}