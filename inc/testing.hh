#ifndef _testing_h
#define _testing_h "testing v0.1" /**< for header vs library matching */

/** \file
* \brief Testing Library Exported API
*
* This file provides data types, function prototypes and macro
* definitions for C code using this Testing library.
*/


#include <vector>
#include <iostream>
#include <string>

#include "testing_log.hh"
#include "testing_suite.hh"
#include "testing_test.hh"
#include "testing_oops.hh"
#include "testing_fixture.hh"

namespace Farsyte {
    namespace Testing {

        /** Retrieve "testing" version strings from library.
        * This method provides access to a list containing
        * the version strings from the headers used to compile
        * the testing library.
        */
        extern std::vector<std::string> const &testing_versions();
    }
}

#endif//_testing_h
