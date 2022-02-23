#include "rational.h"

#include <cmath>

Rational::Rational(const int num) : numerator(num) {}

Rational::Rational(const int num, const int den)
    : numerator(num), denominator(den) {
  if (0 == den) {
    throw std::invalid_argument("Zero denominator");
  }

  this->Normalize();
}

Rational& Rational::operator+=(const Rational& other) {
  numerator *= other.denum();
  numerator += denominator * other.num();
  denominator *= other.denum();

  Normalize();

  return *this;
}
Rational& Rational::operator-=(const Rational& other) {
  numerator *= other.denum();
  numerator -= denominator * other.num();
  denominator *= other.denum();

  Normalize();

  return *this;
}
Rational& Rational::operator/=(const Rational& other) {
  numerator *= other.denum();
  denominator *= other.num();

  Normalize();

  return *this;
}
Rational& Rational::operator*=(const Rational& other) {
  denominator *= other.denum();
  numerator *= other.num();

  Normalize();

  return *this;
}

Rational Rational::operator-() const {
  return Rational(-numerator, denominator);
}

bool Rational::operator==(const Rational& other) const {
  return numerator == other.num() && denominator == other.denum();
}
bool Rational::operator!=(const Rational& other) const {
  return !(*this == other);
}
bool Rational::operator<(const Rational& other) const {
  return (int64_t)num() * (int64_t)other.denum() <
         (int64_t)other.num() * (int64_t)denum();
}
bool Rational::operator<=(const Rational& other) const {
  return *this < other || *this == other;
}
bool Rational::operator>(const Rational& other) const {
  return !(*this <= other);
}
bool Rational::operator>=(const Rational& other) const {
  return !(*this < other);
}

Rational::operator double() const { return (double)numerator / denominator; }

int Rational::num() const { return numerator; }
int Rational::denum() const { return denominator; }

std::istream& Rational::read_from(std::istream& istrm) {
  istrm >> numerator >> denominator;
  return istrm;
}
std::ostream& Rational::write_to(std::ostream& ostrm) const {
  ostrm << this->numerator;
  if (this->denominator != 1) {
    ostrm << "/" << this->denominator;
  }

  return ostrm;
}

// input, output
std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
  stream << rational.num();
  if (rational.denum() != 1) {
    stream << "/" << rational.denum();
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