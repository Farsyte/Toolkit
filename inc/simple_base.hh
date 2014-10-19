#ifndef _simple_base_h
/** Header version string. */
#define _simple_base_h "simple_base v0.1"

/** \file
 * * \brief Base Types for Simple Things
 */

namespace Farsyte {
    namespace Simple {

        /** Base data type for Simple stuff.
         */
        typedef double T;

        /** Common dimension (row count) for Simple stuff.
         */
        static const int Nr = 3;

        /** Common dimension (column count) for Simple stuff.
         */
        static const int Nc = 3;

        /** Standard Row Vector Typedef.
         */
        typedef struct Row R;

        /** Standard Vector Typedef.
         */
        typedef struct Col V;

        /** Standard Matrix Typedef.
         */
        typedef struct Mat M;

        /** Standard Quaternion Typedef.
         */
        typedef struct Quat Q;

    }
}

#endif//_simple_base_h
