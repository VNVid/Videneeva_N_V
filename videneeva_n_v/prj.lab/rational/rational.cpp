#include "rational.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

Rational::Rational(const int num) : numerator(num) {}

Rational::Rational(const int num, const int den)
    : numerator(num), denominator(den) {
  if (0 == den) {
    throw RationalException("Zero denominator");
  }

  this->Normalize();
}

Rational &Rational::operator+=(const Rational &other) {
  numerator *= other.denum();
  numerator += denominator * other.num();
  denominator *= other.denum();

  Normalize();

  return *this;
}
Rational &Rational::operator-=(const Rational &other) {
  numerator *= other.denum();
  numerator -= denominator * other.num();
  denominator *= other.denum();

  Normalize();

  return *this;
}
Rational &Rational::operator/=(const Rational &other) {
  if (other.num() == 0) {
    throw RationalException("Devision by zero");
  }
  numerator *= other.denum();
  denominator *= other.num();

  Normalize();

  return *this;
}
Rational &Rational::operator*=(const Rational &other) {
  denominator *= other.denum();
  numerator *= other.num();

  Normalize();

  return *this;
}

Rational &Rational::operator+=(const int n) { return *this += Rational(n); }
Rational &Rational::operator-=(const int n) { return *this -= Rational(n); }
Rational &Rational::operator*=(const int n) { return *this *= Rational(n); }
Rational &Rational::operator/=(const int n) { return *this /= Rational(n); }

Rational Rational::operator-() const {
  return Rational(-numerator, denominator);
}

bool Rational::operator==(const Rational &other) const {
  return numerator == other.num() && denominator == other.denum();
}
bool Rational::operator!=(const Rational &other) const {
  return !(*this == other);
}
bool Rational::operator<(const Rational &other) const {
  return (int64_t)num() * (int64_t)other.denum() <
         (int64_t)other.num() * (int64_t)denum();
}
bool Rational::operator<=(const Rational &other) const {
  return *this < other || *this == other;
}
bool Rational::operator>(const Rational &other) const {
  return !(*this <= other);
}
bool Rational::operator>=(const Rational &other) const {
  return !(*this < other);
}

Rational::operator double() const { return (double)numerator / denominator; }

int Rational::num() const { return numerator; }
int Rational::denum() const { return denominator; }

std::istream &Rational::read_from(std::istream &istrm) {
  std::string input = "";
  std::getline(istrm, input);

  int sepInd = -1;
  bool good = true;
  for (size_t i = 0; i < input.size(); i++) {
    if (std::isdigit(input[i]) || i == 0 && input[i] == '-') {
      continue;
    } else if (input[i] == '/') {
      sepInd = i;
      break;
    } else {
      istrm.setstate(std::ios_base::failbit);
      good = false;
      break;
    }
  }
  for (size_t i = sepInd + 1; i < input.size(); i++) {
    if (!std::isdigit(input[i])) {
      istrm.setstate(std::ios_base::failbit);
      good = false;
      break;
    }
  }

  if (good) {
    if (sepInd == -1) {
      numerator = std::stoi(input);
      denominator = 1;
    } else if (sepInd == input.size() - 1 || sepInd == 0) {
      istrm.setstate(std::ios_base::failbit);
    } else {
      numerator = std::stoi(input.substr(0, sepInd));
      denominator =
          std::stoi(input.substr(sepInd + 1, input.size() - sepInd - 1));
      if (denominator == 0) {
        numerator = 0;
        denominator = 1;
        istrm.setstate(std::ios_base::failbit);
      }
    }
  }

  Normalize();

  return istrm;
}
std::ostream &Rational::write_to(std::ostream &ostrm) const {
  ostrm << this->numerator << "/" << this->denominator;

  return ostrm;
}

// input, output
std::ostream &operator<<(std::ostream &stream, const Rational &rational) {
  rational.write_to(stream);
  return stream;
}
std::istream &operator>>(std::istream &stream, Rational &rational) {
  rational.read_from(stream);
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