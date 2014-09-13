#ifndef _matrix_h
#define _matrix_h

/** \file
 * \brief Matrix Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Matrix library.
 */

#include <array>

#include <iostream>
using std::cerr;
using std::endl;

#include <iomanip>
using std::fixed;
using std::setw;
using std::setprecision;

namespace Farsyte {
  namespace Matrix {


    /** Matrix Template.
     * \param Nc    Number of columns in the matrix.
     * \param Nr    Number of rows in the matrix.
     * \param T     Data type for each matrix element.
     *
     * This template implements rectangular matrices
     * of a compile-time determined size, containing
     * elements of compile-time determined type.
     */
    template<int Nc, int Nr, typename T>
    class Matrix {

    protected:
      typedef std::array<T,Nr> C;
      typedef std::array<C,Nc> A;

      T const & sub(int ri, int ci) const
        {
          return data[ci-1][ri-1];
        }

      T       & sub(int ri, int ci)
        {
          return data[ci-1][ri-1];
        }

    public:

      Matrix()
        : data()
        {
        }

      Matrix(Matrix const &c)
        : data(c.data)
        {
        }

      Matrix(A const &a)
        : data(a)
        {
        }

      T const & operator()(int ri, int ci) const
        {
          return sub(ri, ci);
        }

      T       & operator()(int ri, int ci)
        {
          return sub(ri, ci);
        }

      bool equals(Matrix const &p) const {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            if (sub(ri,ci) != p.sub(ri,ci))
              return false;
        return true;
      }

      Matrix & operator+=(Matrix const &p) {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            sub(ri,ci) += p.sub(ri,ci);
        return *this;
      }

      Matrix & operator-=(Matrix const &p) {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            sub(ri,ci) -= p.sub(ri,ci);
        return *this;
      }

    protected:
      A                         data;
    };


    template<int Nc, int Nr, typename T>
    inline bool operator==(Matrix<Nc,Nr,T> const &L, Matrix<Nc,Nr,T> const &R) {
      return L.equals(R);
    }

    template<int Nc, int Nr, typename T>
    inline bool operator!=(Matrix<Nc,Nr,T> const &L, Matrix<Nc,Nr,T> const &R) {
      return !(L == R);
    }

    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator+(Matrix<Nc,Nr,T> L, Matrix<Nc,Nr,T> const &R) {
      return L += R;
    }

    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator-(Matrix<Nc,Nr,T> L, Matrix<Nc,Nr,T> const &R) {
      return L -= R;
    }

    /** Column Vector Template.
     * \param Nr    Number of rows in the vector.
     * \param T     Data type for each vector element.
     *
     * This template implements a column vector
     * of a compile-time determined size, containing
     * elements of compile-time determined type.
     */
    template<int Nr, typename T>
    class ColVec
      : public Matrix<1,Nr,T>
    {
    private:
      typedef Matrix<1,Nr,T>	Base;

    protected:
      typedef typename Base::A	A;

      T const & sub(int ri) const
        {
          return Base::sub(ri, 1);
        }

      T       & sub(int ri)
        {
          return Base::sub(ri, 1);
        }

    public:

      ColVec()
        : Base()
        {
        }

      ColVec(A const &a)
        : Base(a)
        {
        }

      ColVec(ColVec const &c)
        : Base(c)
        {
        }

      T const & operator()(int ri) const
        {
          return sub(ri);
        }

      T       & operator()(int ri)
        {
          return sub(ri);
        }

    };

    /** Position Class.
     *
     * This class implements a representation of
     * a Position (more precisely a change in
     * position), expressed as a column vector
     * of three double precision components.
     */
    class Position
      : public ColVec<3,double>
    {
    private:
      typedef ColVec<3,double>	Base;


    public:

      Position()
        : Base()
        {
        }

      Position(double x, double y, double z)
        : Base(A{{{{x,y,z}}}})
        {
        }

      Position(Position const &p)
        : Base(p)
        {
        }

    };

  }
}

#endif//_matrix_h
