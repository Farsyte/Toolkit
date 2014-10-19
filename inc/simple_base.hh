#ifndef _simple_base_h
/** Header version string. */
#define _simple_base_h "simple_base v0.1"

/** \file
 * * \brief Base Types for Simple Things
 */

namespace Farsyte {
    namespace Simple {

        typedef double T;
        static const int Nr = 3;
        static const int Nc = 3;

        struct Col;
        typedef Col V;

    }
}

#endif//_simple_base_h
