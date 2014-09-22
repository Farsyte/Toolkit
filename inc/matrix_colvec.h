#ifndef _matrix_colvec_h
#define _matrix_colvec_h "matrix colvec v0.1" /**< for header vs library matching */

/** \file
* \brief ColVec Template
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Matrix library.
*/

#include "matrix_matrix.h"

namespace Farsyte {
  namespace Matrix {

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
        : public Matrix<1, Nr, T>
    {

    public:

      /** Typedef for matrix generalization. */
      typedef Matrix<1, Nr, T> MatMe;

      /** Typedef for array containing the data.
      */
      typedef typename MatMe::A A;

    public:

      ColVec ()
          : MatMe ()
      {
      }

      /** Construct a Column Vector from a 2-D Array.
      * \param a  An appropriately shaped object of the C++ array template type.
      * This initializes the Column Vector data to contain values from
      * the corresponding elements of the array provided.
      */
      ColVec (A const &a)
          : MatMe (a)
      {
      }

      /** Duplicate an existing Column Vector.
      * \param c  A column vector to duplicate.
      * Initialize this column vector to be a duplicate of the one provided.
      * \note Can be called with any appropriately dimensioned matrix.
      */
      ColVec (MatMe const &c)
          : MatMe (c)
      {
      }
    };
  }
}

#endif//_matrix_colvec_h
