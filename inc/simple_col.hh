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

    /** Simple Column 3-vector.
     */
    struct Col {

      Col();

      /** Construct a Column vector from three scalars.
       */
      Col(T c0, T c1, T c2);

      /** Access (read-only) to an element of the vector.
       */
      T             const & operator[](int i) const;

      /** Access (mutable) to an element of the vector.
       */
      T                   & operator[](int i);

      /** Vector Comparison for equality.
       */
      bool                  operator==(Col const &that) const;

      /** Vector Comparison for inequality.
       */
      bool                  operator!=(Col const &that) const;

      /** Vector increment.
       */
      Col &operator+=(Col const &that);

      /** Vector Decrement.
       */
      Col &operator-=(Col const &that);

      /** Vector Scale Up.
       */
      Col &operator*=(T by);

      /** Vector Scale Down.
       */
      Col &operator/=(T by);

      /** Vector Data Representation.
       */
      T a[Nc];
    };

    /** Unary Negative operator for Column vector. 
     */
    extern Col     operator-(
      Col const &a);

    /** Binary Addition operator for Column vectors.
     */
    extern Col     operator+(
      Col a,
      Col const &b);

    /** Binary Subtraction operator for Column vectors.
     */
    extern Col     operator-(
      Col a,
      Col const &b);

    /** Multiply column vector by scalar operator.
     */
    extern Col     operator*(
      Col a,
      T const &b);

    /** Multiply scalar by column vector operator.
     */
    extern Col     operator*(
      T const &b,
      Col a);

    /** Divide column vector by scalar operator.
     */
    extern Col     operator/(
      Col a,
      T const &b);

    /** Column Vector Cross Product.
     */
    extern Col cross(
      Col const &a,
      Col const &b);

    /** Column Vector Dot Product.
     */
    extern T dot(
      Col const &a,
      Col const &b);

    /** Square of the 2-Norm of a Column Vector.
     */
    extern T normsq(
      Col const &a);

    /** The 2-Norm of a Column Vector.
     */
    extern T norm(
      Col const &a);

    /** Print column vector to output stream.
     */
    extern std::ostream &operator<<(
      std::ostream &str,
      Col const &r);

  }
}

#endif//_simple_col_h
