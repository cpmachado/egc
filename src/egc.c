/* Copyright 2024 cpmachado */

/* HEADERS */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef VERSION
#define VERSION "unknown"
#endif

/* TYPES */
typedef struct CliArgs {
  int64_t *num, *den;
  int32_t *csv, *straight;
} CliArgs;

/* FUNCTION DECLARATIONS */

void parseFlags(int32_t argc, char **argv, CliArgs args);

void promptForParameter(char *str, int64_t *n);

void csvOutput(int64_t *s, int64_t n);

void simpleOutput(int64_t *s, int64_t n);

void straightOutput(int64_t *s, int64_t n);

int32_t computeUnitaryFractions(int64_t num, int64_t den, int64_t *s);

int32_t main(int32_t argc, char **argv) {
  int64_t s[BUFSIZ];
  int64_t n = 0;
  int64_t num = -1, den = -1;
  int32_t csv = 0, straight = 0;

  parseFlags(
      argc, argv,
      (CliArgs){.num = &num, .den = &den, .csv = &csv, .straight = &straight});
  if (num <= 0) {
    promptForParameter("numerator: ", &num);
  }
  if (den <= 0) {
    promptForParameter("denominator: ", &den);
  }

  if (num > den || num <= 0) {
    fprintf(stderr, "r not in ]0, 1[\n");
    exit(EXIT_FAILURE);
  }

  n = computeUnitaryFractions(num, den, s);
  if (csv) {
    csvOutput(s, n);
  } else if (straight) {
    straightOutput(s, n);
  } else {
    simpleOutput(s, n);
  }
  return 0;
}

/* FUNCTION DEFINITIONS */

void usage(void) {
  fprintf(stdout, "egc computes an unitary fraction expansion of a given n.\n"
                  "                   n is a rational, such that 0 < n < 1.\n\n"
                  "Usage: egc [OPTIONS] [-n NUMERATOR] [-d DENOMINATOR]\n"
                  "Options:\n"
                  "   - h             -- display help and exit\n"
                  "   - v             -- display version and exit\n"
                  "   - n Numerator   -- set numerator of fraction\n"
                  "   - d Denominator -- set denominator of fraction\n"
                  "   - c             -- display csv output\n"
                  "   - s             -- display output in tuples \n");
}

void version(void) {
  fprintf(stdout, "egc-" VERSION " Copyright © 2023 "
                  ": cpmachado\n");
}

int32_t parseVal(char *str, int64_t *n) {
  *n = atoll(str);
  if (*n <= 0) {
    printf("Invalid value %s\n", str);
    return 1;
  }
  return 0;
}

void parseFlags(int32_t argc, char **argv, CliArgs args) {
  int32_t i, j;
  char *curr;

  for (i = 1; i < argc; i++) {
    curr = argv[i];
    if (*curr != '-') {
      break;
    }
    for (j = 1; curr[j]; j++) {
      switch (curr[j]) {
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
      case 'v':
        version();
        exit(EXIT_SUCCESS);
      case 'c':
        *(args.csv) = 1;
        break;
      case 's':
        *(args.straight) = 1;
        break;
      case 'n':
        if (curr[j + 1] || i > argc - 1 || parseVal(argv[i + 1], args.num)) {
          usage();
          exit(EXIT_FAILURE);
        }
        i++;
        break;
      case 'd':
        if (curr[j + 1] || i > argc - 1 || parseVal(argv[i + 1], args.den)) {
          usage();
          exit(EXIT_FAILURE);
        }
        i++;
        break;
      default:
        usage();
        exit(EXIT_FAILURE);
      }
    }
  }
}

int32_t computeUnitaryFractions(int64_t num, int64_t den, int64_t *s) {
  int64_t n, i;

  s[0] = 0;

  for (i = 1; num > 1; i++) {
    n = den / num + (den % num > 0);
    s[i] = n;
    num = num * n - den;
    den = den * n;
  }

  if (num > 0) {
    s[i] = den;
    i++;
  }
  return i;
}

void promptForParameter(char *str, int64_t *n) {
  printf("%s", str);
  scanf(" %ld", n);
}

void csvOutput(int64_t *s, int64_t n) {
  int64_t i;

  printf("i,n_i\n");

  for (i = 1; i < n; i++) {
    printf("%ld,%ld\n", i, s[i]);
  }
}

void simpleOutput(int64_t *s, int64_t n) {
  int64_t i;

  for (i = 1; i < n; i++) {
    printf("%ld\n", s[i]);
  }
}

void straightOutput(int64_t *s, int64_t n) {
  int64_t i;

  for (i = 1; i < n; i++) {
    printf("(%ld, %ld)", i, s[i]);
    if (i < n - 1) {
      putchar(',');
    }
  }
  putchar('\n');
}
