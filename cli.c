/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


/* FUNCTION DEFINITIONS */
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
