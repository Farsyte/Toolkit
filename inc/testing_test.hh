#ifndef _testing_test_h
#define _testing_test_h "testing test v0.1" /**< for header vs library matching */

/** \file
* * \brief Testing Test Case Interface
*/

#include <sstream>

namespace Farsyte {
    namespace Testing {

        class Suite;

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
                : public std::ostringstream {
        public:
            /** Test Suite associated with this Test. */
            Suite &ref;

            /** Name of the test case */
            std::string const name;

            /** number of FAIL reports for this test. */
            int fails;

            /** number of SKIP reports for this test. */
            int skips;

            /** number of ERROR reports for this test. */
            int errors;

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

            /** Register a Test PASS.
            * \param cond -- one-line description of passed condition.
            *
            * Mark that a test condition has PASSED. There is no XML output
            * for Bamboo in this case. The purpose of this call is to
            * correctly assocaite any supporting text sent to the Test
            * object with this PASSING condition rather than including it
            * in a subsequent fail, skip, or error.
            */
            void pass(std::string const &cond);

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

            /** Common Test Case: Condition True
            */
            int is_T(int cond, std::string const &msg) {
                if (0 != cond) {
                    pass(msg);
                    return 0;
                } else {
                    fail(msg);
                    return 1;
                }
            }

            /** Common Test Case: Condition True
            */
            int is_F(int cond, std::string const &msg) {
                if (0 == cond) {
                    pass(msg);
                    return 0;
                } else {
                    fail(msg);
                    return 1;
                }
            }

            /** Common Test Case: (obs == exp).
            */
            template<typename T, typename U>
            int eq(T obs, U exp, std::string const &msg) {
                (*this)
                        << "observed:    " << obs << "\n"
                        << "expected: == " << exp << "\n";
                return is_T(obs == exp, msg);
            }

            /** Common Test Case: (obs >= exp).
            */
            template<typename T, typename U>
            int ge(T obs, U exp, std::string const &msg) {
                (*this)
                        << "observed:    " << obs << "\n"
                        << "expected: >= " << exp << "\n";
                return is_T(obs >= exp, msg);
            }
        };

    }
}

#endif//_testing_test_h
