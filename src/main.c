/* Copyright 2024 cpmachado */

/* HEADERS */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "egc.h"

#ifndef VERSION
#define VERSION "unknown"
#endif

extern int errno;
extern char *optarg;

/* FUNCTION DECLARATIONS */

void usage(void);

void version(void);

int64_t readPositiveInt64(void);

void csvOutput(EgyptianFraction *s);

void simpleOutput(EgyptianFraction *s);

void straightOutput(EgyptianFraction *s);

int32_t main(int32_t argc, char **argv) {
  int64_t n = 0;
  Fraction fraction = {.num = -1, .den = -1};
  EgyptianFraction egyptian;
  int32_t csv = 0, straight = 0;
  int opt;

  while ((opt = getopt(argc, argv, "hvcsn:d:")) != -1) {
    switch (opt) {
    case 'h':
      usage();
      exit(EXIT_SUCCESS);
    case 'v':
      version();
      exit(EXIT_SUCCESS);
    case 'c':
      if (straight) {
        fprintf(stderr, "Already chose straight output\n");
        usage();
        exit(EXIT_FAILURE);
      }
      csv = 1;
      break;
    case 's':
      if (csv) {
        fprintf(stderr, "Already chose csv output\n");
        usage();
        exit(EXIT_FAILURE);
      }
      straight = 1;
      break;
    case 'n':
      fraction.num = strtoll(optarg, NULL, 10);
      if (errno) {
        fprintf(stderr, "%s", strerror(errno));
        usage();
        exit(EXIT_FAILURE);
      }
      break;
    case 'd':
      fraction.den = strtoll(optarg, NULL, 10);
      if (errno) {
        fprintf(stderr, "%s", strerror(errno));
        usage();
        exit(EXIT_FAILURE);
      }
      break;

    default:
      usage();
      exit(EXIT_FAILURE);
    }
  }
  if (fraction.num <= 0) {
    printf("numerator: ");
    fraction.num = readPositiveInt64();
  }
  if (fraction.den <= 0) {
    printf("denominator: ");
    fraction.den = readPositiveInt64();
  }

  if (fraction.num > fraction.den || fraction.num <= 0) {
    fprintf(stderr, "r not in ]0, 1[\n");
    exit(EXIT_FAILURE);
  }

  if ((n = computeEgyptianFraction(&fraction, &egyptian)) <= 0) {
    fprintf(stderr, "Failed computeEgyptianFration with code %ld\n", n);
    exit(EXIT_FAILURE);
  }
  if (csv) {
    csvOutput(&egyptian);
  } else if (straight) {
    straightOutput(&egyptian);
  } else {
    simpleOutput(&egyptian);
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

int64_t readPositiveInt64() {
  char buf[BUFSIZ];
  int64_t n;

  if (!fgets(buf, BUFSIZ, stdin)) {
    fprintf(stderr, "Failed to read number.");
    exit(EXIT_FAILURE);
  }
  n = strtoll(buf, NULL, 10);
  if (errno) {
    fprintf(stderr, "%s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return n;
}

void csvOutput(EgyptianFraction *s) {
  int64_t i;

  printf("i,n_i\n");

  for (i = 0; i < s->n; i++) {
    printf("%ld,%ld\n", i, s->dens[i]);
  }
}

void simpleOutput(EgyptianFraction *s) {
  int64_t i;

  for (i = 0; i < s->n; i++) {
    printf("%ld\n", s->dens[i]);
  }
}

void straightOutput(EgyptianFraction *s) {
  int64_t i;

  for (i = 0; i < s->n; i++) {
    printf("(%ld, %ld)", i, s->dens[i]);
    if (i < s->n - 1) {
      putchar(',');
    }
  }
  putchar('\n');
}
