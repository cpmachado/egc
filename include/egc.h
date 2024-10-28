/* Copyright 2024 cpmachado */

#define MAX_FRACTIONS_EGYPTIAN 100

typedef struct Fraction {
  int64_t num, den;
} Fraction;

typedef struct EgyptianFraction {
  int64_t dens[MAX_FRACTIONS_EGYPTIAN], n;
} EgyptianFraction;

int64_t computeEgyptianFraction(Fraction *fraction, EgyptianFraction *egyptian);
