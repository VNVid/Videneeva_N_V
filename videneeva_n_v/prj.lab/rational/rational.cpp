#include <iostream>

class Rational {
 public:
  Rational() = default;
  Rational(const Rational&) = default;  // copy constructor
  Rational(const int num, const int den) : numerator(num), denominator(den) {
    // TODO
    // react to zero denominator
    if (0 == den) {
      // throw SomeException;
    }
    // simplify fraction
  }
  // TODO Rational() move constructor
  ~Rational() = default;

  Rational& operator=(const Rational& other);

  // arithmetic methods
  Rational& operator+=(const Rational& other);

  // unary
  Rational operator-() const { return Rational(-numerator, denominator); }

  // comparisons
  bool operator==(const Rational& other) const;

  // cast to double
  // TODO

  // some getters
  int GetNumerator() const { return numerator; }
  int GetDenominator() const { return denominator; }

 private:
  int numerator = 0;
  int denominator = 1;  // > 0

  void Normalize();
};

Rational operator+(const Rational& left, const Rational& right) {
  return Rational(left) += right;
}

// input, output
std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
  stream << rational.GetNumerator() << "/" << rational.GetDenominator();
  return stream;
}
std::istream& operator>>(std::istream& stream, const Rational& rational);