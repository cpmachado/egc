/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"


/* FUNCTIONS */

int
computeUnitaryFractions(long long int num, long long int den, long long int *s) {
	long long int n, i;

	s[0] = 0;

	for (i = 1; num > 1; i++) {
		n = den / num + (den % num > 0);
		s[i] = n;
		num = num * n - den;
		den = den * n;
	}

	if(num > 0) {
		s[i] = den;
		i++;
	}
	return i;
}

void
promptForParameter(char *str, long long int *n) {
	printf("%s", str);
	scanf(" %lld", n);
}

void
csvOutput(long long int *s, long long int n) {
	long long int i;

	printf("i,n_i\n");

	for(i = 1; i < n; i++) {
		printf("%lld,%lld\n", i, s[i]);
	}
}

void
simpleOutput(long long int *s, long long int n) {
	long long int i;

	for(i = 1; i < n; i++) {
		printf("%lld\n", s[i]);
	}
}

int
main(int argc, char **argv) {
	long long int s[BUFSIZ];
	long long int n = 0;
	long long int num = -1, den = -1;
	int csv = 0;

	parseFlags(argc, argv, (CliArgs){
		.num = &num,
		.den = &den,
		.csv = &csv
	});
	if(num <= 0) {
		promptForParameter("numerator: ", &num);
	}
	if(den <= 0) {
		promptForParameter("denominator: ", &den);
	}

	if (num > den || num <= 0) {
		fprintf(stderr, "r not in ]0, 1[\n");
		exit(EXIT_FAILURE);
	}

	n = computeUnitaryFractions(num, den, s);
	if(csv) {
		csvOutput(s, n);
	} else {
		simpleOutput(s, n);
	}
	return 0;
}
