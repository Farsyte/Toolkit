#ifndef _simple_h
#define _simple_h "simple v0.1" /**< for header vs library matching */

/** \file
 * \brief Simple Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Simple library.
 */

#include "simple_base.hh"
#include "simple_col.hh"
#include "simple_row.hh"
#include "simple_mat.hh"
#include "simple_quat.hh"

#include <vector>
#include <string>

namespace Farsyte {
    namespace Simple {

        /** Retrieve "simple" version strings from library.
         * This method provides access to a list containing
         * the version strings from the headers used to compile
         * the simple library.
         */
        extern const char ** simple_versions();

    }
}

#endif//_simple_h
