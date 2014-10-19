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

    class Mat {
    public:

      Mat();

      explicit Mat(T const &v);

      explicit Mat(T const &x, T const &y, T const &z);

      explicit Mat(Row const &d);

      Mat(Row const &r0,
          Row const &r1,
          Row const &r2);

      explicit Mat(Col const &d);

      Row const &operator[](int r) const;

      Row &operator[](int r);

      T                     operator()(int r, int c) const;

      T &operator()(int r, int c);

      bool                  operator==(Mat const &that) const;

      bool                  operator!=(Mat const &that) const;

      Mat &operator+=(Mat const &that);

      Mat &operator-=(Mat const &that);

      Mat &operator*=(T by);

      Mat &operator/=(T by);

    private:
      Row a[Nr];

    };

    extern Mat operator+(
      Mat a,
      Mat const &b);

    extern Mat operator-(
      Mat a,
      Mat const &b);

    extern Mat operator-(
      Mat const &b);

    extern Mat operator*(
      T b,
      Mat a);

    extern Mat operator*(
      Mat a,
      T b);

    extern Mat operator/(
      Mat a,
      T b);

    extern Mat operator*(
      Mat const &a,
      Mat const &b);

    extern std::ostream &operator<<(std::ostream &str,
                                    Mat const &m);


  }
}

#endif//_simple_mat_h
