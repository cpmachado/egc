/* SEE LICENSE for details */

#include <math.h>

#include "ds.h"

unsigned long long
egyptianUnitFractions(Ratio r, Ratio rk[], long long nk[], unsigned long long N) {
	unsigned long long i = 0;
	Ratio s = {.n = 1,.d = 0 };

	if (r.n < r.d && r.n > 0) {
		for (i = 0; i < N && r.n > 0; i++) {
			s.d = nk[i] = r.d / r.n + (r.d % r.n > 0);
			r = rk[i] = RatioSub(r, s);
		}
	}
	return i;
}
