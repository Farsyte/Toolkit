#include "simple_row.hh"

#include <stdexcept>

using std::out_of_range;

using Farsyte::Simple::Row;
using Farsyte::Simple::T;

Row::Row() {
  for (int i = 0; i < Nc; ++i)
    a[i] = T();
}

Row::Row(T c0, T c1, T c2) {
  a[0] = c0;
  a[1] = c1;
  a[2] = c2;
}

T Row::operator[](int i) const {
  if ((i < 0) || (i >= Nc))
    throw out_of_range("Row Index");
  return a[i];
}

T &Row::operator[](int i) {
  if ((i < 0) || (i >= Nc))
    throw out_of_range("Row Index");
  return a[i];
}

bool Row::operator==(Row const &that) const {
  for (int i = 0; i < Nc; ++i)
    if (a[i] != that.a[i])
      return false;
  return true;
}

bool Row::operator!=(Row const &that) const {
  for (int i = 0; i < Nc; ++i)
    if (a[i] != that.a[i])
      return true;
  return false;
}

Row &Row::operator+=(Row const &that) {
  for (int i = 0; i < Nc; ++i)
    a[i] += that.a[i];
  return *this;
}

Row &Row::operator-=(Row const &that) {
  for (int i = 0; i < Nc; ++i)
    a[i] -= that.a[i];
  return *this;
}

Row &Row::operator*=(T by) {
  for (int i = 0; i < Nc; ++i)
    a[i] *= by;
  return *this;
}

Row &Row::operator/=(T by) {
  for (int i = 0; i < Nc; ++i)
    a[i] /= by;
  return *this;
}

Row operator-(Row const &a) {
  Row z;
  z -= a;
  return z;
}

Row operator+(Row a, Row const &b) {
  a += b;
  return a;
}

Row operator-(Row a, Row const &b) {
  a -= b;
  return a;
}

Row operator*(Row a, T const &b) {
  a *= b;
  return a;
}

Row operator*(T const &b, Row a) {
  a *= b;
  return a;
}

Row operator/(Row a, T const &b) {
  a /= b;
  return a;
}

Row cross(
    Row const &a,
    Row const &b) {
  return Row(
      a[1] * b[2] - a[2] * b[1],
      a[2] * b[0] - a[0] * b[2],
      a[0] * b[1] - a[1] * b[0]);
}

T dot(Row const &a, Row const &b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

T normsq(Row const &a) {
  return a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
}

#include <cmath>

T norm(Row const &a) {
  return sqrt(normsq(a));
}

#include <iomanip>

using std::setw;

std::ostream &operator<<(std::ostream &s, Row const &r) {
  int w = (int) s.width();
  s << setw(1) << "{"
      << setw(w) << r[0] << ","
      << setw(w) << r[1] << ","
      << setw(w) << r[2] << "}";
  return s;
}
