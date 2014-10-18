#ifndef _testing_log_h
#define _testing_log_h "testing log v0.1" /**< for header vs library matching */

/** \file
* * \brief Testing Log Interface
*/

#include <iostream>
#include <string>

namespace Farsyte {
    namespace Testing {
        class Suite;

        /** The Log Object
        *
        * The Log object constructor writes XML text to the specified
        * output stream to start a new log file. The destructor
        * writes trailer data to finish the XML element opened at the
        * top. Test programs create a Log object for each file they
        * want to write, and may have several Log file objects open
        * at the same time.
        */
        class Log {
        public:

            std::ostream &out;                ///< Current output stream.

            std::string const name;           ///< Name of the test log.

            Suite *curr;                      ///< Currently active Suite, or NULL if none.

            int suites;                       ///< Cumulative count of Suites.
            int tests;                        ///< Cumulative count of Tests.

            int failed_tests;                 ///< Cumulative count of Tests with at least one FAIL.
            int skipped_tests;                ///< Cumulative count of Tests with at least one SKIP.
            int errored_tests;                ///< Cumulative count of Tests with at least one ERROR.

            int total_fails;                  ///< Cumulative count of all FAIL reports.
            int total_skips;                  ///< Cumulative count of all SKIP reports.
            int total_errors;                 ///< Cumulative count of all ERROR reports.

            /** Log Constructor.
            * \param out - where to send the XML text.
            * \param name - the name of the Log.
            * Writes XML header text to the output stream.
            */
            Log(std::ostream &out, std::string const &name);

            /** Log Destructor.
            * Writes XML trailer text to the output stream.
            */
            ~Log();

            /** Append output text. */
            template<typename T>
            Log &operator<<(T const &t) {
                out << t;
                return *this;
            }

            /** Apply I/O manipulator. */
            Log &operator<<(std::ostream &(*man)(std::ostream &stream)) {
                out << man;
                return *this;
            }
        };

    }
}

#endif//_testing_log_h
