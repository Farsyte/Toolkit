#ifndef _testing_internal_h
#define _testing_internal_h

#include "testing.h"

/** \file
 * \brief Testing Library Internal API
 *
 * This file provides data types, function prototypes and macro
 * definitions for interfaces between parts of this library.
 */

namespace Farsyte {
    namespace Testing {
        extern std::string cq(char ch, char qc = 0);
        extern std::string hq(std::string const &str, char qc = 0);
        extern std::string sq(std::string const &str);
    }
}

#define CHECK_OOPS(cond, msg)                   \
    do {                                        \
        if ((cond)) break;                      \
        std::ostringstream oss;                 \
        oss << msg;                             \
        string str(oss.str());                  \
        throw Oops(__FILE__, __LINE__, str);    \
    } while (0)


using namespace Farsyte::Testing;

#endif//_testing_internal_h
