#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
 public:
  Rational() = default;
  Rational(const Rational&) = default;
  Rational(const int num, const int den);
  ~Rational() = default;

  Rational& operator=(const Rational& other) = default;

  // arithmetic methods
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational& operator*=(const Rational& other);

  // unary
  Rational operator-() const;

  // comparisons
  bool operator==(const Rational& other) const;
  bool operator!=(const Rational& other) const;

  // cast to double
  operator double() const;

  // some getters
  int GetNumerator() const;
  int GetDenominator() const;

 private:
  int numerator = 0;
  int denominator = 1;  // > 0

  void Normalize();
  int GCD();
};

Rational operator+(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right);
Rational operator/(const Rational& left, const Rational& right);
Rational operator*(const Rational& left, const Rational& right);

// input, output
std::ostream& operator<<(std::ostream& stream, const Rational& rational);
std::istream& operator>>(std::istream& stream, const Rational& rational);

#endif