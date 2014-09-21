#include "testing.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Utility::literal;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

/** Get array of lines sent to a string stream.
* \todo move this to a text utility library somewhere?
*/
vector<string> lines (ostringstream &oss)
{
  string str (oss.str ());
  istringstream iss (str);
  string line;
  vector<string> vos;
  while (getline (iss, line))
    vos.push_back (line);
  return vos;
}

/** Templatized comparison utility
* \todo move this to a test utility library somewhere?
*/
template<typename T, typename U>
int test_compare (
    Suite &s,
    string const &title,
    T const &exp,
    U const &obs,
    string const &message)
{
  Test t (s, title);
  return t.eq (obs, exp, message);
}

int test_testing_version (Log &l)
{
  Suite s (l, "Farsyte::Testing::Version");
  Test t (s, "Version Comparison");

  vector<string> ver_list = Farsyte::Testing::testing_versions ();
  size_t min_size = 1;
  size_t ver_size = ver_list.size ();

  return 0
         || t.ge (ver_size, min_size, "version string list too short")
         || t.eq (ver_list[0], string (_testing_h), "master version string mismatch");
}

/** Verify the next entry in a string list is as expected.
*/
int test_testing_log_line (
    Suite &s,
    string const &title,
    vector<string> const &vos,
    unsigned &off,
    string const &exp)
{
  Test t (s, title);

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** if any test fails, do not try remaining tests.
  */

  int ec = 0
           || t.ge (vos.size (), off, "XML Text generated")
           || t.eq (vos[off], exp, "XML Text matches");

  if (ec < 1)
    ++off;

  return ec;
}

/** Verify that we are at the end of the string list.
*/
int test_testing_log_eof (
    Suite &s,
    string const &title,
    vector<string> const &vos,
    unsigned off)
{
  Test t (s, title);

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** if any test fails, do not try remaining tests.
  */

  return t.eq (off, vos.size (), "XML End of File");
}

/** Test that Log objects have correct initial state.
*/
int test_testing_log_init (Suite &s)
{
  ostringstream oss;
  Log tl (oss, "Log Tester Log Name");

  Test t (s, "Initial state of Log");

  return 0
         + t.eq (&tl.out, &oss, "output stream reference")
         + t.eq (tl.curr, (void *) 0, "initial Suite link")
         + t.eq (tl.suites, 0, "initial Suite count")
         + t.eq (tl.tests, 0, "initial Test count");
}

int test_testing_log_out (Suite &s)
{

  ostringstream oss;

  {
    Log tl (oss, "Log Tester Log Name");
  }

  vector<string> vos (lines (oss));
  unsigned off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
         || test_testing_log_line (s, "XML Header", vos, off, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
         || test_testing_log_line (s, "top of testsuites entity", vos, off, "<testsuites name=\"Log Tester Log Name\">")
         || test_testing_log_line (s, "end of testsuites entity", vos, off, "</testsuites>")
         || test_testing_log_eof (s, "text after end of testsuites", vos, off);

}

int test_testing_log (Log &log)
{
  Suite s (log, "Farsyte::Testing::Log");

  return 0
         || test_testing_log_init (s)
         || test_testing_log_out (s);
}

int test_testing_suite_init (Suite &s)
{
  ostringstream oss;
  int ec = 0;
  Log tl (oss, "Suite Tester Log Name");
  Suite ts (tl, "Suite Tester Suite Name");

  {
    Test t (s, "Initial Suite Primary Bookkeeping");
    ec = ec
         + t.eq (&ts.ref, &tl, "Suite link to Log object")
         + t.eq (tl.curr, &ts, "Log link to Suite object")
         + t.eq (ts.curr, (void *) 0, "Suite link to Test object")
         + t.eq (tl.suites, 1, "Log count of Suite objects")
         + t.eq (ts.tests, 0, "Suite count of Test objects");
  }

  {
    Test t (s, "Initial Suite Result Counters");
    ec = ec
         + t.eq (ts.failed_tests, 0, "suite failed test count")
         + t.eq (ts.skipped_tests, 0, "suite skipped test count")
         + t.eq (ts.errored_tests, 0, "suite errored test count")
         + t.eq (ts.total_fails, 0, "suite failed condition count")
         + t.eq (ts.total_skips, 0, "suite skipped condition count")
         + t.eq (ts.total_errors, 0, "suite total error count");
  }

  {
    Test t (s, "Initial Log Result Counters");
    ec = ec
         + t.eq (tl.failed_tests, 0, "log failed test count")
         + t.eq (tl.skipped_tests, 0, "log skipped test count")
         + t.eq (tl.errored_tests, 0, "log errored test count")
         + t.eq (tl.total_fails, 0, "log failed condition count")
         + t.eq (tl.total_skips, 0, "log skipped condition count")
         + t.eq (tl.total_errors, 0, "log total error count");
  }

  return ec;
}

int test_testing_suite_init2 (Suite &s)
{
  ostringstream oss;
  Log tl (oss, "Suite Tester Log Name");
  Suite (tl, "Suite Tester Suite Name1");
  Suite ts (tl, "Suite Tester Suite Name2");

  Test t (s, "Initialization of Second Suite");

  return 0
         + t.eq (&ts.ref, &tl, "Second Suite links to Log")
         + t.eq (tl.curr, &ts, "Log links to Second Suite")
         + t.eq (ts.curr, (void *) 0, "Second Suite link to Test is NULL")
         + t.eq (tl.suites, 2, "Log count of Suites");
}

int test_testing_suite_ierr (Suite &s)
{
  int ec = 0;
  ostringstream oss;
  Log tl (oss, "Suite Tester Log Name");
  Suite ts1 (tl, "Suite Tester Suite Name 1");

  /*
  ** More complicated test: trying to construct
  ** a new Suite object when one is already
  ** open for that log should trigger an exception.
  */

  Test t (s, "Detect opening a suite with a suite still open");

  try {
    Suite ts2 (tl, "Suite Tester Suite Name 2");
    t.fail ("second suite created without exception");
    ec++;
  }
  catch (Oops &e) {
    t << e << endl;
    t.pass ("Suite nesting properly rejected");
  }

  return ec;
}

int test_testing_suite_out (Suite &s)
{

  ostringstream oss;

  Log tl (oss, "Suite Tester Log");

  oss.str ("");

  // Create, then immeidately discard a temporary suite:
  // we just want to see the net addition to the log.
  (void) Suite (tl, "Suite Tester Suite Name");

  vector<string> vos (lines (oss));
  unsigned off = 0;

  Test t (s, "XML output by Suite");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
         || t.ge (vos.size (), 2, "long enough")
         || t.eq (vos[0], "  <testsuite name=\"Suite Tester Suite Name\">", "add <testsuite>")
         || t.eq (vos[1], "  </testsuite>", "Add </testsuite>")
         || t.eq (vos.size (), 2, "no extra text");
}

int test_testing_suite (Log &log)
{
  Suite s (log, "Farsyte::Testing::Suite");
  return 0
         || test_testing_suite_init (s)
         || test_testing_suite_init2 (s)
         || test_testing_suite_ierr (s)
         || test_testing_suite_out (s);
}

int test_testing_test_ierr (Suite &s)
{
  int ec = 0;
  ostringstream oss;
  Log tl (oss, "Test Tester Log Name");
  Suite ts (tl, "Test Tester Suite Name");
  Test tc1 (ts, "Test Tester Test Name 1");

  /*
  ** More complicated test: trying to construct
  ** a new Test object when one is already
  ** open for that log should trigger an exception.
  */

  Test t (s, "Detect opening a test with a test still open");

  try {
    {
      Test tc2 (ts, "Test Tester Test Name 2");
      t.fail ("second test created without exception");
      ec++;
    }
  }
  catch (Oops &e) {
    t << e << endl;
    t.pass ("prevented nesting Test objects");
  }

  return ec;
}

int test_testing_test_init (Suite &s)
{
  ostringstream oss;
  Log tl (oss, "Test Tester Log Name");
  Suite ts (tl, "Test Tester Suite Name");
  Test tc (ts, "Test Tester Test Name");

  Test t (s, "Test object initialization");

  return 0
         + t.eq (&tc.ref, &ts, "Test link to Suite object")
         + t.eq (ts.curr, &tc, "Suite link to Test object")
         + t.eq (tl.tests, 1, "Log count of tests incremented")
         + t.eq (ts.tests, 1, "Suite count of tests incremented")
         + t.eq (tc.fails, 0, "Test count or condition FAILs clear")
         + t.eq (tc.skips, 0, "Test count of condition SKIPs clear")
         + t.eq (tc.errors, 0, "Test count of testing ERROSs clear");
}

int test_testing_test_init2 (Suite &s)
{
  ostringstream oss;
  Log tl (oss, "Test Tester Log Name");
  Suite ts (tl, "Test Tester Suite Name");
  Test (ts, "Test Tester Test Name 1");
  Test tc (ts, "Test Tester Test Name 2");

  Test t (s, "Second Test Object Init");

  return 0
         + t.eq (&tc.ref, &ts, "Test link to Suite")
         + t.eq (ts.curr, &tc, "Suite link to Test")
         + t.eq (tl.tests, 2, "Log counter of Tests")
         + t.eq (ts.tests, 2, "Suite counter of Tests")
         + t.eq (tc.fails, 0, "Test counter of FAILs")
         + t.eq (tc.skips, 0, "Test counter of SKIPs")
         + t.eq (tc.errors, 0, "Test counter of ERRORs");
}

int test_testing_test_init4 (Suite &s)
{
  ostringstream oss;
  Log tl (oss, "Test Tester Log Name");
  {
    Suite ts (tl, "Test Tester Suite Name 1");
    Test (ts, "Test Tester Test Name 1");
    Test (ts, "Test Tester Test Name 2");
  }
  Suite ts (tl, "Test Tester Suite Name 2");
  Test (ts, "Test Tester Test Name 1");
  Test tc (ts, "Test Tester Test Name 2");

  Test t (s, "Multi-suite Multi-test init check");

  return 0
         + t.eq (&tc.ref, &ts, "Test link to Suite")
         + t.eq (ts.curr, &tc, "Suite link to Test")
         + t.eq (tl.tests, 4, "Log test counter")
         + t.eq (ts.tests, 2, "Suite test counter")
         + t.eq (tc.fails, 0, "Test counter of FAILs")
         + t.eq (tc.skips, 0, "Test counter of SKIPs")
         + t.eq (tc.errors, 0, "Test counter of ERRORs");
}

int test_testing_test_obj (Suite &s)
{
  ostringstream oss;

  Log tl (oss, "Test Tester Log");
  Suite ts (tl, "Test Tester Suite Name");

  oss.str ("");

  // Create and immediately destroy a Test object:
  // all we want is the net effect on the Log stream.

  (void) Test (ts, "Test Tester Test Name");

  vector<string> vos (lines (oss));
  unsigned off = 0;

  Test t (s, "XML output from Test object");
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
         || t.ge (vos.size (), 2, "enough XML output.")
         || t.eq (vos[0], "    <testcase name=\"Test Tester Test Name\">", "<testcase>")
         || t.eq (vos[1], "    </testcase>", "</testcase>")
         || t.eq (vos.size (), 2, "no extra XML output.");
}

int test_testing_test_fail (Suite &s)
{

  ostringstream oss;

  Log tl (oss, "Fail Tester Log");
  Suite ts (tl, "Fail Tester Suite Name");
  Test tc (ts, "Fail Tester Test Name");

  tc.fail ("Fail Tester Condition Name (before clear)");
  oss.str ("");
  tc.fail ("Fail Tester Condition Name");

  vector<string> vos (lines (oss));

  int ec = 0;

  {
    Test t (s, "XML output from Test::fail()");
    ec = ec
         || t.ge (vos.size (), 2, "enough XML output")
         || t.eq (vos[0], "      <failure message=\"Fail Tester Condition Name\">", "<failure>")
         || t.eq (vos[1], "      </failure>", "</failure>")
         || t.eq (vos.size (), 2, "not too much XML output");
  }
  {
    Test t (s, "Bookkeeping update from Test::fail()");
    ec = ec
         + t.eq (tc.fails, 2, "Test FAILs counter")
         + t.eq (tc.skips, 0, "Test SKIPs counter")
         + t.eq (tc.errors, 0, "Test ERRORs counter")

         + t.eq (ts.failed_tests, 1, "Suite count of Test FAILs")
         + t.eq (ts.skipped_tests, 0, "Suite count of Test SKIPs")
         + t.eq (ts.errored_tests, 0, "Suite count of Test ERRORs")

         + t.eq (ts.total_fails, 2, "Suite cont of Cond FAILs")
         + t.eq (ts.total_skips, 0, "Suite count of Cond SKIPs")
         + t.eq (ts.total_errors, 0, "Suite count of Cond ERRORs")

         + t.eq (tl.failed_tests, 1, "Log count of Test FAILs")
         + t.eq (tl.skipped_tests, 0, "Log count of Test FAILs")
         + t.eq (tl.errored_tests, 0, "Log count of Test ERRORs")

         + t.eq (tl.total_fails, 2, "Log count of Cond FAILs")
         + t.eq (tl.total_skips, 0, "Log count of Cond SKIPs")
         + t.eq (tl.total_errors, 0, "Log count of Cond ERRORs");
  }

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return ec;
}

int test_testing_test_text (Suite &s)
{

  static const vector<string> exp = {
      Farsyte::Utility::quoted ("      <failure message=\"Text Tester Condition Name\">"),
      Farsyte::Utility::quoted ("Text Tester Detail Line #1"),
      Farsyte::Utility::quoted ("Text Tester Detail Line #2"),
      Farsyte::Utility::quoted ("Text Tester Detail Line #3"),
      Farsyte::Utility::quoted ("      </failure>"),
  };
  static const vector<string> msg = {
      "open failure entity",
      "evidence line 1",
      "evidence line 2",
      "evidence line 3",
      "close failure entity"
  };

  ostringstream oss;

  Log tl (oss, "Text Tester Log");
  Suite ts (tl, "Text Tester Suite Name");
  Test tc (ts, "Text Tester Test Name");

  oss.str ("");

  tc << "Text Tester Detail Line #1" << endl;
  tc << "Text Tester Detail Line #2\n";
  tc << "Text Tester Detail Line #3";

  tc.fail ("Text Tester Condition Name");

  vector<string> vos (lines (oss));

  Test t (s, "XML output of Test::fail evidence");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
         || t.ge (vos.size (), 5, "enough XML output.")
         || t.eq (Farsyte::Utility::quoted (vos[0]), exp[0], msg[0])
         || t.eq (Farsyte::Utility::quoted (vos[1]), exp[1], msg[1])
         || t.eq (Farsyte::Utility::quoted (vos[2]), exp[2], msg[2])
         || t.eq (Farsyte::Utility::quoted (vos[3]), exp[3], msg[3])
         || t.eq (Farsyte::Utility::quoted (vos[4]), exp[4], msg[4])
         || t.eq (vos.size (), 5, "no extra XML output.");
}

int test_testing_test_skip (Suite &s)
{
  static const vector<string> exp = {
      Farsyte::Utility::quoted ("      <skipped message=\"Skip Tester Condition Name\">"),
      Farsyte::Utility::quoted ("Skip Tester Detail Line #1"),
      Farsyte::Utility::quoted ("Skip Tester Detail Line #2"),
      Farsyte::Utility::quoted ("Skip Tester Detail Line #3"),
      Farsyte::Utility::quoted ("      </skipped>"),
  };
  static const vector<string> msg = {
      "open skipped entity",
      "evidence line 1",
      "evidence line 2",
      "evidence line 3",
      "close skipped entity"
  };

  ostringstream oss;

  Log tl (oss, "Skip Tester Log");
  Suite ts (tl, "Skip Tester Suite Name");
  Test tc (ts, "Skip Tester Test Name");

  tc.skip ("Skip Tester Condition Name (before clear)");
  oss.str ("");
  tc << "Skip Tester Detail Line #1" << endl;
  tc << "Skip Tester Detail Line #2\n";
  tc << "Skip Tester Detail Line #3";
  tc.skip ("Skip Tester Condition Name");

  vector<string> vos (lines (oss));

  int ec = 0;

  {
    Test t (s, "XML output from Test::skip with evidence");
    ec = ec
         + t.ge (vos.size (), 5, "Enough XML output")
         + t.eq (Farsyte::Utility::quoted (vos[0]), exp[0], msg[0])
         + t.eq (Farsyte::Utility::quoted (vos[1]), exp[1], msg[1])
         + t.eq (Farsyte::Utility::quoted (vos[2]), exp[2], msg[2])
         + t.eq (Farsyte::Utility::quoted (vos[3]), exp[3], msg[3])
         + t.eq (Farsyte::Utility::quoted (vos[4]), exp[4], msg[4])
         + t.ge (vos.size (), 5, "Enough XML output");
  }

  {
    Test t (s, "Bookkeeping update from Test::skip");
    ec = ec
         + t.eq (tc.fails, 0, "Test FAILs counter")
         + t.eq (tc.skips, 2, "Test SKIPs counter")
         + t.eq (tc.errors, 0, "Test ERRORs counter")

         + t.eq (ts.failed_tests, 0, "Suite count of Test FAILs")
         + t.eq (ts.skipped_tests, 1, "Suite count of Test SKIPs")
         + t.eq (ts.errored_tests, 0, "Suite count of Test ERRORs")

         + t.eq (ts.total_fails, 0, "Suite cont of Cond FAILs")
         + t.eq (ts.total_skips, 2, "Suite count of Cond SKIPs")
         + t.eq (ts.total_errors, 0, "Suite count of Cond ERRORs")

         + t.eq (tl.failed_tests, 0, "Log count of Test FAILs")
         + t.eq (tl.skipped_tests, 1, "Log count of Test FAILs")
         + t.eq (tl.errored_tests, 0, "Log count of Test ERRORs")

         + t.eq (tl.total_fails, 0, "Log count of Cond FAILs")
         + t.eq (tl.total_skips, 2, "Log count of Cond SKIPs")
         + t.eq (tl.total_errors, 0, "Log count of Cond ERRORs");
  }
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return ec;

}

int test_testing_test_error (Suite &s)
{
  static const vector<string> exp = {
      Farsyte::Utility::quoted ("      <error message=\"Error Tester Condition Name\">"),
      Farsyte::Utility::quoted ("Error Tester Detail Line #1"),
      Farsyte::Utility::quoted ("Error Tester Detail Line #2"),
      Farsyte::Utility::quoted ("Error Tester Detail Line #3"),
      Farsyte::Utility::quoted ("      </error>"),
  };
  static const vector<string> msg = {
      "open error entity",
      "evidence line 1",
      "evidence line 2",
      "evidence line 3",
      "close error entity"
  };

  ostringstream oss;

  Log tl (oss, "Error Tester Log");
  Suite ts (tl, "Error Tester Suite Name");
  Test tc (ts, "Error Tester Test Name");

  tc.error ("Error Tester Condition Name (before clear)");
  oss.str ("");
  tc << "Error Tester Detail Line #1" << endl;
  tc << "Error Tester Detail Line #2\n";
  tc << "Error Tester Detail Line #3";
  tc.error ("Error Tester Condition Name");

  vector<string> vos (lines (oss));

  int ec = 0;

  {
    Test t (s, "XML output from Test::error");
    ec = ec
         || t.ge (vos.size (), 5, "Enough XML output.")
         || t.eq (Farsyte::Utility::quoted (vos[0]), exp[0], msg[0])
         || t.eq (Farsyte::Utility::quoted (vos[1]), exp[1], msg[1])
         || t.eq (Farsyte::Utility::quoted (vos[2]), exp[2], msg[2])
         || t.eq (Farsyte::Utility::quoted (vos[3]), exp[3], msg[3])
         || t.eq (Farsyte::Utility::quoted (vos[4]), exp[4], msg[4])
         || t.eq (vos.size (), 5, "No extra XML output.");
  }

  {
    Test t (s, "Bookkeeping update from Test::error");
    ec = ec
         + t.eq (tc.fails, 0, "Test FAILs counter")
         + t.eq (tc.skips, 0, "Test SKIPs counter")
         + t.eq (tc.errors, 2, "Test ERRORs counter")

         + t.eq (ts.failed_tests, 0, "Suite count of Test FAILs")
         + t.eq (ts.skipped_tests, 0, "Suite count of Test SKIPs")
         + t.eq (ts.errored_tests, 1, "Suite count of Test ERRORs")

         + t.eq (ts.total_fails, 0, "Suite cont of Cond FAILs")
         + t.eq (ts.total_skips, 0, "Suite count of Cond SKIPs")
         + t.eq (ts.total_errors, 2, "Suite count of Cond ERRORs")

         + t.eq (tl.failed_tests, 0, "Log count of Test FAILs")
         + t.eq (tl.skipped_tests, 0, "Log count of Test FAILs")
         + t.eq (tl.errored_tests, 1, "Log count of Test ERRORs")

         + t.eq (tl.total_fails, 0, "Log count of Cond FAILs")
         + t.eq (tl.total_skips, 0, "Log count of Cond SKIPs")
         + t.eq (tl.total_errors, 2, "Log count of Cond ERRORs");
  }

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return ec;
}

int test_testing_test (Log &log)
{

  Suite s (log, "Farsyte::Testing::Test");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */

  return 0
         + test_testing_test_init (s)
         + test_testing_test_init2 (s)
         + test_testing_test_init4 (s)
         + test_testing_test_ierr (s)
         + test_testing_test_obj (s)
         + test_testing_test_fail (s)
         + test_testing_test_text (s)
         + test_testing_test_skip (s)
         + test_testing_test_error (s);
}

int test_testing (Log &log)
{
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */
  return 0
         + test_testing_version (log)
         + test_testing_log (log)
         + test_testing_suite (log)
         + test_testing_test (log);
}

int main (void)
{

  Log log (cout, "Testing Library");

  int ec = test_testing (log);

  if (ec)
    fprintf (stderr, "%7d FAIL test_testing\n", ec);
  else
    fprintf (stderr, "%7d PASS test_testing\n", ec);

  return 0;
}
