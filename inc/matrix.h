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
    public:

      /** Typedef for type of matrix elements. */
      typedef T               value_type;

      /** Reference to a matrix element. */
      typedef T       &       reference;

      /** Const reference to a matrix element. */
      typedef T const & const_reference;

      /** Pointer to a matrix element. */
      typedef T       *       pointer;

      /** Const pointer to a matrix element. */
      typedef T const * const_pointer;

      /** Number of rows in the matrix. */
      static size_t rows() { return Nr; }

      /** Number of columns in the matrix.*/
      static size_t cols() { return Nc; }

      /** Number of elements in the matrix. */
      static size_t size() { return rows() * cols(); }

    protected:
      
      typedef Matrix<Nc,Nr,T>	Root;

      /** Typedef for array containing one column of the data.
       */
      typedef std::array<T,Nr> C;

      /** Typedef for array containing the data.
       */
      typedef std::array<C,Nc> A;

      /** Matrix Construction from Array.
       * \param a  Array to duplicate.
       * This method is used by subclasses to provide value
       * construction of Matrices using Arrays of Arrays of the
       * appropriate dimensions.
       * \note Nort a public interface: only classes within the class
       * heirarchy below Matrix should be aware of the data
       * organization within the Matrix object.
       */
      Matrix(A const &a)
        : data(a)
        {
        }

      /** Matrix Subscripting Implementation.
       * \param ri  Row Index, ranging from 1 to Nr inclusive.
       * \param ci  Column Index, ranging from 1 to Nc inclusive.
       * This method locates and returns a read-only reference
       * to the element indicated by the subscript.
       * \note Fortran conventions for array subscripting.
       */
      T const & sub(int ri, int ci) const
        {
#ifdef RANGE_CHECKER
          RANGE_CHECKER(1,ci,Nc);
          RANGE_CHECKER(1,ri,Nr);
#endif
          return data[ci-1][ri-1];
        }

      /** Matrix Subscripting Implementation.
       * \param ri  Row Index, ranging from 1 to Nr inclusive.
       * \param ci  Column Index, ranging from 1 to Nc inclusive.
       * This method locates and returns a read-only reference
       * to the element indicated by the subscript.
       * \note Fortran conventions for array subscripting.
       */
      T       & sub(int ri, int ci)
        {
#ifdef RANGE_CHECKER
          RANGE_CHECKER(1,ci,Nc);
          RANGE_CHECKER(1,ri,Nr);
#endif
          return data[ci-1][ri-1];
        }

    public:

      /** Matrix Default Constructor.
       * Matrix objects that are default-constructed are assured
       * of having each element appropriately initialized.
       */
      Matrix()
        : data()
        {
        }

      /** Matrix Diagonal Constructor.
       * \param d   Value to copy into each diagonal element.
       */
      Matrix(T const &d)
        : data()
        {
          for (size_t i = 1; (i <= Nr) && (i <= Nc); ++i)
            sub(i,i) = d;
        }

      /** Duplicate Matrix Construction.
       * \param m  Matrix to duplicate.
       * Initialize this matrix to duplicate the data contained
       * in the provided matrix.
       */
      Matrix(Matrix const &m)
        : data(m.data)
        {
        }

      /** Matrix Subscripting Operator.
       * \param ri  Row Index, in the range 1 to Nr inclusive.
       * \param ci  Column Index, in the range 1 to Nc inclusive.
       * This function returns a read-only reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
      T const & operator()(int ri, int ci) const
        {
          return sub(ri, ci);
        }

      /** Matrix Subscripting Operator.
       * \param ri  Row Index, in the range 1 to Nr inclusive.
       * \param ci  Column Index, in the range 1 to Nc inclusive.
       * This function returns a modifiable reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
      T       & operator()(int ri, int ci)
        {
          return sub(ri, ci);
        }

      /** Matrix Equality Test.
       * \param p  Matrix to compare.
       * This function returns true if each element of this
       * matrix compares equal to the corresponding member
       * of the specified matrix.
       */
      bool equals(Matrix const &p) const {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            if (sub(ri,ci) != p.sub(ri,ci))
              return false;
        return true;
      }

      /** Matrix Increment operation.
       * \param p  Matrix of increment values.
       * Each element of this matrix is incremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & operator+=(Matrix const &p) {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            sub(ri,ci) += p.sub(ri,ci);
        return *this;
      }

      /** Matrix Decrement operation.
       * \param p  Matrix of decrement values.
       * Each element of this matrix is decremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & operator-=(Matrix const &p) {
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            sub(ri,ci) -= p.sub(ri,ci);
        return *this;
      }

      Matrix negate() const {
        Matrix R;
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            R(ri,ci) = -sub(ri,ci);
        return R;
      }

      Matrix transpose() const {
        Matrix<Nr,Nc,T> R;
        for (int ci = 1; ci <= Nc; ++ci)
          for (int ri = 1; ri <= Nr; ++ri)
            R(ci,ri) = sub(ri,ci);
        return R;
      }

    protected:
      /** Storage for Matrix State. */
      A                         data;
    };


    /** Equality Operator for Matrix-based Classes.
     * \param L   First operand for equality comparison.
     * \param R   Second operand for equality comparison.
     * \returns true if all elements compare equal, else false.
     */
    template<int Nc, int Nr, typename T>
    inline bool operator==(Matrix<Nc,Nr,T> const &L, Matrix<Nc,Nr,T> const &R) {
      return L.equals(R);
    }

    /** Inequality Operator for Matrix-based Classes.
     * \param L   First operand for equality comparison.
     * \param R   Second operand for equality comparison.
     * \returns true if any element does not compare equal, else false.
     */
    template<int Nc, int Nr, typename T>
    inline bool operator!=(Matrix<Nc,Nr,T> const &L, Matrix<Nc,Nr,T> const &R) {
      return !(L == R);
    }

    /** Addition Operator for Matrix-based Classes.
     * \param L  First operand for addition.
     * \param R  Second operand for addition.
     * \returns Matrix whose elements are the sum of corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator+(Matrix<Nc,Nr,T> L, Matrix<Nc,Nr,T> const &R) {
      return L += R;
    }

    /** Addition Operator for Matrix-based Classes.
     * \param L  First operand for addition.
     * \param R  Second operand for addition.
     * \returns Matrix whose elements are the difference between corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator-(Matrix<Nc,Nr,T> L, Matrix<Nc,Nr,T> const &R) {
      return L -= R;
    }

    /** Negation Operator for Matrix-based Classes.
     * \param R  operand for Negation.
     * \returns Matrix whose elements are the negative of the corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator-(Matrix<Nc,Nr,T> R) {
      return R.negate();
    }

    /** Transpose Operator for Matrix-based Classes.
     * \param R  operand for Transposition
     * \returns Matrix whose elements are the 
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nr,Nc,T> operator~(Matrix<Nc,Nr,T> R) {
      return R.transpose();
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

    protected:
      typedef Matrix<1,Nr,T>		Base;
      typedef typename Base::Root	Root;

      /** Typedef for array containing the data.
       */
      typedef typename Base::A	A;

      /** Typedef for array containing one column of data.
       */
      typedef typename Base::C	C;

      /** ColVec Subscripting Implementation.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * This function returns a read-only reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
      T const & sub(int ri) const
        {
          return Base::sub(ri, 1);
        }

      /** ColVec Subscripting Implementation.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * This function returns a modifiable reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
      T       & sub(int ri)
        {
          return Base::sub(ri, 1);
        }

    public:

      ColVec()
        : Base()
        {
        }

      /** Construct a Column Vector from a 2-D Array.
       * \param a  An appropriately shaped object of the C++ array template type.
       * This initializes the Column Vector data to contain values from
       * the corresponding elements of the array provided.
       */
      ColVec(A const &a)
        : Base(a)
        {
        }

      /** Construct a Column Vector from a 1-D Array.
       * \param a  An appropriately shaped object of the C++ array template type.
       * This initializes the Column Vector data to contain values from
       * the corresponding elements of the array provided.
       */
      ColVec(C const &a)
        : Base(A{{a}})
        {
        }

      /** Duplicate an existing Column Vector.
       * \param c  A column vector to duplicate.
       * Initialize this column vector to be a duplicate of the one provided.
       * \note Can be called with any appropriately dimensioned matrix.
       */
      ColVec(Root const &c)
        : Base(c)
        {
        }

      /** ColVec Subscripting Operator.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * This function returns a read-only reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
      T const & operator()(int ri) const
        {
          return sub(ri);
        }

      /** ColVec Subscripting Operator.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * This function returns a modifiable reference to the matrix
       * element located at the specified row and column index.
       * \note Fortran conventions for array subscripting.
       */
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
    protected:
      typedef ColVec<3,double>	Base;
      typedef Base::Root	Root;
      typedef Base::C		C;


    public:

      Position()
        : Base()
        {
        }

      /** Position Constructor for Given Coefficients.
       * \param x  X coefficient for position.
       * \param y  Y coefficient for position.
       * \param z  Z coefficient for position.
       * Initializes this position to contain the specified
       * coefficients for location along each of the three axes.
       */
      Position(double x, double y, double z)
        : Base(C{{x,y,z}})
        {
        }

      /** Duplicate Constructor for Position.
       * \param p  Position to duplicate.
       * Initializes this position to contain a duplicate of the provided position.
       * \note Can be called with any appropriately dimensioned matrix.
       */
      Position(Root const &p)
        : Base(p)
        {
        }

    };

  }
}

#endif//_matrix_h
