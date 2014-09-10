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

        /** Quote a character to be included in a C literal.
         * \param ch -- character to be quoted
         * \param qc -- quote character used for literal
         *
         * This function returns a string to use to represent
         * the "ch" character in a C literal, where "qc" is the
         * quote character for the literal.
         *
         * \note Currently returns a zero-length string for
         * characters that are not printable ASCII.
         */
        std::string quote_for_lit(char ch, char qc);

        /** Quote a string to be included in a C literal.
         * \param str -- string to be quoted
         *
         * This function returns a string to use to represent
         * the "str" string in a C literal (in double-quotes).
         *
         * \note Currently discards all contained characters that are
         * not printable ASCII.
         */
        std::string quote_for_lit(std::string const &str);

        /** Return a C literal representing the given string.
         * \param str -- string to be quoted
         *
         * This function returns a string to use to represent
         * the "str" string as C literal (with double-quotes).
         *
         * \note Currently discards all contained characters that are
         * not printable ASCII.
         */
        std::string literal(std::string const &str);

    }
}

#endif//_utility_h
