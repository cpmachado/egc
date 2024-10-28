/* Copyright 2024 cpmachado */

#include <stdint.h>
#include <stdio.h>

#include "egc.h"

int64_t gcd(int64_t a, int64_t b) {
  int64_t c;
  while (b > 0) {
    if (a > b) {
      c = a;
      a = b;
      b = c % a;
    } else {
      b = b % a;
    }
  }
  return a;
}

int64_t computeEgyptianFraction(Fraction *fraction,
                                EgyptianFraction *egyptian) {
  int64_t num = fraction->num, den = fraction->den;
  int64_t i, gcd_val, n;

  for (i = 0; num > 1; i++) {
    gcd_val = gcd(num, den);
    num /= gcd_val;
    den /= gcd_val;
    n = den / num + (den % num > 0);
    egyptian->dens[i] = n;
    if (INT64_MAX / n < num) {
      fprintf(stderr, "Overflow detected: (num, n) = (%ld, %ld)\n", num, n);
      return -1;
    }
    num = num * n - den;
    if (INT64_MAX / n < den) {
      fprintf(stderr, "Overflow detected: (den, n) = (%ld, %ld)\n", den, n);
      return -1;
    }
    den = den * n;
  }
  egyptian->dens[i] = den;
  i++;
  egyptian->n = i;
  return i;
}
