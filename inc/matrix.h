#ifndef _matrix_h
#define _matrix_h "matrix v0.1" /**< for header vs library matching */

/** \file
 * \brief Matrix Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Matrix library.
 */

#include <array>
#include <iomanip>
#include <iostream>

namespace Farsyte
{
  namespace Matrix
  {

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
    class Matrix
    {
    public:

      /** Typedef for array containing the data.
       */
      typedef std::array<T,Nr*Nc> A;

      /** Matrix rows.
       * \returns number of rows `Nr` in tha matrix.
       */
      static int rows()
        {
          return Nr;
        }

      /** Matrix columns.
       * \returns number of columns `Nc` in tha matrix.
       */
      static int cols()
        {
          return Nc;
        }

      /** Matrix elements.
       * \returns number of elements `Nr*Nc` in the matrix.
       */
      static int size()
        {
          return rows() * cols();
        }

    protected:

      /** Matrix subscript to offset calculation.
       */
      int off(int ri, int ci) const
        {
#ifdef RANGE_CHECKER
          RANGE_CHECKER(1,ci,Nc);
          RANGE_CHECKER(1,ri,Nr);
#endif
          return (ri-1) * Nc + (ci-1);
        }

      /** Matrix Subscripting Implementation.
       * \param ri  Row Index, ranging from 1 to Nr inclusive.
       * \param ci  Column Index, ranging from 1 to Nc inclusive.
       * \returns a read-only reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T const & sub(int ri, int ci = 1) const
        {
          return data[off(ri,ci)];
        }

      /** Matrix Subscripting Implementation.
       * \param ri  Row Index, ranging from 1 to Nr inclusive.
       * \param ci  Column Index, ranging from 1 to Nc inclusive.
       * \returns a writable reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T       & sub(int ri, int ci = 1)
        {
          return data[off(ri,ci)];
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
          for (int i = 1; (i <= Nr) && (i <= Nc); ++i)
            sub(i,i) = d;
        }

      /** Matrix Construction from Array of Arrays.
       * \param a  Array to duplicate.
       * This method is used by subclasses to provide value
       * construction of Matrices using Arrays of Arrays of the
       * appropriate dimensions.
       * \note Not a public interface: only classes within the class
       * heirarchy below Matrix should be aware of the data
       * organization within the Matrix object.
       */
      Matrix(A const &a)
        : data(a)
        {
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
       * \returns read-only reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T const & operator()(int ri, int ci = 1) const
        {
          return sub(ri, ci);
        }

      /** Matrix Subscripting Operator.
       * \param ri  Row Index, in the range 1 to Nr inclusive.
       * \param ci  Column Index, in the range 1 to Nc inclusive.
       * \returns modifiable reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T       & operator()(int ri, int ci = 1)
        {
          return sub(ri, ci);
        }

      /** Matrix Equality Test.
       * \param p  Matrix to compare.
       * \returns true if all elements compare equal, else false.
       */
      bool equals(Matrix const &p) const
        {
          for (int ci = 1; ci <= Nc; ++ci)
            for (int ri = 1; ri <= Nr; ++ri)
              if (sub(ri,ci) != p.sub(ri,ci))
                return false;
          return true;
        }

      /** Matrix Increment operation.
       * \param p  Matrix of increment values.
       * \returns this matrix, after incrementing.
       * Each element of this matrix is incremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & increment_by(Matrix const &p)
        {
          for (int ci = 1; ci <= Nc; ++ci)
            for (int ri = 1; ri <= Nr; ++ri)
              sub(ri,ci) += p.sub(ri,ci);
          return *this;
        }

      /** Matrix Increment operator.
       * \param p  Matrix of increment values.
       * \returns this matrix, after incrementing.
       * Each element of this matrix is incremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & operator+=(Matrix const &p)
        {
          return increment_by(p);
        }

      /** Matrix Decrement operation.
       * \param p  Matrix of decrement values.
       * \returns this matrix, after decrementing.
       * Each element of this matrix is decremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & decrement_by(Matrix const &p)
        {
          for (int ci = 1; ci <= Nc; ++ci)
            for (int ri = 1; ri <= Nr; ++ri)
              sub(ri,ci) -= p.sub(ri,ci);
          return *this;
        }

      /** Matrix Decrement operator.
       * \param p  Matrix of decrement values.
       * \returns this matrix, after decrementing.
       * Each element of this matrix is decremented by
       * the value of the corresponding element of the
       * provided matrix.
       */
      Matrix & operator-=(Matrix const &p)
        {
          return decrement_by(p);
        }

      /** Matrix Negate operation.
       * \returns self after negating elements.
       */
      Matrix negate()
        {
          for (int ci = 1; ci <= Nc; ++ci)
            for (int ri = 1; ri <= Nr; ++ri)
              sub(ri,ci) = -sub(ri,ci);
          return *this;
        }

      /** Matrix Transpose operation.
       * \returns transposed matrix.
       */
      Matrix<Nr,Nc,T>
      transpose() const
        {
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
    inline bool operator==(
      Matrix<Nc,Nr,T> const &L,
      Matrix<Nc,Nr,T> const &R)
    {
      return L.equals(R);
    }

    /** Inequality Operator for Matrix-based Classes.
     * \param L   First operand for equality comparison.
     * \param R   Second operand for equality comparison.
     * \returns true if any element does not compare equal, else false.
     */
    template<int Nc, int Nr, typename T>
    inline bool operator!=(
      Matrix<Nc,Nr,T> const &L,
      Matrix<Nc,Nr,T> const &R)
    {
      return !(L == R);
    }

    /** Addition Operator for Matrix-based Classes.
     * \param L  First operand for addition.
     * \param R  Second operand for addition.
     * \returns Matrix whose elements are the sum of corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator+(
      Matrix<Nc,Nr,T> L,
      Matrix<Nc,Nr,T> const &R)
    {
      return L += R;
    }

    /** Addition Operator for Matrix-based Classes.
     * \param L  First operand for addition.
     * \param R  Second operand for addition.
     * \returns Matrix whose elements are the difference between corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator-(
      Matrix<Nc,Nr,T> L,
      Matrix<Nc,Nr,T> const &R)
    {
      return L -= R;
    }

    /** Negation Operator for Matrix-based Classes.
     * \param R  operand for Negation.
     * \returns Matrix whose elements are the negative of the corresponding input elements.
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nc,Nr,T> operator-(
      Matrix<Nc,Nr,T> R)
    {
      return R.negate();
    }

    /** Transpose Operator for Matrix-based Classes.
     * \param R  operand for Transposition
     * \returns Matrix whose elements are the
     */
    template<int Nc, int Nr, typename T>
    inline Matrix<Nr,Nc,T> operator~(
      Matrix<Nc,Nr,T> const &R)
    {
      return R.transpose();
    }

    /** Matrix Multiply.
     * \param L  left operand for multiply.
     * \param R  right operand for multiply.
     * \returns the product of the matrices.
     */
    template<int Nc, int Ni, int Nr, typename T>
    inline Matrix<Nc,Nr,T>
    operator*(
      Matrix<Ni,Nr,T> const & L,
      Matrix<Nc,Ni,T> const & R)
    {
      Matrix<Nc,Nr,T> X;
      for (int ri=1; ri<=Nr; ++ri) {
        for (int ci=1; ci<=Nc; ++ci) {
          T &acc(X(ri,ci));
          acc = L(ri,1)*R(1,ci);
          for (int ii=2; ii<=Ni; ++ii) {
            acc += L(ri,ii)*R(ii,ci);
          }
        }
      }
      return X;
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

    public:

      /** Typedef for matrix generalization. */
      typedef Matrix<1,Nr,T>            MatMe;

      /** Typedef for array containing the data.
       */
      typedef typename MatMe::A A;

    protected:

      /** ColVec Subscripting Implementation.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * \returns read-only reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T const & sub(int ri) const
        {
          return MatMe::sub(ri, 1);
        }

      /** ColVec Subscripting Implementation.
       * \param ri  Row Index, in the range 1 to N inclusive.
       * \returns modifiable reference to the selected element.
       * \note Fortran conventions for array subscripting.
       */
      T       & sub(int ri)
        {
          return MatMe::sub(ri, 1);
        }

    public:

      T const & operator[] (int i) const {
        return sub(i+1,1);
      }

      T       & operator[] (int i)      {
        return sub(i+1,1);
      }

      ColVec()
        : MatMe()
        {
        }

      /** Construct a Column Vector from a 2-D Array.
       * \param a  An appropriately shaped object of the C++ array template type.
       * This initializes the Column Vector data to contain values from
       * the corresponding elements of the array provided.
       */
      ColVec(A const &a)
        : MatMe(a)
        {
        }

      /** Duplicate an existing Column Vector.
       * \param c  A column vector to duplicate.
       * Initialize this column vector to be a duplicate of the one provided.
       * \note Can be called with any appropriately dimensioned matrix.
       */
      ColVec(MatMe const &c)
        : MatMe(c)
        {
        }

    };

    /** ThreeVec Class.
     *
     * This class implements a representation of
     * a ThreeVec (more precisely a change in
     * position), expressed as a column vector
     * of three double precision components.
     */
    class ThreeVec
      : public ColVec<3,double>
    {
    protected:
      /** Typedef for ColVec generalization */
      typedef ColVec<3,double>  ColMe;

      /** Typedef for Matrix generalization. */
      typedef ColMe::MatMe      MatMe;

      /** Typedef for array containing the data.
       */
      typedef typename ColMe::A A;

    public:

      /** ThreeVec Default Constructor.
       * This class assures that all ThreeVec objects are initialized
       * to zero when they are constructed, if no initial value is
       * specified via a different constructor.
       */
      ThreeVec();

      /** ThreeVec Constructor for Given Coefficients.
       * \param x  X coefficient for position.
       * \param y  Y coefficient for position.
       * \param z  Z coefficient for position.
       * Initializes this position to contain the specified
       * coefficients for location along each of the three axes.
       */
      ThreeVec(double x, double y, double z);

      /** Duplicate Constructor for ThreeVec.
       * \param p  ThreeVec to duplicate.
       * Initializes this position to contain a duplicate of the provided position.
       * \note Can be called with any appropriately dimensioned matrix.
       */
      ThreeVec(MatMe const &p);

    };

    /** Cross-Product operation.
     * \param L  First operand for product.
     * \param R  Second operand for product.
     * \returns the cross product of the two vectors.
     */
    extern ThreeVec cross(
      Matrix<1,3,double> const &L,
      Matrix<1,3,double> const &R);

    /** Report version string for library.
     * The optional parameter may provide access
     * to additional version information.
     */
    extern std::string matrix_version(int i = 0);

  }
}

#endif//_matrix_h
