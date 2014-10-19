#ifndef _simple_quat_h
/** Header version string. */
#define _simple_quat_h "simple_quat v0.1"

/** \file
 * * \brief Simple Quaternion
 */

#include "simple_base.hh"
#include "simple_col.hh"

#include <iostream>

namespace Farsyte {
    namespace Simple {

        struct Quat {

            Quat();

            explicit
            Quat(T const & wi);

            explicit
            Quat(V const & vi);

            Quat(T const & wi, V const & vi);

            bool                  operator==(Quat const &that) const;

            bool                  operator!=(Quat const &that) const;

            Quat &operator+=(Quat const &that);

            Quat &operator-=(Quat const &that);

            Quat &operator*=(Quat const &that);

            Quat &operator*=(T by);

            Quat &operator/=(T by);

            T w;
            V v;
        };

        extern Quat     operator-(
            Quat const &a);

        extern Quat     operator~(
            Quat const &a);

        extern Quat     operator+(
            Quat a,
            Quat const &b);

        extern Quat     operator-(
            Quat a,
            Quat const &b);

        extern Quat     operator*(
            Quat const &a,
            Quat const &b);

        extern Quat     operator*(
            Quat a,
            T const &b);

        extern Quat     operator*(
            T const &b,
            Quat a);

        extern Quat     operator/(
            Quat a,
            T const &b);

        extern T normsq(
            Quat const &a);

        extern T norm(
            Quat const &a);

        extern std::ostream &operator<<(
            std::ostream &str,
            Quat const &r);

    }
}

#endif//_simple_quat_h
