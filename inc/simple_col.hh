#ifndef _simple_col_h
/** Header version string. */
#define _simple_col_h "simple_col v0.1"

/** \file
* * \brief Simple Col Vector
*/

#include "simple_base.hh"

#include <iostream>

namespace Farsyte {
  namespace Simple {

    struct Col {

      Col();

      Col(T c0, T c1, T c2);

      T                     operator[](int i) const;

      T &operator[](int i);

      bool                  operator==(Col const &that) const;

      bool                  operator!=(Col const &that) const;

      Col &operator+=(Col const &that);

      Col &operator-=(Col const &that);

      Col &operator*=(T by);

      Col &operator/=(T by);

      T a[Nc];
    };

  }
}

extern Farsyte::Simple::Col     operator-(
    Farsyte::Simple::Col const &a);

extern Farsyte::Simple::Col     operator+(
    Farsyte::Simple::Col a,
    Farsyte::Simple::Col const &b);

extern Farsyte::Simple::Col     operator-(
    Farsyte::Simple::Col a,
    Farsyte::Simple::Col const &b);

extern Farsyte::Simple::Col     operator*(
    Farsyte::Simple::Col a,
    Farsyte::Simple::T const &b);

extern Farsyte::Simple::Col     operator*(
    Farsyte::Simple::T const &b,
    Farsyte::Simple::Col a);

extern Farsyte::Simple::Col     operator/(
    Farsyte::Simple::Col a,
    Farsyte::Simple::T const &b);

extern Farsyte::Simple::Col cross(
    Farsyte::Simple::Col const &a,
    Farsyte::Simple::Col const &b);

extern Farsyte::Simple::T dot(
    Farsyte::Simple::Col const &a,
    Farsyte::Simple::Col const &b);

extern Farsyte::Simple::T normsq(
    Farsyte::Simple::Col const &a);

extern Farsyte::Simple::T norm(
    Farsyte::Simple::Col const &a);

extern std::ostream &operator<<(
    std::ostream &str,
    Farsyte::Simple::Col const &r);

#endif//_simple_col_h
