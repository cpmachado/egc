/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"


/* FUNCTIONS */

int
computeUnitaryFractions(long int num, long int den, long int *s) {
	long int n, i;

	for (i = 0; num > 1; i++) {
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
promptForParameters(long int *num, long int *den) {
	printf("Let r be a rational, such that 0 < r < 1\n");
	printf("Input r(n / d): ");
	scanf(" %ld / %ld", num, den);
}

int
main(int argc, char **argv) {
	long int s[BUFSIZ];
	long int n, i = 0;
	long int num, den;

	parseFlags(argc, argv);
	promptForParameters(&num, &den);

	if (num > den) {
		fprintf(stderr, "r not in ]0, 1[\n");
		exit(EXIT_FAILURE);
	}

	n = computeUnitaryFractions(num, den, s);

	for(i = 0; i < n; i++) {
		printf("%ld", s[i]);
		if(i < n - 1) {
			putchar(',');
		}
	}
	putchar('\n');

	return 0;
}
