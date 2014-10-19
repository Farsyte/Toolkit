#ifndef _simple_mat_h
/** Header version string. */
#define _simple_mat_h "simple_mat v0.1"

/** \file
 * * \brief Simple Matrix
 */

#include "simple_base.hh"
#include "simple_row.hh"
#include "simple_col.hh"

#include <iostream>

namespace Farsyte {
  namespace Simple {

    /** Simple 3x3 Matrix.
     */
    struct Mat {

      Mat();

      /** Construct Matrix from Single Scalar.
       * The value is stored in each diagonal element.
       * Other elements are initialized to T().
       * \param v value to write to the diagonal elements.
       */
      explicit Mat(T const &v);

      /** Construct Matrix from Three Scalars.
       * The values are stored in the diagonal elements.
       * Other elements are initialized to T().
       * \param x value to write to the upper left element.
       * \param y value to write to the center element.
       * \param z value to write to the lower right element.
       */
      explicit Mat(T const &x, T const &y, T const &z);

      /** Construct Matrix from Row Vector.
       * The data from the vector are stored in the diagonal of the matrix.
       * Other elements are initialized to T().
       * \param d vector of data to write to the diagonal.
       */
      explicit Mat(Row const &d);

      /** Matrix Construction.
       * Data from the vectors are loaded into
       * the rows of the matrix.
       * \param r0 vector of data for the top row.
       * \param r1 vector of data for the middle row.
       * \param r2 vector of data for the bottom row.
       */
      Mat(Row const &r0,
          Row const &r1,
          Row const &r2);

      /** Matrix Construction from Column Vector.
       * The data from the vector are stored in the diagonal of the matrix.
       * Other elements are initialized to T().
       * \param d vector of data to write to the diagonal.
       */
      explicit Mat(Col const &d);

      /** Access (read-only) to the rows of the matrix.
       */
      Row const &operator[](int r) const;

      /** Access (mutable) to the rows of the matrix.
       */
      Row &operator[](int r);

      /** Access (read-only) to elements of the matrix.
       */
      T             const & operator()(int r, int c) const;

      /** Access (mutable) to elements of the matrix.
       */
      T                   & operator()(int r, int c);

      /** Matrix Comparison for equality.
       */
      bool                  operator==(Mat const &that) const;

      /** Matrix Comparison for inequality.
       */
      bool                  operator!=(Mat const &that) const;

      /** Matrix Increment.
       */
      Mat &operator+=(Mat const &that);

      /** Matrix Decrement.
       */
      Mat &operator-=(Mat const &that);

      /** Matrix Scale Up.
       */
      Mat &operator*=(T by);

      /** Matrix Scale Down.
       */
      Mat &operator/=(T by);

      /** Matrix Data Representation.
       */
      Row a[Nr];

    };

    /** Binary Addition operator for 3x3 Matrices.
     */
    extern Mat operator+(
      Mat a,
      Mat const &b);

    /** Binary Subtraction operator for 3x3 Matrices.
     */
    extern Mat operator-(
      Mat a,
      Mat const &b);

    /** Unary Negative operator for 3x3 Matrix.
     */
    extern Mat operator-(
      Mat const &b);

    /** Multiply Scalar by 3x3 Matrix.
     */
    extern Mat operator*(
      T b,
      Mat a);

    /** Multiply 3x3 Matrix by Scalar.
     */
    extern Mat operator*(
      Mat a,
      T b);

    /** Divide 3x3 Matrix by Scalar.
     */
    extern Mat operator/(
      Mat a,
      T b);

    /** Binary Multiply operator for 3x3 Matrices.
     */
    extern Mat operator*(
      Mat const &a,
      Mat const &b);

    /** Print 3x3 matrix to output stream.
     */
    extern std::ostream &operator<<(std::ostream &str,
                                    Mat const &m);


    /** Multiply Matrix by (Column) Vector.
     */
    V operator*(M const &m, V const &v);

  }
}

#endif//_simple_mat_h
