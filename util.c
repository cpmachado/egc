/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>

#include "config.h"


/* FUNCTION DEFINITIONS */
void usage(void) {
	fprintf(stdout,
	        "sample is a sample program.\n"
	        "Usage: sample [OPTIONS]\n"
	        "Options:\n"
	        "   - h          -- display help and exit\n"
	        "   - v          -- display version and exit\n");
}


void version(void) {
	fprintf(stdout,
	        "sample-" VERSION
	        " Copyright © 2020 "
	        ": Author\n");
}

