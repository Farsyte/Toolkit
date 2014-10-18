#include "testing.hh"

#if 0

// Need to rebuild this test code
// to run as a client of the test code,
// and observe the results logged to
// the captive output stream.

#include <iomanip>

using std::setw;

template<typename T>
T Factorial(T t) {
  static const T one(1);
  T acc(one);
  while (t > one) {
    acc *= t;
    --t;
  }
  return acc;
}

UT_CASE(Factorial, NegativeInput) {
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_EQ(1, Factorial(-5));
};

UT_CASE(Factorial, PositiveInput) {
  ASSERT_EQ(1, Factorial(1));
  EXPECT_EQ(24, Factorial(4));
  EXPECT_EQ(99, Factorial(5));
};
#endif

#include <fstream>
#include <map>
#include <list>

using std::ostream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::function;
using std::map;
using std::list;


namespace Farsyte {
  namespace Testing {

    static string logname;

    void setlogname(std::string const &name) {
      logname = name;
    }

    typedef list<TestFunc> TestFuncs;
    typedef map<string, TestFuncs> TestCases;
    typedef map<string, TestCases> TestSuites;

    TestSuites &all_tests() {
      static TestSuites *dp = new TestSuites;
      return *dp;
    }

    void run_all_tests(ostream &str, string const &name) {
      Log l(str, name);
      auto &slist(Farsyte::Testing::all_tests());
      for (auto &si : slist) {
        Suite s(l, si.first);
        for (auto &ci : si.second) {
          Test t(s, ci.first);
          for (auto &fp : ci.second) {
            fp(t);
          }
        }
      }
    }

    void autorun() {
      if (logname.empty())
        return run_all_tests(cout, "atexit");
      string name("test_" + logname + "_log.xml");
      ofstream xml(name.c_str());
      run_all_tests(xml, logname);
    }

    int autorun_atexit_rv   __attribute__ ((unused))
        = atexit(autorun);

    TestNames *operator+(TestNames *r, TestFunc f) {
      static TestSuites &d(Farsyte::Testing::all_tests());
      d[r->sn][r->tn].push_back(f);
      return r;
    }

  }
}
