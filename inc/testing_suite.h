#ifndef _testing_suite_h
#define _testing_suite_h "testing suite v0.1" /**< for header vs library matching */

/** \file
* * \brief Testing Suite Interface
*/

#include <string>

namespace Farsyte {
  namespace Testing {

    class Log;

    class Test;

    /** The Suite Object.
    *
    * The Suite object constructor writes appropraite opening
    * text to the XML output stream. The destructor writes
    * appropriate text to the XML stream to close the XML element
    * corresponding to the suite. It is an error to construct a
    * Suite object for a Log that currently has an active Suite
    * object; be sure that each Suite object goes out of scope
    * before the next one is constructed.
    */
    class Suite
    {
    public:

      Log &ref;                 ///< Test Log associated with this Suite.

      std::string const name;   ///< Name of the test suite

      Test *curr;               ///< Currently active Test, or NULL if none.

      int tests;                ///< Count of tests within this suite.

      int failed_tests;         ///< Cumulative count of Tests with at least one FAIL.
      int skipped_tests;        ///< Cumulative count of Tests with at least one SKIP.
      int errored_tests;        ///< Cumulative count of Tests with at least one ERROR.

      int total_fails;          ///< Cumulative count of all FAIL reports.
      int total_skips;          ///< Cumulative count of all SKIP reports.
      int total_errors;         ///< Cumulative count of all ERROR reports.

      /** Construct a new Suite object.
      * \param ref - Log that contains this Suite.
      * \param name - what to call this Suite.
      * Generates appropriate header text to the XML
      * text output stream to start a new suite.
      * May throw an exception if there is already an
      * existing Suite associated with the specified Log.
      */
      Suite (Log &ref, std::string const &name);

      /** Suite Destructor.
      * Generates an appropriate trailer to the XML text output
      * stream to close the Suite.
      * May throw an exception if it appears that this is not the
      * current Suite associated with the Log.
      */
      ~Suite ();
    };

  }
}

#endif//_testing_suite_h
