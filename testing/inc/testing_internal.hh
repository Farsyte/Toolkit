#ifndef _testing_internal_h
#define _testing_internal_h "testing_internal v0.1" /**< for header vs library matching */

/** \file
* \brief Testing Library Internal API
*
* This file provides data types, function prototypes and macro
* definitions for interfaces between parts of this library.
*/

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
