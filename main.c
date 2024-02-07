/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(void) {
	fprintf(stdout,
	        "egc computes an unitary fraction expansion of a given n.\n"
	        "                   n is a rational, such that 0 < n < 1.\n\n"
	        "Usage: egc [OPTIONS] [-n NUMERATOR] [-d DENOMINATOR]\n"
	        "Options:\n"
	        "   - h             -- display help and exit\n"
	        "   - v             -- display version and exit\n");
}


void version(void) {
	fprintf(stdout,
	        "egc-" VERSION
	        " Copyright © 2023-2024 "
	        ": Carlos Pinto Machado \n");
}

void parseFlags(int argc, char **argv) {
	int i, j;
	char *curr;

	for (i = 1; i < argc; i++) {
		curr = argv[i];
		if (*curr != '-') {
			break;
		}
		for (j = 1; curr[j] ; j++) {
			switch (curr[j]) {
			case 'h': usage(); exit(EXIT_SUCCESS);
			case 'v': version(); exit(EXIT_SUCCESS);
			default:
				usage();
				exit(EXIT_FAILURE);
			}
		}
	}
}

int
main(int argc, char **argv) {
	parseFlags(argc, argv);
	return 0;
}
