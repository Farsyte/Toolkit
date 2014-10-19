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


        extern Row     operator-(
            Row const &a);

        extern Row     operator+(
            Row a,
            Row const &b);

        extern Row     operator-(
            Row a,
            Row const &b);

        extern Row     operator*(
            Row a,
            T const &b);

        extern Row     operator*(
            T const &b,
            Row a);

        extern Row     operator/(
            Row a,
            T const &b);

        extern Row cross(
            Row const &a,
            Row const &b);

        extern T dot(
            Row const &a,
            Row const &b);

        extern T normsq(
            Row const &a);

        extern T norm(
            Row const &a);

        extern std::ostream &operator<<(
            std::ostream &str,
            Row const &r);

    }
}

#endif//_simple_row_h
