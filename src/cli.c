/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "util.h"


/* FUNCTION DEFINITIONS */

int
parseVal(char *str, long long int *n) {
	*n = atoll(str);
	if(*n <= 0) {
		printf("Invalid value %s\n", str);
		return 1;
	}
	return 0;
}

void parseFlags(int argc, char **argv, CliArgs args) {
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
			case 'c': *(args.csv) = 1;break;
			case 'n':
				if (curr[j + 1] || i > argc - 1
					|| parseVal(argv[i+1], args.num)) {
					usage();
					exit(EXIT_FAILURE);
				}
				i++;
				break;
			case 'd':
				if (curr[j + 1] || i > argc - 1
					|| parseVal(argv[i+1], args.den)) {
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
