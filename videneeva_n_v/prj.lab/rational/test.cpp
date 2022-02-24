#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>

#include <fstream>

TEST_CASE("testing arithmetics operations, constructors and comparisons") {
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

  CHECK(b + c == Rational(4, 3));
  CHECK(b - c == Rational(0));
  CHECK(b / c == Rational(1, 1));
  CHECK(b * c == Rational(4, 9));

  b -= c;
  CHECK(b == Rational(0, 1));
  CHECK(c == Rational(2, 3));

  a *= c;
  CHECK(a == Rational(7, 9));
  CHECK(c == Rational(2, 3));

  a /= c;
  CHECK(a == Rational(7, 6));
  CHECK(c == Rational(2, 3));

  CHECK(Rational(0) == Rational());
}

TEST_CASE("testing normalization and cast to double") {
  CHECK(Rational(6, 15) == Rational(2, 5));

  double number = (double)Rational(1, 2);
  CHECK(abs(number - 0.5) < 1e-4);
}

Rational* generateRational() {
  Rational* rational(new Rational(2, 1));
  return rational;
}
TEST_CASE("move constructor and =") {
  Rational* rational;
  rational = generateRational();

  CHECK(rational->num() == 2);
  CHECK(rational->denum() == 1);
}

TEST_CASE("comparisons and unary minus") {
  Rational a(-1, 3);
  Rational b(1, 2);

  CHECK(a < b);
  CHECK(a <= b);
  CHECK(a <= a);
  CHECK(b >= b);

  CHECK(a > -b);
  CHECK(-a < b);
}

TEST_CASE("getters and streams") {
  Rational a = Rational(2, 3);
  Rational b = Rational(2, 3);

  std::cin >> a;
  CHECK(a.num() == -4);
  CHECK(a.denum() == 1);

  b.read_from(std::cin);
  CHECK(b.num() == 1);
  CHECK(b.denum() == 4);

  std::cout << a << std::endl;
  b.write_to(std::cout);
}
