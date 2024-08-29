#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    Flags flags = {0, 0, 0, 0, 0, 0};
    int countFlags = flagReader(argc, argv, &flags);
    if (countFlags != -1) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
          fileReader(argv, &flags);
        }
      }
    } else {
      printf("Try 'cat --help' for more information.\n");
    }
  } else {
    printf("Error, try cat [OPTION] [FILE]...");
  }
  return 0;
}

void fileReader(char *argv[], Flags *flags) {
  const char *fileName = argv[optind];
  FILE *file = fopen(fileName, "r");

  if (file == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", fileName);
  } else {
    fileOutput(file, flags);
    fclose(file);
  }
}

void fileOutput(FILE *file, Flags *flags) {
  int lineNumber = 1;
  int emptyLineNumber = 0;
  int last = '\n';
  while (!feof(file)) {
    int ch = fgetc(file);
    if (ch == EOF) {
      break;
    }
    if (flags->s && ch == '\n' && last == '\n') {
      emptyLineNumber++;
      if (emptyLineNumber > 1) {
        continue;
      }
    } else {
      emptyLineNumber = 0;
    }
    if (last == '\n' && ((flags->b && ch != '\n') || flags->n)) {
      printf("%6d\t", lineNumber++);
    }
    if (flags->t && ch == '\t') {
      printf("^");
      ch = 'I';
    }
    if (flags->e && ch == '\n') {
      printf("$");
    }
    if (flags->v) {
      if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) ||
          (ch > 126 && ch <= 160)) {
        printf("^");
        if (ch > 126) {
          ch -= 64;
        } else {
          ch += 64;
        }
      }
    }
    printf("%c", ch);
    last = ch;
  }
}

int flagReader(int argc, char *argv[], Flags *flags) {
  int flag = 0;
  int checkCountFlags = 0;

  while ((flag = getopt_long(argc, argv, "bEnsTvet", longFlags, NULL)) != -1) {
    switch (flag) {
      case 'b':
        flags->b = 1;
        checkCountFlags++;
        break;
      case 'E':
        flags->e = 1;
        checkCountFlags++;
        break;
      case 'n':
        flags->n = 1;
        checkCountFlags++;
        break;
      case 's':
        flags->s = 1;
        checkCountFlags++;
        break;
      case 'T':
        flags->t = 1;
        checkCountFlags++;
        break;
      case 'v':
        flags->v = 1;
        checkCountFlags++;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        checkCountFlags++;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        checkCountFlags++;
        break;
      default:
        checkCountFlags = -1;
        break;
    }
    if (flags->b && flags->n) {
      flags->n = 0;
    }
  }
  return checkCountFlags;
}