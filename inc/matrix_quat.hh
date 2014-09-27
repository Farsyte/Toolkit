#ifndef _matrix_quat_h
#define _matrix_quat_h "matrix quat v0.1" /**< for header vs library matching */

/** \file
* \brief Matrix Library Exported API
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Matrix library.
*/

#include <iostream>

namespace Farsyte {
    namespace Matrix {

        /** Quat Class.
        *
        * This class implements a representation of
        * a Quaternion, a four-degree-of-freedom
        * hypercomplex number comprising a real scalar
        * part and a complex vector part.
        */
        class Quat
        {
        public:

            /** Quat Default Constructor.
            * This class assures that all Quat objects are initialized
            * to zero when they are constructed, if no initial value is
            * specified via a different constructor.
            */
            Quat();
        };

        /** Stream Output Operation.
        */
        extern std::ostream &operator<<(std::ostream &s, Quat const &q);
    }
}

#endif//_matrix_quat_h
