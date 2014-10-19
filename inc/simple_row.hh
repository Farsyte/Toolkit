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

        /** Simple Row 3-vector.
         */
        struct Row {

            Row();

            /** Constructor for a Row Vector.
             * \param c0 value to write to the first element.
             * \param c1 value to write to the second element.
             * \param c2 value to write to the third element.
             */
            Row(T c0, T c1, T c2);

            /** Access (read-only) to an indexed element.
             * \param i which element to access (0, 1, or 2).
             * \returns const reference to the specifeid element.
             */
            T             const & operator[](int i) const;

            /** Access (mutable) to an indexed element.
             * \param i which element to access (0, 1, or 2).
             * \returns const reference to the specifeid element.
             */
            T                   & operator[](int i);

            /** Row Vector Comparison for equality.
             */
            bool                  operator==(Row const &that) const;

            /** Row Vector Comparison for inequality.
             */
            bool                  operator!=(Row const &that) const;

            /** Row Vector Increment.
             */
            Row &operator+=(Row const &that);

            /** Row Vector Decrement.
             */
            Row &operator-=(Row const &that);

            /** Row Vector Scale Up.
             */
            Row &operator*=(T by);

            /** Row Vector Scale Down.
             */
            Row &operator/=(T by);

            /** Row Vector Storage Representation.
             */
            T a[Nc];
        };


        /** Unary Negative of Row Vector.
         */
        extern Row     operator-(
            Row const &a);

        /** Binary Addition operator for Row Vectors.
         */
        extern Row     operator+(
            Row a,
            Row const &b);

        /** Binary Subtraction operator for Row Vectors.
         */
        extern Row     operator-(
            Row a,
            Row const &b);

        /** Multiply Row vector by Scalar.
         */
        extern Row     operator*(
            Row a,
            T const &b);

        /** Multiply Scalar by Row Vector.
         */
        extern Row     operator*(
            T const &b,
            Row a);

        /** Divide Row Vector by Scalar.
         */
        extern Row     operator/(
            Row a,
            T const &b);

        /** Cross Product of Row Vectors.
         */
        extern Row cross(
            Row const &a,
            Row const &b);

        /** Dot Product of Row Vectors.
         */
        extern T dot(
            Row const &a,
            Row const &b);

        /** Square of the 2-Norm of a Row Vector.
         */
        extern T normsq(
            Row const &a);

        /** The 2-Norm of a Row Vector.
         */
        extern T norm(
            Row const &a);

        /** Print a row vector to an output stream.
         */
        extern std::ostream &operator<<(
            std::ostream &str,
            Row const &r);

    }
}

#endif//_simple_row_h
