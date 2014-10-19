#ifndef _simple_quat_h
/** Header version string. */
#define _simple_quat_h "simple_quat v0.1"

/** \file
 * * \brief Simple Quaternion
 */

#include "simple_base.hh"
#include "simple_col.hh"
#include "simple_mat.hh"

#include <iostream>

namespace Farsyte {
    namespace Simple {

        struct Quat {

            Quat();

            Quat(T const & wi);

            Quat(V const & vi);

            Quat(T const & wi, V const & vi);

            Quat &operator+=(Quat const &that);

            Quat &operator-=(Quat const &that);

            Quat &operator*=(T by);

            Quat &operator/=(T by);

            Quat &operator*=(Quat const &that);

            Quat &operator/=(Quat const &that);

            V operator()(V const &that) const;

            explicit
            operator M() const;

            T w;
            V v;
        };

        extern bool     operator==(
            Quat const &a,
            Quat const &b);

        extern bool     operator!=(
            Quat const &a,
            Quat const &b);

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

        extern Quat     operator/(
            T const &a,
            Quat const &b);

        extern Quat     operator/(
            Quat const &a,
            Quat const &b);

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
