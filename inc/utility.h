#ifndef _utility_h
#define _utility_h "utility v0.1" /**< for header vs library matching */

/** \file
 * \brief Testing Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Testing library.
 */

#include <string>
#include <vector>

namespace Farsyte {
  namespace Utility {

    /** Convert a character into its literal representation.
     * \param ch -- character to be quoted
     *
     * This function returns a string to use to represent
     * the "ch" character in a C literal within either a
     * character or string literal. Oddball characters may
     * use the representation of the DELETE character.
     */
    std::string literal(char ch);

    /** Convert a string into its literal representation (without quotes).
    * \param str -- string to be quoted
    *
    * This function returns a string to be used within a C string
    * literal to represent the value. Sufficiently oddball
    * characters may be replaced by the representation of the
    * DELETE character.
    */
    std::string literal(std::string const &str);

    /** Convert a character into its literal representation (with quotes).
    * \param str -- string to be quoted
    *
    * This function returns a string to be used as a C string
    * literal to represent the value. Sufficiently oddball
    * characters may be replaced by the representation of the
    * DELETE character.
    */
    std::string quoted(std::string const &str);

    /** Retrieve "utility" version strings from library.
    * This method provides access to a list containing
    * the version strings from the headers used to compile
    * the utility library.
     */
    extern std::vector<std::string> const & utility_versions();
  }
}

#endif//_utility_h
