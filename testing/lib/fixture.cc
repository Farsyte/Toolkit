#include "testing.hh"

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
      TestSuites &slist(Farsyte::Testing::all_tests());
      for (TestSuites::iterator si = slist.begin(); si != slist.end(); ++si) {
        Suite s(l, si->first);
        for (TestCases::iterator ci = si->second.begin(); ci != si->second.end(); ++ci) {
          Test t(s, ci->first);
          for (TestFuncs::iterator fi = ci->second.begin(); fi != ci->second.end(); ++fi) {
            TestFunc fp = *fi;
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

    int ut_reg(
      std::string const &sname,
      std::string const &tname,
      TestFunc f)
    {
      static TestSuites &d(Farsyte::Testing::all_tests());
      d[sname][tname].push_back(f);
      return 1;
    }

  }
}
