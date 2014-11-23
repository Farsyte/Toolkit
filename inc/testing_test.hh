#ifndef _testing_test_h
#define _testing_test_h "testing test v0.1" /**< for header vs library matching */

/** \file
 * \brief Testing Test Case Interface
 */

#include "testing_oops.hh"

#include <iostream>
#include <sstream>
#include <iomanip>

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
        class Test {
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

            /** Where to accumulate the output text. */
            std::ostringstream oss;

            /** Get (and clear) accumulated output. 
             * \returns a string containing the test output.
             */
            std::string drain() {
                std::string s = oss.str();
                oss.str("");
                return s;
            }

            /** Append output text.
             * \param t value to print to the test log.
             * \returns this test object for further operations.
             */
            template<typename T>
            Test &operator<<(T const &t) {
                oss << t;
                return *this;
            }

            /** Apply I/O manipulator.
             * \param man manipulator to apply to the log stream.
             * \returns this test object for further operations.
             */
            Test &operator<<(std::ostream &(*man)(std::ostream &stream)) {
                oss << man;
                return *this;
            }

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

            /* -- ================================================================ -- */

            /** Support code for logging a condition check result.
             * \param ok true if the condition passed, false if it failed.
             * \param msg message string to associate with the condition
             * \returns zero if the condition passed, nonzero if it failed.
             */
            int check(bool ok, std::string const &msg) __attribute__ ((unused)) {
                if (ok)
                    return pass(msg), 0;
                else
                    return fail(msg), 1;
            }

            /** Support Template for performing a condition test.
             * \param ov observed value
             * \param ev expected value
             * \param ok result of comparison
             * \param op string describing the compare operation
             * \param msg string to associate with the condition
             * \returns zero if the condition passed, nonzero if it failed.
             * This template is used if the observed and expected
             * value expressions have different types.
             */
            template<typename T, typename U>
            int check_op(
                T const &ov,
                U const &ev,
                bool ok,
                std::string const &op,
                std::string const &msg) __attribute__ ((unused)) {

                int w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << op << " "
                    << std::setw((int) w) << ev << std::endl;

                return check(ok, msg);
            }

            /** Support Template for performing a condition test.
             * \param ov observed value
             * \param ev expected value
             * \param ok result of comparison
             * \param op string describing the compare operation
             * \param msg string to associate with the condition
             * \returns zero if the condition passed, nonzero if it failed.
             * This template is used if the observed and expected
             * value expressions have the same type.
             */
            template<typename T>
            int check_op(
                T const &ov,
                T const &ev,
                bool ok,
                std::string const &op,
                std::string const &msg) __attribute__ ((unused)) {

                int w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << op << " "
                    << std::setw((int) w) << ev << std::endl;

                return check(ok, msg);
            }

/** Support macro: create a a standard condition test method.
 */
#define DECL_CHECK_OP(ID, OP)                   \
            template<typename T, typename U>    \
            int check_ ## ID (                  \
                T const &ov,                    \
                U const &ev,                    \
                std::string const &op,          \
                std::string const &msg)         \
                __attribute__ ((unused))        \
                {                               \
                    return check_op(            \
                        ov, ev, ov OP ev,       \
                        op, msg);               \
                }

/** Standard Equality Check method.
 */
            DECL_CHECK_OP(eq, ==);

/** Declare a failure if the expressions do not compare equal.
 */
#define EXPECT_EQ(obs, exp)        UT_EXPECT(check_eq,obs,exp,"==",#obs " == " #exp)

/** Declare a failure and return if the expressions do not compare equal.
 */
#define ASSERT_EQ(obs, exp)        UT_ASSERT(check_eq,obs,exp,"==",#obs " == " #exp)

/** Declare a failure if the expression is not a null pointer.
 */
#define EXPECT_Null(obs)           UT_EXPECT(check_eq,obs,(void*)0,"==",#obs " == nullptr")

/** Declare a failure and return if the expression is not a null pointer.
 */
#define ASSERT_Null(obs)           UT_ASSERT(check_eq,obs,(void*)0,"==",#obs " == nullptr")

/** Standard Inequality Check method.
 */
            DECL_CHECK_OP(ne, !=);

/** Declare a failure if the expressions do not compare not equal.
 */
#define EXPECT_NE(obs, exp)        UT_EXPECT(check_ne,obs,exp,"!=",#obs " != " #exp)

/** Declare a failure and return if the expressions do not compare not equal.
 */
#define ASSERT_NE(obs, exp)        UT_ASSERT(check_ne,obs,exp,"!=",#obs " != " #exp)

/** Declare a failure if the expressions do not compare not equal.
 */
#define EXPECT_NotNull(obs)        UT_EXPECT(check_ne,obs,(void*)0,"!=",#obs " != nullptr")

/** Declare a failure and return if the expressions do not compare not equal.
 */
#define ASSERT_NotNull(obs)        UT_ASSERT(check_ne,obs,(void*)0,"!=",#obs " != nullptr")

/** Standard Lower Threshold Check method.
 */
            DECL_CHECK_OP(ge, >=);

/** Declare a failure if the first expression does not compare greater than or equal to the second.
 */
#define EXPECT_GE(obs, exp)        UT_EXPECT(check_ge,obs,exp,">=",#obs " >= " #exp)

/** Declare a failure and return if the first expression does not compare greater than or equal to the second.
 */
#define ASSERT_GE(obs, exp)        UT_ASSERT(check_ge,obs,exp,">=",#obs " >= " #exp)

/** Standard Upper Threshold Check method.
 */
            DECL_CHECK_OP(le, <=);

/** Declare a failure if the first expression does not compare less than or equal to the second.
 */
#define EXPECT_LE(obs, exp)        UT_EXPECT(check_le,obs,exp,"<=",#obs " <= " #exp)

/** Declare a failure and return if the first expression does not compare less than or equal to the second.
 */
#define ASSERT_LE(obs, exp)        UT_ASSERT(check_le,obs,exp,"<=",#obs " <= " #exp)

            /* -- Get a good message for range checks -- */

            template<typename T>
            int check_in(
                T const &ov,
                T const &lo,
                T const &hi,
                std::string const &msg) __attribute__ ((unused)) {

                bool ok = ((ov >= lo) && (ov <= hi));

                int w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << "in" << " "
                    << std::setw((int) w) << lo
                    << " ... "
                    << std::setw((int) w) << hi
                    << std::endl;

                return check(ok, msg);
            }

/** Declare a failure if the observed value is not in the inclusive range.
 */
#define EXPECT_IN(obs,lo,hi) UT_EXPECT3(check_in,obs,lo,hi,#lo " ... " #hi)

/** Declare a failure and return if the observed value is not in the inclusive range.
 */
#define ASSERT_IN(obs,lo,hi) UT_ASSERT3(check_in,obs,lo,hi,#lo " ... " #hi)

            /* -- Get a good message for "close" checks -- */

            template<typename T>
            int check_pm(
                T const &ov,
                T const &ev,
                T const &pm,
                std::string const &msg) __attribute__ ((unused)) {

                bool ok = ((ev-ov) <= pm) && ((ov-ev) <= pm);

                int w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << "==" << " "
                    << std::setw((int) w) << ev
                    << " +/- "
                    << std::setw((int) w) << pm
                    << std::endl;

                return check(ok, msg);
            }

/** Declare a failure if the observed value is not near the expected value.
 */
#define EXPECT_PM(obs,exp,pm) UT_EXPECT3(check_pm,obs,exp,pm,#exp " +/- " #pm)

/** Declare a failure and return if the observed value is not near the expected value.
 */
#define ASSERT_PM(obs,exp,pm) UT_ASSERT3(check_pm,obs,exp,pm,#exp " +/- " #pm)

        };
    }
}

#endif//_testing_test_h
