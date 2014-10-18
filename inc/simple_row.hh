#ifndef _simple_row_h
/** Header version string. */
#define _simple_row_h "simple_row v0.1"

/** \file
* * \brief Simple Row Vector
*/

#include "simple_base.hh"

#include <iostream>

namespace Farsyte {
  namespace Simple {

    struct Row {

      Row();

      Row(T c0, T c1, T c2);

      T                     operator[](int i) const;

      T &operator[](int i);

      bool                  operator==(Row const &that) const;

      bool                  operator!=(Row const &that) const;

      Row &operator+=(Row const &that);

      Row &operator-=(Row const &that);

      Row &operator*=(T by);

      Row &operator/=(T by);

      T a[Nc];
    };

  }
}

extern Farsyte::Simple::Row     operator-(
    Farsyte::Simple::Row const &a);

extern Farsyte::Simple::Row     operator+(
    Farsyte::Simple::Row a,
    Farsyte::Simple::Row const &b);

extern Farsyte::Simple::Row     operator-(
    Farsyte::Simple::Row a,
    Farsyte::Simple::Row const &b);

extern Farsyte::Simple::Row     operator*(
    Farsyte::Simple::Row a,
    Farsyte::Simple::T const &b);

extern Farsyte::Simple::Row     operator*(
    Farsyte::Simple::T const &b,
    Farsyte::Simple::Row a);

extern Farsyte::Simple::Row     operator/(
    Farsyte::Simple::Row a,
    Farsyte::Simple::T const &b);

extern Farsyte::Simple::Row cross(
    Farsyte::Simple::Row const &a,
    Farsyte::Simple::Row const &b);

extern Farsyte::Simple::T dot(
    Farsyte::Simple::Row const &a,
    Farsyte::Simple::Row const &b);

extern Farsyte::Simple::T normsq(
    Farsyte::Simple::Row const &a);

extern Farsyte::Simple::T norm(
    Farsyte::Simple::Row const &a);

extern std::ostream &operator<<(
    std::ostream &str,
    Farsyte::Simple::Row const &r);


#endif//_simple_row_h
