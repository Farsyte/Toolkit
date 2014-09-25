#ifndef _matrix_h
#define _matrix_h "matrix v0.1" /**< for header vs library matching */

/** \file
* \brief Matrix Library Exported API
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Matrix library.
*/

#include "matrix_matrix.hh"
#include "matrix_colvec.hh"
#include "matrix_threevec.hh"

#include <vector>

namespace Farsyte {
    namespace Matrix {

        /** Retrieve "matrix" version strings from library.
        * This method provides access to a list containing
        * the version strings from the headers used to compile
        * the matrix library.
        */
        extern std::vector<std::string> const &matrix_versions();

    }
}

#endif//_matrix_h
