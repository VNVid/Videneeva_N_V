#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("testing arithmetics operations and comparisons") {
  Rational a = Rational(2, 3);
  Rational b = Rational(a);
  Rational c = b;

  CHECK(a == b);
  CHECK(b == c);
  CHECK(c == a);

  a += Rational(1, 2);
  CHECK(a == Rational(7, 6));
  b + c;
  CHECK(b == c);
  CHECK(a != c);

  CHECK(b / c == Rational(1, 1));
  CHECK(b * c == Rational(4, 9));
  b -= c;
  CHECK(b == Rational(0, 1));
}

TEST_CASE("testing normalization and cast to double") {
  CHECK(Rational(6, 15) == Rational(2, 5));

  double number = (double)Rational(1, 2);
  CHECK(abs(number - 0.5) < 1e-4);
}