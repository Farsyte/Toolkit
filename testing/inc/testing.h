#ifndef _testing_h
#define _testing_h

/** \file
 * \brief Testing Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Testing library.
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace Farsyte {
    namespace Testing {

        class Log;
        class Suite;
        class Test;
        class Oops;

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

            /** Current output stream. */
            std::ostream & out;

            /** Currently active Suite, or NULL if none. */
            Suite *curr;

            /** Cumulative count of Suites. */
            size_t suites;

            /** Cumulative count of Tests. */
            size_t tests;

            /** Cumulative count of Tests with at least one FAIL. */
            size_t failed_tests;

            /** Cumulative count of Tests with at least one SKIP. */
            size_t skipped_tests;

            /** Cumulative count of Tests with at least one ERROR. */
            size_t errored_tests;

            /** Cumulative count of all FAIL reports. */
            size_t total_fails;

            /** Cumulative count of all SKIP reports. */
            size_t total_skips;

            /** Cumulative count of all ERROR reports. */
            size_t total_errors;

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
        };

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
        class Suite {
          public:

            /** Test Log associated with this Suite. */
            Log &ref;

            /** Currently active Test, or NULL if none. */
            Test *curr;

            /** Count of tests within this suite. */
            size_t tests;

            /** Cumulative count of Tests with at least one FAIL. */
            size_t failed_tests;

            /** Cumulative count of Tests with at least one SKIP. */
            size_t skipped_tests;

            /** Cumulative count of Tests with at least one ERROR. */
            size_t errored_tests;

            /** Cumulative count of all FAIL reports. */
            size_t total_fails;

            /** Cumulative count of all SKIP reports. */
            size_t total_skips;

            /** Cumulative count of all ERROR reports. */
            size_t total_errors;

            /** Construct a new Suite object.
             * \param ref - Log that contains this Suite.
             * \param name - what to call this Suite.
             * Generates appropriate header text to the XML
             * text output stream to start a new suite.
             * May throw an exception if there is already an
             * existing Suite associated with the specified Log.
             */
            Suite(Log &ref, std::string const &name);

            /** Suite Destructor.
             * Generates an appropriate trailer to the XML text output
             * stream to close the Suite.
             * May throw an exception if it appears that this is not the
             * current Suite associated with the Log.
             */
            ~Suite();
        };

        /** The Test object.
         *
         * Derived from Output String Stream.
         *
         * The Test object constructor writes appropriate opening text
         * to the XML file associatd with the Suite. The destructor
         * writes appropriate text to the XML file to close the XML
         * element corresponding to the test. Methods on Test objects
         * are available for reporting test conditions that are
         * skipped, test conditions that fail, and errors encountered
         * during testing. It is an error to construct a Test object
         * for a Suite that currently has an active Test object. Be
         * sure that each Test object goes out of scope before the
         * next one is constructed.
         *
         * Data sent to this object using the `<<` operator will be
         * formatted appropriately and displayed by Bamboo as
         * supporting text in appropriate reporting conditions.
         */
        class Test 
            : public std::ostringstream
        {
          public:
            /** Test Suite associated with this Test. */
            Suite &ref;

            /** number of FAIL reports for this test. */
            size_t fails;

            /** number of SKIP reports for this test. */
            size_t skips;

            /** number of ERROR reports for this test. */
            size_t errors;

            /** Construct a new Test object.
             * \param ref - Suite that contains this Test.
             * \param name - what to call this Test.
             * Generates appropriate header text to the XML
             * text output stream to start a new Test.
             * May throw an exception if there is already an
             * existing Test associated with the specified Suite.
             */
            Test(Suite &ref, std::string const &name);

            /** Register a Test FAIL.
             * \param cond -- one-line description of failed condition.
             *
             * Sends text to the XML log indicating that a test
             * condition has failed, as described in the parameter
             * string. Any accumulated text sent to the Test object
             * with the C++ `<<` operator will be included in the FAIL
             * object as supporting text.
             */
            void fail(std::string const &cond);

            /** Register a Test SKIP.
             * \param cond -- one-line description of skipped condition.
             *
             * Sends text to the XML log indicating that a test
             * condition has been skipped, as described in the
             * parameter string. Any accumulated text sent to the Test
             * object with the C++ `<<` operator will be included in
             * the SKIP object as supporting text.
             */
            void skip(std::string const &cond);

            /** Register a Test ERROR.
             * \param cond -- one-line description of the error.
             *
             * Sends text to the XML log indicating that a test has
             * encountered a testing error, as described in the
             * parameter string. Any accumulated text sent to the Test
             * object with the C++ `<<` operator will be included in
             * the ERROR object as supporting text.
             */
            void error(std::string const &cond);

            /** Suite Destructor.
             * Generates an appropriate trailer to the XML text output
             * stream to close the Test.
             * May throw an exception if it appears that this is not the
             * current Test associated with the Suite.
             *
             * Any text sent to the Test object using the C++ `<<`
             * operator that was not used in a FAIL, SKIP, or ERROR
             * report will be attached to the test as supporting text.
             */
            ~Test();
        };

        /** The Oops Object.
         *
         * Base class for Exception heirarchy
         * for the Testing library.
         * Errors in the Testing library or in
         * the way test code uses the testing library
         * MAY be reported by throwing an object of
         * a class derived from Oops.
         */
        class Oops {
          public:
            std::string         file;
            int                 line;
            std::string         cond;
            mutable bool        pend;

            /** Create a new Oops object.
             * \param f - source file name.
             * \param l - source line number.
             * \param c - condition that was violated.
             */
            Oops(
                std::string     f,
                int             l,
                std::string     c);

            /** Print exception details to output stream.
             *
             * This method produces all available details
             * from this exception object onto the specified
             * output stream (and marks the object as having
             * been printed).
             */
            virtual std::ostream& print(std::ostream&s) const;

            /** Cancel exception printing.
             *
             * This method simply marks the object as having
             * been printed, without the overhead of actually
             * printing the details.
             */
            virtual void cancel() const;

            /** Object Destructor.
             *
             * If the object has not been printed (or cancelled),
             * prints the exception details to the standard error
             * output. All resources owned by the object are released.
             */
            virtual ~Oops();
        };
    }
}

extern std::ostream& operator<< (std::ostream&s, Farsyte::Testing::Oops const &f);

#endif//_testing_h
