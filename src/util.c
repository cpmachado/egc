/* See LICENSE for details */

/* HEADERS */
#include <stdio.h>

#include "config.h"


/* FUNCTION DEFINITIONS */
void usage(void) {
	fprintf(stdout,
	        "egc computes an unitary fraction expansion of a given n.\n"
	        "                   n is a rational, such that 0 < n < 1.\n\n"
	        "Usage: egc [OPTIONS] [-n NUMERATOR] [-d DENOMINATOR]\n"
	        "Options:\n"
	        "   - h             -- display help and exit\n"
	        "   - v             -- display version and exit\n"
	        "   - n Numerator   -- set numerator of fraction\n"
	        "   - d Denominator -- set denominator of fraction\n"
	        "   - c             -- display csv output\n");
}


void version(void) {
	fprintf(stdout,
	        "egc-" VERSION
	        " Copyright © 2023 "
	        ": cpmachado\n");
}

