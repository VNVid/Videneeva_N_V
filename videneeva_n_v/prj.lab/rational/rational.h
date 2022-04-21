#ifndef RATIONAL_H
#define RATIONAL_H

#include <exception>
#include <iosfwd>
#include <string>

class Rational {
 public:
  Rational() = default;
  Rational(const Rational &) = default;
  Rational(Rational &&) = default;
  Rational(const int num);
  Rational(const int num, const int den);
  ~Rational() = default;

  Rational &operator=(const Rational &other) = default;
  Rational &operator=(Rational &&other) = default;

  // arithmetic methods
  Rational &operator+=(const Rational &other);
  Rational &operator-=(const Rational &other);
  Rational &operator/=(const Rational &other);
  Rational &operator*=(const Rational &other);

  Rational &operator+=(const int n);
  Rational &operator-=(const int n);
  Rational &operator*=(const int n);
  Rational &operator/=(const int n);

  // unary
  Rational operator-() const;

  // comparisons
  bool operator==(const Rational &other) const;
  bool operator!=(const Rational &other) const;
  bool operator<(const Rational &other) const;
  bool operator<=(const Rational &other) const;
  bool operator>(const Rational &rhothers) const;
  bool operator>=(const Rational &other) const;

  // cast to double
  operator double() const;

  // some getters
  int num() const;
  int denum() const;

  std::istream &read_from(std::istream &istrm);
  std::ostream &write_to(std::ostream &ostrm) const;

  class RationalException : public std::exception {
   private:
    std::string error;

   public:
    RationalException(std::string error) : error(error) {}

    const char *what() const noexcept { return error.c_str(); }
  };

 private:
  int numerator = 0;
  int denominator = 1;  // > 0

  void Normalize();
  int GCD();
};

inline const Rational operator+(const Rational &left, const Rational &right) {
  return Rational(left) += right;
}
inline const Rational operator-(const Rational &left, const Rational &right) {
  return Rational(left) -= right;
}
inline const Rational operator/(const Rational &left, const Rational &right) {
  return Rational(left) /= right;
}
inline const Rational operator*(const Rational &left, const Rational &right) {
  return Rational(left) *= right;
};

inline const Rational operator+(const Rational &rational, const int n) {
  return Rational(rational) += Rational(n);
}
inline const Rational operator-(const Rational &rational, const int n) {
  return Rational(rational) -= Rational(n);
}
inline const Rational operator*(const Rational &rational, const int n) {
  return Rational(rational) *= Rational(n);
}
inline const Rational operator/(const Rational &rational, const int n) {
  return Rational(rational) /= Rational(n);
}

inline const Rational operator+(const int n, const Rational &rational) {
  return Rational(n) += rational;
}
inline const Rational operator-(const int n, const Rational &rational) {
  return Rational(n) -= rational;
}
inline const Rational operator*(const int n, const Rational &rational) {
  return Rational(n) *= rational;
}
inline const Rational operator/(const int n, const Rational &rational) {
  return Rational(n) /= rational;
}

// input, output
std::ostream &operator<<(std::ostream &stream, const Rational &rational);
std::istream &operator>>(std::istream &stream, Rational &rational);

#endif