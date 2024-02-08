/* See LICENSE for details */
/* Data structures and operations to support operations */

typedef struct Ratio {
	long long n, d;
} Ratio;

long long gcd(long long a, long long b);

Ratio RatioAdd(Ratio a, Ratio b);

Ratio RatioSub(Ratio a, Ratio b);

Ratio RatioMul(Ratio a, Ratio b);

Ratio RatioDiv(Ratio a, Ratio b);
