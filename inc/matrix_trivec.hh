#ifndef _matrix_trivec_h
#define _matrix_trivec_h "matrix trivec v0.1" /**< for header vs library matching */

/** \file
* \brief Matrix Library Exported API
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Matrix library.
*/

#include "matrix_colvec.hh"

namespace Farsyte {
    namespace Matrix {
        /** TriVec Class.
        *
        * This class implements a representation of
        * a TriVec (more precisely a change in
        * position), expressed as a column vector
        * of three double precision components.
        */
        class TriVec
                : public ColVec<3, double> {
        protected:
            /** Typedef for ColVec generalization */
            typedef ColVec<3, double> ColMe;

            /** Typedef for Matrix generalization. */
            typedef ColMe::MatMe MatMe;

            /** Typedef for array containing the data.
            */
            typedef typename ColMe::A A;

        public:

            /** TriVec Default Constructor.
            * This class assures that all TriVec objects are initialized
            * to zero when they are constructed, if no initial value is
            * specified via a different constructor.
            */
            TriVec();

            /** TriVec Constructor for Given Coefficients.
            * \param x  X coefficient for position.
            * \param y  Y coefficient for position.
            * \param z  Z coefficient for position.
            * Initializes this position to contain the specified
            * coefficients for location along each of the three axes.
            */
            TriVec(double x, double y, double z);

            /** Duplicate Constructor for TriVec.
            * \param p  TriVec to duplicate.
            * Initializes this position to contain a duplicate of the provided position.
            * \note Can be called with any appropriately dimensioned matrix.
            */
            TriVec(MatMe const &p);

        };

        /** Cross-Product operation.
        * \param L  First operand for product.
        * \param R  Second operand for product.
        * \returns the cross product of the two vectors.
        */
        extern TriVec cross(
                Matrix<1, 3, double> const &L,
                Matrix<1, 3, double> const &R);

        /** Stream Output Operation.
        */
        extern std::ostream &operator<<(std::ostream &s, TriVec const &v);
    }
}

#endif//_matrix_trivec_h
