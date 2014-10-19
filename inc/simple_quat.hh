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

        /** Simple Quaternion.
         */
        struct Quat {

            Quat();

            /** Scalar to Quaternion Conversion.
             */
            Quat(T const & wi);

            /** Vector to Quaternion Conversion.
             */
            Quat(V const & vi);

            /** Quaternion Initializer.
             */
            Quat(T const & wi, V const & vi);

            /** Quaternion Increment.
             */
            Quat &operator+=(Quat const &that);

            /** Quaternion Decrement.
             */
            Quat &operator-=(Quat const &that);

            /** Quaternion Scale Up.
             */
            Quat &operator*=(T by);

            /** Quaternion Scale Down.
             */
            Quat &operator/=(T by);

            /** Quaternion Multiply.
             */
            Quat &operator*=(Quat const &that);

            /** Quaternion Divide.
             */
            Quat &operator/=(Quat const &that);

            /** Quaternion operate on Vector.
             */
            V operator()(V const &that) const;

            /** Quaternion conversion to Scale-and-Rotate matrix.
             */
            explicit
            operator M() const;

            /** Quaternion Scalar Part Storage. */
            T w;

            /** Quaternion Vector Part Storage. */
            V v;
        };

        /** Quaternion Equality Comparison.
         */
        extern bool     operator==(
            Quat const &a,
            Quat const &b);

        /** Quaternion Inequality Comparison.
         */
        extern bool     operator!=(
            Quat const &a,
            Quat const &b);

        /** Quaternion Unary Negative operator.
         */
        extern Quat     operator-(
            Quat const &a);

        /** Quaternion Conjuaget operator.
         */
        extern Quat     operator~(
            Quat const &a);

        /** Quaternion Addition.
         */
        extern Quat     operator+(
            Quat a,
            Quat const &b);

        /** Quaternion Subtraction.
         */
        extern Quat     operator-(
            Quat a,
            Quat const &b);

        /** Quaternion Multiplication.
         */
        extern Quat     operator*(
            Quat const &a,
            Quat const &b);

        /** Multiply Quaternion by Scalar.
         */
        extern Quat     operator*(
            Quat a,
            T const &b);

        /** Multiply Scalar by Quaternion.
         */
        extern Quat     operator*(
            T const &b,
            Quat a);

        /** Divide Quaternion b Scalar.
         */
        extern Quat     operator/(
            Quat a,
            T const &b);

        /** Divde Scalar by Quaternion.
         * Also known as Quaternion Inversion.
         */
        extern Quat     operator/(
            T const &a,
            Quat const &b);

        /** Binary Division operator for Quaternions.
         */
        extern Quat     operator/(
            Quat const &a,
            Quat const &b);

        /** Square of the 2-Norm of a Quaternion.
         */
        extern T normsq(
            Quat const &a);

        /** The 2-Norm of a Quaternion.
         */
        extern T norm(
            Quat const &a);

        /** Print a quaternion to an output stream.
         */
        extern std::ostream &operator<<(
            std::ostream &str,
            Quat const &r);

    }
}

#endif//_simple_quat_h
