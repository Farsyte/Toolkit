#ifndef _testing_fixture_h
#define _testing_fixture_h "testing fixture v0.1" /**< for header vs library matching */

/** \file
* \brief Testing Fixture Interface
*/

#include <string>

namespace Farsyte {
  namespace Testing {

    /** Change the base name to use for the output log file.
     */
    extern void setlogname(std::string const &name);

    /** Result of the automatic atexit() call.
     */
    extern int autorun_atexit_rv;

    /** Collector for Unit Test Fixture Names.
     */
    class TestNames {
    public:
      /** Storage for the name for the test suite. */
      std::string const sn;

      /** Storage for the name for the test case. */
      std::string const tn;

      /** Construct a new Test names object.
       * \param sname name for the test suite
       * \param tname name for the test case
       */
      TestNames(
          std::string const &sname,
          std::string const &tname)
          : sn(sname), tn(tname) {
      }
    };

    /** Data type expected for test bodies.
     */
    typedef std::function<void(Test &)> TestFunc;

    /** Combine test names and a body (register the test case).
     */
    extern TestNames *operator+(TestNames *r, TestFunc f);

/** Support Macro: declare storage needed by UT_CASE.
 */
#define UT_RV(sn, tn)       static auto __ ## sn ## __ ## tn ## __Regcode

/** Support Macro: Dynamic Allocation of TestNames for UT_CASE.
 */
#define UT_ID(sn, tn)       = new Farsyte::Testing::TestNames(#sn,#tn)

/** Support Macro: Append TestBody for UT_CASE.
 */
#define UT_DOES()           + (Farsyte::Testing::TestFunc) [](Farsyte::Testing::Test &t)

/** Introduce a Test Case.
 */
#define UT_CASE(sn, tn)     UT_RV(sn,tn) UT_ID(sn,tn) UT_DOES()

/** Commom code for checking a Test Condition.
 */
#define UT_COND(mf, ov, ev, os, ms, onfail)                     \
      do {                                                      \
        bool evaluating = false;                                \
        try {                                                   \
          evaluating = true;                                    \
          auto ovv = (ov);                                      \
          evaluating = false;                                   \
          if (t.mf(ovv, ev, os, ms))                            \
            onfail;                                             \
        }                                                       \
        catch (Farsyte::Testing::Oops &e) {                     \
          t << "exception from ";                               \
          if (evaluating)                                       \
            t << os;                                            \
          else                                                  \
            t << "condition check code";                        \
          t << ":\n" << e << std::endl;                         \
          t.fail("exception thrown");                           \
          onfail;                                               \
        }                                                       \
      } while (0)

/** Check condition; indicate failure if not met.
 */
#define UT_EXPECT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, break)

/** Check condition: fail and return from test if not met.
 */
#define UT_ASSERT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, return)

/** Common code for testing a Thrown Exception.
 */
#define UT_EXCEPT(exp, str, onfail)                             \
      do {                                                      \
        bool evaluating = false;                                \
        try {                                                   \
          evaluating = true;                                    \
          (void) (exp);                                         \
          evaluating = false;                                   \
          t << "Did not observe"                                \
              << " expected exception from\n"                   \
              << "  " << str << std::endl;                      \
          t.fail("Did not see expected exception");             \
          onfail;                                               \
        }                                                       \
        catch (Farsyte::Testing::Oops &e) {                     \
          if (evaluating) {                                     \
            t << "Observed"                                     \
                << " expected exception\n"                      \
                << "  " << e << "\n"                            \
                << "from\n"                                     \
                << "  " << str << std::endl;                    \
            t.pass("saw expected exception");                   \
          } else {                                              \
            t << "Did not observe"                              \
                << " expected exception from\n"                 \
                << "  " << str << "\n"                          \
                << "but DID get an exception after:\n"          \
                << e << std::endl;                              \
            t.fail("Did not see expected exception");           \
            onfail;                                             \
          }                                                     \
        }                                                       \
      } while (0)

/** Expect an exception, indicate failure if not observed.
 */
#define EXPECT_EX(exp)        UT_EXCEPT(exp, #exp, break)

/** Expect an exception, fail and return from test if not observed.
 */
#define ASSERT_EX(exp)        UT_EXCEPT(exp, #exp, return)

  }
}

#endif//_testing_fixture_h
