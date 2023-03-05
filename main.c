/* See LICENSE for details */


/* HEADERS */
#include <stdio.h>

#include "cli.h"
#include "sample/sample.h"


int main(int argc, char **argv) {

	parseFlags(argc, argv);

	printf("%s is running\n", *argv);

	sample_function();

	return 0;
}
