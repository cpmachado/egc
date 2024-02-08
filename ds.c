#include <stdlib.h>
#include "ds.h"

long long
gcd(long long a, long long b) {
	long long ap;

	if (a < 0 || b < 0) {
		return gcd(llabs(a), llabs(b));
	}
	if (a == 0) {
		return b ? b : 1;
	} else if (b == 0) {
		return 1;
	}
	while (a != b && b > 0) {
		ap = b;
		b = a % b;
		a = ap;
	}
	return a;
}

Ratio
RatioAdd(Ratio a, Ratio b) {
	long long n = a.n * b.d + b.n * a.d;
	long long d = a.d * b.d;
	long long g = gcd(n, d);
	return (Ratio) {
	.n = n / g,.d = d / g};
}

Ratio
RatioSub(Ratio a, Ratio b) {
	long long n = a.n * b.d - b.n * a.d;
	long long d = a.d * b.d;
	long long g = gcd(n, d);
	return (Ratio) {
	.n = n / g,.d = d / g};
}

Ratio
RatioMul(Ratio a, Ratio b) {
	long long n = a.n * b.n;
	long long d = a.d * b.d;
	long long g = gcd(n, d);
	return (Ratio) {
	.n = n / g,.d = d / g};
}

Ratio
RatioDiv(Ratio a, Ratio b) {
	long long n = a.n * b.d;
	long long d = a.d * b.n;
	long long g = gcd(n, d);
	return (Ratio) {
	.n = n / g,.d = d / g};
}
