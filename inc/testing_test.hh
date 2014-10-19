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

            /** Get (and clear) accumulated output. */
            std::string drain() {
                std::string s = oss.str();
                oss.str("");
                return s;
            }

            /** Append output text. */
            template<typename T>
            Test &operator<<(T const &t) {
                oss << t;
                return *this;
            }

            /** Apply I/O manipulator. */
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
            /* the old way to do things */

            
            /** Common Test Case: Condition True
             */
            [[deprecated]] 
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
            [[deprecated]]
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
            [[deprecated]]
            int eq(T obs, U exp, std::string const &msg) {
                (*this)
                    << "observed:    " << obs << "\n"
                    << "expected: == " << exp << "\n";
                return is_T(obs == exp, msg);
            }

            /** Common Test Case: (obs >= exp).
             */
            template<typename T, typename U>
            [[deprecated]]
            int ge(T obs, U exp, std::string const &msg) {
                (*this)
                    << "observed:    " << obs << "\n"
                    << "expected: >= " << exp << "\n";
                return is_T(obs >= exp, msg);
            }



            /* -- ================================================================ -- */

            /* the new way to do things */

            int check(bool ok, std::string const &msg) __attribute__ ((unused)) {
                if (ok)
                    return pass(msg), 0;
                else
                    return fail(msg), 1;
            }

            template<typename T, typename U>
            int check_op(
                T const &ov,
                U const &ev,
                bool ok,
                std::string const &op,
                std::string const &msg) __attribute__ ((unused)) {

                auto w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << op << " "
                    << std::setw((int) w) << ev << std::endl;

                return check(ok, msg);
            }

            template<typename T>
            int check_op(
                T const &ov,
                T const &ev,
                bool ok,
                std::string const &op,
                std::string const &msg) __attribute__ ((unused)) {

                auto w = oss.width();

                oss << std::setw(1);

                oss << "observed: "
                    << std::setw(7) << " " << " "
                    << std::setw((int) w) << ov << std::endl;

                oss << "expected: "
                    << std::setw(7) << op << " "
                    << std::setw((int) w) << ev << std::endl;

                return check(ok, msg);
            }

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

            DECL_CHECK_OP(eq, ==)

#define EXPECT_EQ(obs, exp)        UT_EXPECT(check_eq,obs,exp,"==",#obs " == " #exp)
#define ASSERT_EQ(obs, exp)        UT_ASSERT(check_eq,obs,exp,"==",#obs " == " #exp)

#define EXPECT_Null(obs)           UT_EXPECT(check_eq,obs,(void*)0,"==",#obs " == nullptr")
#define ASSERT_Null(obs)           UT_ASSERT(check_eq,obs,(void*)0,"==",#obs " == nullptr")

            DECL_CHECK_OP(ne, !=)

#define EXPECT_NE(obs, exp)        UT_EXPECT(check_ne,obs,exp,"!=",#obs " != " #exp)
#define ASSERT_NE(obs, exp)        UT_ASSERT(check_ne,obs,exp,"!=",#obs " != " #exp)

#define EXPECT_NotNull(obs)        UT_EXPECT(check_ne,obs,(void*)0,"!=",#obs " != nullptr")
#define ASSERT_NotNull(obs)        UT_ASSERT(check_ne,obs,(void*)0,"!=",#obs " != nullptr")

            DECL_CHECK_OP(ge, >=)

#define EXPECT_GE(obs, exp)        UT_EXPECT(check_ge,obs,exp,">=",#obs " >= " #exp)
#define ASSERT_GE(obs, exp)        UT_ASSERT(check_ge,obs,exp,">=",#obs " >= " #exp)

        };
    }
}

#endif//_testing_test_h
