#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>

#include <sstream>
#include <vector>

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

Rational *generateRational() {
  Rational *rational(new Rational(2, 1));
  return rational;
}
TEST_CASE("move constructor and =") {
  Rational *rational;
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
  SUBCASE("istream: correct inputs") {
    std::vector<std::string> rationals{"-10/2", "1/2", "3", "20/6"};
    std::vector<int> values{-5, 1, 1, 2, 3, 1, 10, 3};

    for (size_t i = 0; i < rationals.size(); i++) {
      std::stringstream strin(rationals[i]);
      Rational rational;
      strin >> rational;

      CHECK(rational.num() == values[2 * i]);
      CHECK(rational.denum() == values[2 * i + 1]);
      CHECK(!strin.fail());
    }
  }
  SUBCASE("ostream") {
    std::vector<Rational> rationals{Rational(-10, 2), Rational(5, 1),
                                    Rational(1, 2), Rational(0, 1)};
    std::vector<std::string> strs{"-5/1", "5/1", "1/2", "0/1"};

    for (size_t i = 0; i < rationals.size(); i++) {
      std::stringstream strout;
      strout << rationals[i];

      CHECK(strout.str() == strs[i]);
    }
  }
  SUBCASE("invalid input") {
    std::vector<std::string> rationals{"-10/0", "1/ 2", "3/", "/6", "str"};

    for (size_t i = 0; i < rationals.size(); i++) {
      std::stringstream strin(rationals[i]);
      Rational rational;
      strin >> rational;

      CHECK(strin.fail());
    }
  }
}

TEST_CASE("exceptions") {
  CHECK_THROWS(Rational(1, 0));

  Rational a = Rational(1, 2);
  Rational zero = Rational(0, 1);

  CHECK_THROWS(a / zero);
  CHECK_THROWS(a /= zero);

  CHECK_THROWS(a / 0);
  CHECK_THROWS(a /= 0);
}

TEST_CASE("arithmetics operations with integers") {
  Rational a = Rational(1, 2);
  int b = 1;

  CHECK((a += b) == Rational(3, 2));
  CHECK((a -= b) == Rational(1, 2));
  CHECK((a *= b) == Rational(1, 2));
  CHECK((a /= b) == Rational(1, 2));

  CHECK(a + b == Rational(3, 2));
  CHECK(a - b == Rational(-1, 2));
  CHECK(a * b == Rational(1, 2));
  CHECK(a / b == Rational(1, 2));
}
