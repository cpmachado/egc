/* See LICENSE for details */

/* HEADERS */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"
#include "egc.h"

void
usage(void) {
	fprintf(stdout,
		"egc computes an unitary fraction expansion of a given n.\n"
		"                   n is a rational, such that 0 < n < 1.\n\n"
		"Usage: egc [OPTIONS] [-n NUMERATOR] [-d DENOMINATOR]\n"
		"Options:\n"
		"   - h             -- display help and exit\n"
		"   - v             -- display version and exit\n"
		"   - n Numerator   -- set numerator of fraction\n"
		"   - d Denominator -- set denominator of fraction\n");
}

void
version(void) {
	fprintf(stdout,
		"egc-" VERSION
		" Copyright © 2023-2024 " ": Carlos Pinto Machado \n");
}

long long
parseVal(char *str, long long int *n) {
	*n = atoll(str);
	if (*n <= 0) {
		printf("Invalid value %s\n", str);
		return 1;
	}
	return 0;
}

void
parseFlags(int argc, char **argv, Ratio * r) {
	int i, j;
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
			case 'n':
				if (curr[j + 1] || i > argc - 1
				    || parseVal(argv[i + 1], &r->n)) {
					usage();
					exit(EXIT_FAILURE);
				}
				i++;
				break;
			case 'd':
				if (curr[j + 1] || i > argc - 1
				    || parseVal(argv[i + 1], &r->d)) {
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

void
RatioPPrint(Ratio r, char *s, int nw, int nd) {
	if (nw || nd) {
		sprintf(s, "%*lld / %*lld", nw, r.n, nd, r.d);
	} else {
		sprintf(s, "%lld / %lld", r.n, r.d);
	}
}

int
main(int argc, char **argv) {
	Ratio r = {.n = 0,.d = 0 };
	parseFlags(argc, argv, &r);
	char buf[1000];
	Ratio rk[1000];
	long long n[1000];
	unsigned long long i, N;
	int nw = 0, nd = 0;

	if (!r.n || !r.d) {
		printf("Missing numerator or denominator\n");
		exit(EXIT_FAILURE);
	}
	N = egyptianUnitFractions(r, rk, n, 1000ULL);
	if (!N) {
		printf("Failed to compute unit fraction expansion\n");
		exit(EXIT_FAILURE);
	}
	RatioPPrint(r, buf, 0, 0);
	printf("r: %s = ", buf);
	r.n = 1;
	for (i = 0; i < N; i++) {
		r.d = n[i];
		RatioPPrint(r, buf, 0, 0);
		printf(" %s", buf);
		if (i < N - 1) {
			printf(" +");
		}
		if (ceil(log10(rk[i].n)) > nw) {
			nw = ceil(log10(rk[i].n));
		}
	}
	printf("\n");
	nd = ceil(log10(rk[N - 2].d));
	printf("%5s | %20s | %5s\n", "i", "ri", "ni");
	for (i = 0; i < N; i++) {
		RatioPPrint(rk[i], buf, nw, nd);
		printf("%5llu | %20s | %5lld\n", i + 1, buf, n[i]);
	}
	return 0;
}
