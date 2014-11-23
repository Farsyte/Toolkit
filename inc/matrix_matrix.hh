#ifndef _matrix_matrix_h
/** Header version string. */
#define _matrix_matrix_h "matrix_matrix v0.1"

/** \file
* * \brief Matrix Template
*/

#include <array>
#include <iostream>
#include <iomanip>

namespace Farsyte {
    namespace Matrix {

        /** Construct matrix range error string. */
        extern std::string matrix_range_error(
                int Nr, int Nc, int ri, int ci);


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

            /** Typedef for array containing the data.
            */
            typedef std::array<T, Nr * Nc> A;

            /** Matrix rows.
            * \returns number of rows `Nr` in tha matrix.
            */
            static int rows() {
                return Nr;
            }

            /** Matrix columns.
            * \returns number of columns `Nc` in tha matrix.
            */
            static int cols() {
                return Nc;
            }

            /** Matrix elements.
            * \returns number of elements `Nr*Nc` in the matrix.
            */
            static int size() {
                return rows() * cols();
            }

        protected:

            /** Matrix subscript to offset calculation.
            */
            int off(int ri, int ci) const {
                if ((ri < 0) || (ri >= Nr) ||
                        (ci < 0) || (ci >= Nc))
                    throw std::out_of_range(matrix_range_error(Nr, Nc, ri, ci));

                return ri * Nc + ci;
            }

            /** Matrix Subscripting Implementation.
            * \param ri  Row Index, ranging from 1 to Nr inclusive.
            * \param ci  Column Index, ranging from 1 to Nc inclusive.
            * \returns a read-only reference to the selected element.
            * \note Fortran conventions for array subscripting.
            */
            T const &data(int ri, int ci = 0) const {
                return a[off(ri, ci)];
            }

            /** Matrix Subscripting Implementation.
            * \param ri  Row Index, ranging from 1 to Nr inclusive.
            * \param ci  Column Index, ranging from 1 to Nc inclusive.
            * \returns a writable reference to the selected element.
            * \note Fortran conventions for array subscripting.
            */
            T &data(int ri, int ci = 0) {
                return a[off(ri, ci)];
            }

        public:

            /** Matrix Default Constructor.
            * Matrix objects that are default-constructed are assured
            * of having each element appropriately initialized.
            */
            Matrix()
                    : a() {
            }

            /** Matrix Diagonal Constructor.
            * \param d   Value to copy into each diagonal element.
            */
            Matrix(T const &d)
                    : a() {
                for (int i = 0; (i < Nr) && (i < Nc); ++i)
                    data(i, i) = d;
            }

            /** Matrix Construction from Array of Arrays.
            * \param iv initialization vector.
            * This method is used by subclasses to provide value
            * construction of Matrices using appropriately
            * sized and shaped initialization vectors.
            * \note Not a public interface: only classes within the class
            * heirarchy below Matrix should be aware of the data
            * organization within the Matrix object.
            */
            Matrix(A const &iv)
                    : a(iv) {
            }

            /** Duplicate Matrix Construction.
            * \param m  Matrix to duplicate.
            * Initialize this matrix to duplicate the data contained
            * in the provided matrix.
            */
            Matrix(Matrix const &m)
                    : a(m.a) {
            }

            /** Fast linear element access (read-only).
            * \param i element index.
            * \returns an element within the matrix.
            */
            T const &operator[](int i) const {
                return a[i];
            }

            /** Fast linear element access (mutable).
            * \param i element index.
            * \returns an element within the matrix.
            */
            T &operator[](int i) {
                return a[i];
            }

            /** Matrix Subscripting Operator.
            * \param ri  Row Index, in the range 1 to Nr inclusive.
            * \param ci  Column Index, in the range 1 to Nc inclusive.
            * \returns read-only reference to the selected element.
            * \note Fortran conventions for array subscripting.
            */
            T const &operator()(int ri, int ci = 0) const {
                return data(ri, ci);
            }

            /** Matrix Subscripting Operator.
            * \param ri  Row Index, in the range 1 to Nr inclusive.
            * \param ci  Column Index, in the range 1 to Nc inclusive.
            * \returns modifiable reference to the selected element.
            * \note Fortran conventions for array subscripting.
            */
            T &operator()(int ri, int ci = 0) {
                return data(ri, ci);
            }

            /** Matrix Equality Test.
            * \param p  Matrix to compare.
            * \returns true if all elements compare equal, else false.
            */
            bool equals(Matrix const &p) const {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        if (data(ri, ci) != p.data(ri, ci))
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
            Matrix &increment_by(Matrix const &p) {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        data(ri, ci) += p.data(ri, ci);
                return *this;
            }

            /** Matrix Increment operator.
            * \param p  Matrix of increment values.
            * \returns this matrix, after incrementing.
            * Each element of this matrix is incremented by
            * the value of the corresponding element of the
            * provided matrix.
            */
            Matrix &operator+=(Matrix const &p) {
                return increment_by(p);
            }

            /** Matrix Decrement operation.
            * \param p  Matrix of decrement values.
            * \returns this matrix, after decrementing.
            * Each element of this matrix is decremented by
            * the value of the corresponding element of the
            * provided matrix.
            */
            Matrix &decrement_by(Matrix const &p) {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        data(ri, ci) -= p.data(ri, ci);
                return *this;
            }

            /** Matrix Decrement operator.
            * \param p  Matrix of decrement values.
            * \returns this matrix, after decrementing.
            * Each element of this matrix is decremented by
            * the value of the corresponding element of the
            * provided matrix.
            */
            Matrix &operator-=(Matrix const &p) {
                return decrement_by(p);
            }

            /** Matrix Scalar Multiply operation.
            * \param p  Scaling factor.
            * \returns this matrix, after scaling values up.
            * Each element of this matrix is multiplied by
            * the provided scale factor.
            */
            Matrix &scalar_mul_by(T const &p) {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        data(ri, ci) *= p;
                return *this;
            }

            /** Matrix Scalar Multiply operator.
            * \param p  Scalaing Factor.
            * \returns this matrix, after scaling values up.
            * Each element of this matrix is multiplied by
            * the provided scale factor.
            */
            Matrix &operator*=(T const &p) {
                return scalar_mul_by(p);
            }

            /** Matrix Scalar Divide operation.
            * \param p  Scaling Factor.
            * \returns this matrix, after scaling values down.
            * Each element of this matrix is divided by
            * the scaling factor.
            */
            Matrix &scalar_div_by(T const &p) {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        data(ri, ci) /= p;
                return *this;
            }

            /** Matrix Scalar Divide operator.
            * \param p  Scaling Factor.
            * \returns this matrix, after scaling values down.
            * Each element of this matrix is divided by
            * the scaling factor.
            */
            Matrix &operator/=(T const &p) {
                return scalar_div_by(p);
            }

            /** Matrix Negate operation.
            * \returns self after negating elements.
            */
            Matrix negate() {
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        data(ri, ci) = -data(ri, ci);
                return *this;
            }

            /** Matrix Transpose operation.
            * \returns transposed matrix.
            */
            Matrix<Nr, Nc, T>
            transpose() const {
                Matrix<Nr, Nc, T> R;
                for (int ci = 0; ci < Nc; ++ci)
                    for (int ri = 0; ri < Nr; ++ri)
                        R(ci, ri) = data(ri, ci);
                return R;
            }

        protected:
            /** Storage for Matrix State. */
            A a;
        };

        /** Equality Operator for Matrix-based Classes.
        * \param L   First operand for equality comparison.
        * \param R   Second operand for equality comparison.
        * \returns true if all elements compare equal, else false.
        */
        template<int Nc, int Nr, typename T>
        inline bool operator==(
                Matrix<Nc, Nr, T> const &L,
                Matrix<Nc, Nr, T> const &R) {
            return L.equals(R);
        }

        /** Inequality Operator for Matrix-based Classes.
        * \param L   First operand for equality comparison.
        * \param R   Second operand for equality comparison.
        * \returns true if any element does not compare equal, else false.
        */
        template<int Nc, int Nr, typename T>
        inline bool operator!=(
                Matrix<Nc, Nr, T> const &L,
                Matrix<Nc, Nr, T> const &R) {
            return !(L == R);
        }

        /** Addition Operator for Matrix-based Classes.
        * \param L  First operand for addition.
        * \param R  Second operand for addition.
        * \returns Matrix whose elements are the sum of corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator+(
                Matrix<Nc, Nr, T> L,
                Matrix<Nc, Nr, T> const &R) {
            return L += R;
        }

        /** Subtraction Operator for Matrix-based Classes.
        * \param L  First operand for addition.
        * \param R  Second operand for addition.
        * \returns Matrix whose elements are the difference between corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator-(
                Matrix<Nc, Nr, T> L,
                Matrix<Nc, Nr, T> const &R) {
            return L -= R;
        }

        /** Scalar Multiplication Operator for Matrix-based Classes.
        * \param L  First operand for addition.
        * \param R  Second operand for addition.
        * \returns Matrix whose elements are the sum of corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator*(
                Matrix<Nc, Nr, T> L,
                T const &R) {
            return L *= R;
        }

        /** Scalar Pre-Multiplication Operator for Matrix-based Classes.
        * \param L  First operand for addition.
        * \param R  Second operand for addition.
        * \note: assumes multiplication (T*T) is commutative.
        * \returns Matrix whose elements are the sum of corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator*(
                T const &L,
                Matrix<Nc, Nr, T> R) {
            return R *= L;
        }

        /** Scalar Division Operator for Matrix-based Classes.
        * \param L  First operand for addition.
        * \param R  Second operand for addition.
        * \returns Matrix whose elements are the difference between corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator/(
                Matrix<Nc, Nr, T> L,
                T const &R) {
            return L /= R;
        }

        /** Negation Operator for Matrix-based Classes.
        * \param R  operand for Negation.
        * \returns Matrix whose elements are the negative of the corresponding input elements.
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nc, Nr, T> operator-(
                Matrix<Nc, Nr, T> R) {
            return R.negate();
        }

        /** Transpose Operator for Matrix-based Classes.
        * \param R  operand for Transposition
        * \returns Matrix whose elements are the
        */
        template<int Nc, int Nr, typename T>
        inline Matrix<Nr, Nc, T> operator~(
                Matrix<Nc, Nr, T> const &R) {
            return R.transpose();
        }

        /** Matrix Multiply.
        * \param L  left operand for multiply.
        * \param R  right operand for multiply.
        * \returns the product of the matrices.
        */
        template<int Nc, int Ni, int Nr, typename T>
        inline Matrix<Nc, Nr, T>
        operator*(
                Matrix<Ni, Nr, T> const &L,
                Matrix<Nc, Ni, T> const &R) {
            Matrix<Nc, Nr, T> X;
            for (int ri = 0; ri < Nr; ++ri) {
                for (int ci = 0; ci < Nc; ++ci) {
                    T &acc(X(ri, ci));
                    acc = L(ri, 0) * R(0, ci);
                    for (int ii = 1; ii < Ni; ++ii) {
                        acc += L(ri, ii) * R(ii, ci);
                    }
                }
            }
            return X;
        }

        /** Matrix Multiply Special Case: 1xN by Nx1
        * \param L  left operand for multiply.
        * \param R  right operand for multiply.
        * This version of multiply is used when the result
        * would be a 1x1 matrix -- that is, when we are
        * calculating the inner product of two colvecs
        * by transposing the first.
        * \returns the product of the matrices.
        */
        template<int Ni, typename T>
        inline T
        operator*(
                Matrix<Ni, 1, T> const &L,
                Matrix<1, Ni, T> const &R) {
            T acc(L(0, 0) * R(0, 0));
            for (int i = 1; i < Ni; ++i)
                acc += L(0, i) * R(i, 0);
            return acc;
        }

        /** Matrix Output Method.
         * \param s  stream
         * \param m  matrix to print
         * \returns stream after printing matrix
         * placeholder method for printing a matrix.
         * I really need to provide a way to build
         * up boxes of text that stack horizontally
         * so matrices can be printed side by side.
         */
        template<int Nc, int Nr, typename T>
        std::ostream &operator<<(std::ostream &s, Matrix<Nc, Nr, T> const &m) {
            int w = s.width();     // apply width to each element,
            s << std::setw(1) << "[[" << std::setw(w) << m(0, 0);
            for (int ci = 1; ci < Nc; ++ci)
                s << "," << std::setw(w) << m(0, ci);
            for (int ri = 1; ri < Nr; ++ri) {
                s << "],[" << std::setw(w) << m(ri, 0);
                for (int ci = 1; ci < Nc; ++ci)
                    s << "," << std::setw(w) << m(ri, ci);
            }
            return s << "]]";
        }

        /** Column Vector Output Method.
         * \param s  stream
         * \param m  matrix to print
         * \returns stream after printing matrix
         * placeholder method for printing a matrix.
         * I really need to provide a way to build
         * up boxes of text that stack horizontally
         * so matrices can be printed side by side.
         * NOTE: the form "~[...]" is used to emphasize
         * that the vector is the transpose of what
         * has the visual appearance of a row vector.
         */
        template<int Nr, typename T>
        std::ostream &operator<<(std::ostream &s, Matrix<1, Nr, T> const &m) {
            int w = s.width();     // apply width to each element,
            s << std::setw(1) << "~[" << std::setw(w) << m(0, 0);
            for (int ri = 1; ri < Nr; ++ri)
                s << "," << std::setw(w) << m(ri, 0);
            return s << "]";
        }

        /** Row Vector Output Method.
         * \param s  stream
         * \param m  matrix to print
         * \returns stream after printing matrix
         * placeholder method for printing a matrix.
         * I really need to provide a way to build
         * up boxes of text that stack horizontally
         * so matrices can be printed side by side.
         */
        template<int Nc, typename T>
        std::ostream &operator<<(std::ostream &s, Matrix<Nc, 1, T> const &m) {
            int w = s.width();     // apply width to each element,
            s << std::setw(1) << "[" << std::setw(w) << m(0, 0);
            for (int ci = 1; ci < Nc; ++ci)
                s << "," << std::setw(w) << m(0, ci);
            return s << "]";
        }

    }
}

#endif//_matrix_matrix_h
