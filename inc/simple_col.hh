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

    extern Col     operator-(
      Col const &a);

    extern Col     operator+(
      Col a,
      Col const &b);

    extern Col     operator-(
      Col a,
      Col const &b);

    extern Col     operator*(
      Col a,
      T const &b);

    extern Col     operator*(
      T const &b,
      Col a);

    extern Col     operator/(
      Col a,
      T const &b);

    extern Col cross(
      Col const &a,
      Col const &b);

    extern T dot(
      Col const &a,
      Col const &b);

    extern T normsq(
      Col const &a);

    extern T norm(
      Col const &a);

    extern std::ostream &operator<<(
      std::ostream &str,
      Col const &r);

  }
}

#endif//_simple_col_h
