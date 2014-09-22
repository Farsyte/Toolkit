#ifndef _matrix_matrix_h
/** Header version string. */
#define _matrix_matrix_h "matrix_matrix v0.1"

/** \file
* * \brief Matrix Template
*/

#include <array>

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

        /** Addition Operator for Matrix-based Classes.
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

    }
}

#endif//_matrix_matrix_h
