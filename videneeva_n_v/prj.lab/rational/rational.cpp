#include "rational.h"

#include <cmath>

Rational::Rational(const int num, const int den)
    : numerator(num), denominator(den) {
  if (0 == den) {
    throw std::invalid_argument("Zero denominator");
  }

  this->Normalize();
}

Rational& Rational::operator+=(const Rational& other) {
  numerator *= other.GetDenominator();
  numerator += denominator * other.GetNumerator();
  denominator *= other.GetDenominator();

  Normalize();

  return *this;
}
Rational& Rational::operator-=(const Rational& other) {
  numerator *= other.GetDenominator();
  numerator -= denominator * other.GetNumerator();
  denominator *= other.GetDenominator();

  Normalize();

  return *this;
}
Rational& Rational::operator/=(const Rational& other) {
  numerator *= other.GetDenominator();
  denominator *= other.GetNumerator();

  Normalize();

  return *this;
}
Rational& Rational::operator*=(const Rational& other) {
  denominator *= other.GetDenominator();
  numerator *= other.GetNumerator();

  Normalize();

  return *this;
}

Rational Rational::operator-() const {
  return Rational(-numerator, denominator);
}

bool Rational::operator==(const Rational& other) const {
  return numerator == other.GetNumerator() &&
         denominator == other.GetDenominator();
}
bool Rational::operator!=(const Rational& other) const {
  return !(*this == other);
}

Rational::operator double() const { return (double)numerator / denominator; }

int Rational::GetNumerator() const { return numerator; }
int Rational::GetDenominator() const { return denominator; }

Rational operator+(const Rational& left, const Rational& right) {
  return Rational(left) += right;
}
Rational operator-(const Rational& left, const Rational& right) {
  return Rational(left) -= right;
}
Rational operator/(const Rational& left, const Rational& right) {
  return Rational(left) /= right;
}
Rational operator*(const Rational& left, const Rational& right) {
  return Rational(left) *= right;
}

// input, output
std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
  stream << rational.GetNumerator();
  if (rational.GetDenominator() != 1) {
    stream << "/" << rational.GetDenominator();
  }

  return stream;
}
std::istream& operator>>(std::istream& stream, Rational& rational) {
  int num = 0;
  int den = 1;
  stream >> num >> den;
  rational = Rational(num, den);
  return stream;
}

void Rational::Normalize() {
  int gcd = GCD();
  numerator /= gcd;
  denominator /= gcd;

  if (denominator < 0) {
    denominator *= -1;
    numerator *= -1;
  }
}

int Rational::GCD() {
  int a = abs(numerator);
  int b = abs(denominator);
  while (b != 0) {
    int c = b;
    b = a % b;
    a = c;
  }
  return a;
}