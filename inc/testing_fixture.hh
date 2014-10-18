#ifndef _testing_fixture_h
#define _testing_fixture_h "testing fixture v0.1" /**< for header vs library matching */

/** \file
* \brief Testing Fixture Interface
*/

#include <string>

namespace Farsyte {
  namespace Testing {

    extern void setlogname(std::string const &name);

    extern int autorun_atexit_rv;

    class TestNames {
    public:
      std::string const sn;
      std::string const tn;

      TestNames(
          std::string const &sname,
          std::string const &tname)
          : sn(sname), tn(tname) {
      }
    };

    typedef std::function<void(Test &)> TestFunc;

    extern TestNames *operator+(TestNames *r, TestFunc f);

#define UT_RV(sn, tn)       static auto __ ## sn ## __ ## tn ## __Regcode
#define UT_ID(sn, tn)       = new Farsyte::Testing::TestNames(#sn,#tn)
#define UT_DOES()           + (Farsyte::Testing::TestFunc) [](Farsyte::Testing::Test &t)
#define UT_CASE(sn, tn)     UT_RV(sn,tn) UT_ID(sn,tn) UT_DOES()

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

#define UT_EXPECT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, break)
#define UT_ASSERT(mf, ov, ev, os, ms)   UT_COND(mf, ov, ev, os, ms, return)

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

#define EXPECT_EX(exp)        UT_EXCEPT(exp, #exp, break)
#define ASSERT_EX(exp)        UT_EXCEPT(exp, #exp, return)

  }
}

#endif//_testing_fixture_h
