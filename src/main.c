/* See LICENSE for details */


/* HEADERS */
#include <stdio.h>

#include "cli.h"
#include "rational.h"


void prational(Rational r) {
	printf(" %ld\n", r.n);
	printf("---\n");
	printf("%ld\n", r.d);
}


int main(int argc, char **argv) {
	Rational r;
	long int s[BUFSIZ];
	long int n, i = 0;

	parseFlags(argc, argv);

	printf("Input a rational(n / d): ");
	scanf(" %ld / %ld", &r.n, &r.d);

	printf("\n");

	while (r.n > 1) {
		n = r.d / r.n + 1;
		s[i++] = n;
		printf("%ld\n", n);
		r = rsub(r, (Rational){1, n});
	}
	s[i++] = r.d;
	n = i;

	for(i = 0; i < n; i++) {
		printf("%ld ", s[i]);
	}
	printf("\n");

	return 0;
}
