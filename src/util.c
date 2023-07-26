/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>

#include "config.h"


/* FUNCTION DEFINITIONS */
void usage(void) {
	fprintf(stdout,
	        "egc computes an unitary fraction expansion of a given n(|n| < 1).\n"
	        "Usage: sample [OPTIONS]\n"
	        "Options:\n"
	        "   - h          -- display help and exit\n"
	        "   - v          -- display version and exit\n");
}


void version(void) {
	fprintf(stdout,
	        "egc-" VERSION
	        " Copyright © 2023 "
	        ": cpmachado\n");
}

