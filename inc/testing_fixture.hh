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


    /** Data type expected for test bodies.
     */
    typedef void (*TestFunc)(Farsyte::Testing::Test &t);

    extern int ut_reg(
      std::string const &sname,
      std::string const &tname,
      TestFunc f);

    /* Test Case Name function
     */
#define UT_CN(pre,sn,tn)	UT_CASE__ ## pre ## __ ## sn ## __ ## tn

#define UT_CASE(sn,tn)                                          \
    static void UT_CN(func,sn,tn)(Farsyte::Testing::Test &t);   \
    static int  UT_CN(regc,sn,tn) =                             \
      Farsyte::Testing::ut_reg(#sn,#tn,UT_CN(func,sn,tn));      \
    static void UT_CN(func,sn,tn)(Farsyte::Testing::Test &t)

/** Common code for checking a Test Condition.
 */
#define UT_COND(mf, ov, ev, os, ms, onfail)     \
    do {                                        \
      try {                                     \
        if (t.mf((ov), ev, os, ms))             \
          onfail;                               \
      }                                         \
      catch (Farsyte::Testing::Oops &e) {       \
        t << "exception from ";                 \
        t << os;                                \
        t << ":\n" << e << std::endl;           \
        t.fail("exception thrown");             \
        onfail;                                 \
      }                                         \
    } while (0)

/** Check condition; indicate failure if not met.
 */
#define UT_EXPECT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, break)

/** Check condition: fail and return from test if not met.
 */
#define UT_ASSERT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, return)

/** Common code for testing a Thrown Exception.
 */
#define UT_EXCEPT(exp, str, onfail)             \
    do {                                        \
    try {                                       \
    (void) (exp);                               \
    t << "Did not observe"                      \
    << " expected exception from\n"             \
    << "  " << str << std::endl;                \
    t.fail("Did not see expected exception");   \
    onfail;                                     \
  }                                             \
    catch (Farsyte::Testing::Oops &e) {         \
    t << "Observed"                             \
    << " expected exception\n"                  \
    << "  " << e << "\n"                        \
    << "from\n"                                 \
    << "  " << str                              \
    << std::endl;                               \
    t.pass("saw expected exception");           \
  }                                             \
  } while (0)

/** Expect an exception, indicate failure if not observed.
 */
#define EXPECT_EX(exp)        UT_EXCEPT(exp, #exp, break)

/** Expect an exception, fail and return from test if not observed.
 */
#define ASSERT_EX(exp)        UT_EXCEPT(exp, #exp, return)

/** Commom code for checking a Test Condition.
 */
#define UT_COND3(mf, ov, ev1, ev2, os, ms, onfail)      \
    do {                                                \
      try {                                             \
        if (t.mf((ov), ev1, ev2, ms))                   \
          onfail;                                       \
      }                                                 \
      catch (Farsyte::Testing::Oops &e) {               \
        t << "exception from ";                         \
        t << os;                                        \
        t << ":\n" << e << std::endl;                   \
        t.fail("exception thrown");                     \
        onfail;                                         \
      }                                                 \
    } while (0)

/** Check condition; indicate failure if condition check t.mf() fails
 */
#define UT_EXPECT3(mf, ov, ev1, ev2, ms)   UT_COND3(mf, ov, ev1, ev2, #ov, ms, break)

/** Check condition: fail and return from test if condition check t.mf() fails
 */
#define UT_ASSERT3(mf, ov, ev1, ev2, ms)   UT_COND3(mf, ov, ev1, ev2, #ov, ms, return)


  }
}

#endif//_testing_fixture_h
