#ifndef _utility_h
#define _utility_h

/** \file
 * \brief Testing Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Testing library.
 */

#include <string>

namespace Farsyte {
  namespace Utility {

    /** Convert a character into its literal representation.
     * \param ch -- character to be quoted
     *
     * This function returns a string to use to represent
     * the "ch" character in a C literal within either a
     * character or string literal. Oddball characters will
     * use the representation of the DELETE character.
     */
    std::string literal(char ch);

    /** Convert a character into its literal representation.
     * \param str -- string to be quoted
     *
     * This function returns a string to be used within a C string
     * literal to represent the value. Sufficiently oddball
     * characters will be replaced by the representation of the
     * DELETE character.
     */
    std::string literal(std::string const &str);

  }
}

#endif//_utility_h
