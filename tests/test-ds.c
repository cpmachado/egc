#include <assert.h>
#include "ds.h"

void
test_gcd(void) {
	assert(gcd(48, 18) == 6);
	assert(gcd(48, -18) == 6);
}

void
test_RatioAdd(void) {
	Ratio a = {.n = 1,.d = 2 };
	Ratio b = {.n = 1,.d = 2 };
	Ratio c = RatioAdd(a, b);

	assert(c.n == 1);
	assert(c.d == 1);
}

int
main(void) {
	test_gcd();
	test_RatioAdd();
	return 0;
}
