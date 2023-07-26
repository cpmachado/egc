/* See LICENSE for details */

/* CLI parameters */
typedef struct CliArgs {
	long long int *num, *den;
	int *csv, *straight;
} CliArgs;


/* FUNCTION DECLARATIONS */

void parseFlags(int argc, char **argv, CliArgs args);
