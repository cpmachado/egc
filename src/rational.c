#include <stdlib.h>
#include "rational.h"

Rational radd(Rational a, Rational b) {
	return rreduce((Rational){
		.n = a.n * b.d + b.n * a.d,
		.d = a.d * b.d
	});
}

Rational rsub(Rational a, Rational b) {
	return rreduce((Rational){
		.n = a.n * b.d - b.n * a.d,
		.d = a.d * b.d
	});
}

Rational rmul(Rational a, Rational b) {
	return rreduce((Rational){
		.n = a.n * b.n,
		.d = a.d * b.d
	});
}

Rational rdiv(Rational a, Rational b) {
	return rreduce((Rational){
		.n = a.n * b.d,
		.d = a.d * b.n
	});
}

long int gcd(long int a, long int b) {

	while(a > 1 && b > 1 && a != b) {
		if(a > b) {
			a -= b;
		} else {
			b -= a;
		}
	}

	if(a != b) {
		return 1;
	}

	return a;
}

Rational rreduce(Rational a) {
	long int factor = gcd(labs(a.n), a.d);

	return (Rational) {
		.n = a.n / factor,
		.d = a.d / factor
	};
}
