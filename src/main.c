/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"


int
main(int argc, char **argv) {
	long int s[BUFSIZ];
	long int n, i = 0;
	long int num, den;

	parseFlags(argc, argv);

	printf("Let r be a rational, such that 0 < r < 1\n");
	printf("Input r(n / d): ");
	scanf(" %ld / %ld", &num, &den);

	printf("\n");

	if (num > den) {
		fprintf(stderr, "r not in ]0, 1[\n");
		exit(EXIT_FAILURE);
	}

	while (num > 1) {
		n = den / num + (den % num > 0);
		s[i++] = n;
		num = num * n - den;
		den = den * n;
	}
	if(num > 0) {
		s[i++] = den;
	}
	n = i;

	for(i = 0; i < n; i++) {
		printf("%ld ", s[i]);
	}
	printf("\n");

	return 0;
}
