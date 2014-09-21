#ifndef _testing_internal_h
#define _testing_internal_h "testing_internal v0.1" /**< for header vs library matching */

/** \file
 * \brief Testing Library Internal API
 *
 * This file provides data types, function prototypes and macro
 * definitions for interfaces between parts of this library.
 */

#include "testing.h"

using namespace Farsyte::Testing;

namespace Farsyte {
  namespace Testing {
    /** Quote a character for XML.
     * \todo move this to an XML utility library somewhere?
     *
     * Given a character, return the XML entity that
     * will cause that character to be displayed.
     * Return the empty string if there is no suitable
     * content to be written to the XML file.
     */
    extern std::string cq(char ch, char qc = 0);

    /** Quote a string for XML.
     * \todo move this to an XML utility library somewhere?
     *
     * Given a string, return a string of XML entities that
     * will cause that string to be displayed.
     * Return the empty string if there is no suitable
     * content to be written to the XML file.
     */
    extern std::string hq(std::string const &str, char qc = 0);

    /** Quote a string value, generating a quoted string.
     * \todo move this to an XML utility library somewhere?
     */
    extern std::string sq(std::string const &str);
  }
}

/** Throw an Oops if a condition is not true.
 * \param cond - actual expression to evaluate
 * \param msg - one line description of failed condition
 */
#define CHECK_OOPS(cond, msg)                   \
  do {                                          \
    if ((cond)) break;                          \
    std::ostringstream oss;                     \
    oss << msg;                                 \
    string str(oss.str());                      \
    throw Oops(__FILE__, __LINE__, str);        \
  } while (0)

#endif//_testing_internal_h
