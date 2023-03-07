
typedef struct Rational {
	long int n, d;
} Rational;

Rational radd(Rational a, Rational b);
Rational rsub(Rational a, Rational b);
Rational rmul(Rational a, Rational b);
Rational rdiv(Rational a, Rational b);
Rational rreduce(Rational a);
