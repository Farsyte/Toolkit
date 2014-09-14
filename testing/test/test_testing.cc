#include "testing.h"

using Farsyte::Testing::Log;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Testing::Oops;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <sstream>
using std::istringstream;
using std::ostringstream;

/** Quote a character to go into a string constant.
 * \todo move this to a text utility library somewhere?
 */
string sq(char ch) {

  switch (ch) {
  case '\t': return "\\t";
  case '\n': return "\\n";
  case '"': return "\\\"";
  case '\'': return "\\\'";
  }

  if (ch < 32)
    return "";

  if (ch > 126)
    return "";

  return string(1, ch);
}

/** Quote a string to be a string constant.
 * \todo move this to a text utility library somewhere?
 */
string sq(string const & s) {
  ostringstream       oss;
  oss << '"';
  for (size_t i = 0; i < s.length(); ++i)
    oss << sq(s[i]);
  oss << '"';
  return oss.str();
}

/** Convert an integer into its string representation.
 * \todo move this to a text utility library somewhere?
 */
string itos(int i) {
  ostringstream       oss;
  oss << i;
  return oss.str();
}

/** Get array of lines sent to a string stream.
 * \todo move this to a text utility library somewhere?
 */
vector<string> lines(ostringstream &oss) {
  string              str(oss.str());
  istringstream       iss(str);
  string              line;
  vector<string>      vos;
  while (getline(iss, line))
    vos.push_back(line);
  return vos;
}

/** Templatized comparison utility
 * \todo move this to a test utility library somewhere?
 */
template<typename T, typename U>
int test_compare(
  Suite &s,
  string const &title,
  T const & exp,
  U const & obs,
  string const &message)
{
  Test t(s, title);
  t << "expected: " << exp << endl;
  t << "observed: " << obs << endl;
  if (exp == obs) {
    t.pass(title);
    return 0;
  } else {
    t.fail(message);
    return 1;
  }
}

/** Verify the next entry in a string list is as expected.
 */
int test_testing_log_line(
  Suite &s,
  string const &title,
  vector<string> const &vos,
  unsigned &off,
  string const &exp)
{
  string const sqe(sq(exp));
  Test t(s, title);
  t << "expected: " << sqe << endl;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** if any test fails, do not try remaining tests.
  */

  if (vos.size() <= off) {
    t << "observed: (end of file)" << endl;
    t.fail("XML text: "+sqe);
    return 1;
  }

  string const & obs = vos[off];

  t << "observed: " << sq(obs) << endl;
  if (exp != obs) {
    t.fail("XML text: "+sqe);
    return 1;
  }

  off ++;

  t.pass("XML text: "+sqe);
  return 0;
}

/** Verify that we are at the end of the string list.
 */
int test_testing_log_eof(
  Suite &s,
  string const &title,
  vector<string> const &vos,
  unsigned off)
{
  Test t(s, title);
  t << "expected: output has " << off << " lines." << endl;
  unsigned obs = vos.size();
  t << "observed: output has " << obs << " lines." << endl;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** if any test fails, do not try remaining tests.
  */

  if (obs > off) {
    t.fail("XML end of file");
    return 1;
  }

  if (obs < off) {
    t.fail("XML end of file");
    return 1;
  }

  t.pass("XML end of file");

  return 0;
}

/** Test that Log objects have correct initial state.
 */
int test_testing_log_init(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Log Tester Log Name");

  return 0
    + test_compare(s, "output stream link", (ostream*)&oss, (ostream*)&tl.out,
                   "Log object does not link to output stream")
    + test_compare(s, "log link to suite", tl.curr, (Suite*)0,
                   "Log object has non-NULL suite link")
    + test_compare(s, "log suite count", 0u, tl.suites,
                   "Log object init to non-ZERO suite count")
    + test_compare(s, "log test count", 0u, tl.tests,
                   "Log object init to non-ZERO test count")
    ;
}

int test_testing_log_out(Suite &s) {

  ostringstream               oss;

  {
    Log tl(oss, "Log Tester Log Name");
  }

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

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
    || test_testing_log_eof (s, "text after end of testsuites", vos, off)
    ;

}

int test_testing_log(Log &log) {
  Suite               s(log, "Farsyte::Testing::Log");

  return 0
    || test_testing_log_init(s)
    || test_testing_log_out(s)
    ;
}

int test_testing_suite_init(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Suite Tester Log Name");
  Suite ts(tl, "Suite Tester Suite Name");

  return 0
    + test_compare(s, "suite link to log", &tl, &ts.ref,
                   "Suite object does not link to Log object")
    + test_compare(s, "log link to suite", tl.curr, &ts,
                   "Log object does not link to Suite object")
    + test_compare(s, "suite link to test", ts.curr, (Test*)0,
                   "Suite object has non-NULL test link")
    + test_compare(s, "log suite count", 1u, tl.suites,
                   "Log object not counting suites correctly")
    + test_compare(s, "suite test count", 0u, ts.tests,
                   "Suite object init to non-ZERO test count")

    + test_compare(s, "suite failed test count", 0u, ts.failed_tests,
                   "Suite object init to non-ZERO failed test count")
    + test_compare(s, "suite skipped test count", 0u, ts.skipped_tests,
                   "Suite object init to non-ZERO skipped test count")
    + test_compare(s, "suite errored test count", 0u, ts.errored_tests,
                   "Suite object init to non-ZERO errored test count")

    + test_compare(s, "suite total fail count", 0u, ts.total_fails,
                   "Suite object init to non-ZERO total fail count")
    + test_compare(s, "suite total skip count", 0u, ts.total_skips,
                   "Suite object init to non-ZERO total skip count")
    + test_compare(s, "suite total error count", 0u, ts.total_errors,
                   "Suite object init to non-ZERO total error count")

    + test_compare(s, "log failed test count", 0u, tl.failed_tests,
                   "Log object init to non-ZERO failed test count")
    + test_compare(s, "log skipped test count", 0u, tl.skipped_tests,
                   "Log object init to non-ZERO skipped test count")
    + test_compare(s, "log errored test count", 0u, tl.errored_tests,
                   "Log object init to non-ZERO errored test count")

    + test_compare(s, "log total fail count", 0u, tl.total_fails,
                   "Log object init to non-ZERO total fail count")
    + test_compare(s, "log total skip count", 0u, tl.total_skips,
                   "Log object init to non-ZERO total skip count")
    + test_compare(s, "log total error count", 0u, tl.total_errors,
                   "Log object init to non-ZERO total error count")

    ;
}

int test_testing_suite_init2(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Suite Tester Log Name");
  Suite(tl, "Suite Tester Suite Name1");
  Suite ts(tl, "Suite Tester Suite Name2");

  return 0
    + test_compare(s, "suite link to log", &tl, &ts.ref,
                   "Suite object does not link to Log object")
    + test_compare(s, "log link to suite", tl.curr, &ts,
                   "Log object does not link to Suite object")
    + test_compare(s, "suite link to test", ts.curr, (Test*)0,
                   "Suite object has non-NULL test link")
    + test_compare(s, "log suite count", 2u, tl.suites,
                   "Log object not counting suites correctly")
    ;
}

int test_testing_suite_ierr(Suite &s) {
  int ec = 0;
  ostringstream               oss;
  Log tl(oss, "Suite Tester Log Name");
  Suite ts1(tl, "Suite Tester Suite Name 1");

  /*
  ** More complicated test: trying to construct
  ** a new Suite object when one is already
  ** open for that log should trigger an exception.
  */

  try {
    {
      Test t(s, "Detect opening a suite with a suite still open");

      try {
        {
          Suite ts2(tl, "Suite Tester Suite Name 2");
          t.fail("second suite created without exception");
          ec ++;
        }
        t.fail("second suite closed without exception");
        ec ++;
      }
      catch (Oops &e) {
        t << e << endl;
      }
    }
    Test t(s, "close original suite after nested suite rejected");
  }
  catch (Oops &e) {
    Test t(s, "close original suite after nested suite rejected");
    t << e << endl;
    t.fail("opening second suite prevented proper closure of first.");
    ec ++;
  }

  return ec;
}

int test_testing_suite_out(Suite &s) {

  ostringstream               oss;

  Log tl(oss, "Suite Tester Log");

  oss.str("");

  {
    Suite ts(tl, "Suite Tester Suite Name");
  }

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    || test_testing_log_line (s, "top of testsuite entity", vos, off, "  <testsuite name=\"Suite Tester Suite Name\">")
    || test_testing_log_line (s, "end of testsuite entity", vos, off, "  </testsuite>")
    || test_testing_log_eof (s, "text after end of testsuite", vos, off)
    ;

}

int test_testing_suite(Log &log) {
  Suite               s(log, "Farsyte::Testing::Suite");
  return 0
    || test_testing_suite_init(s)
    || test_testing_suite_init2(s)
    || test_testing_suite_ierr(s)
    || test_testing_suite_out(s)
    ;
}

int test_testing_test_ierr(Suite &s) {
  int ec = 0;
  ostringstream               oss;
  Log tl(oss, "Test Tester Log Name");
  Suite ts(tl, "Test Tester Suite Name");
  Test tc1(ts, "Test Tester Test Name 1");

  /*
  ** More complicated test: trying to construct
  ** a new Test object when one is already
  ** open for that log should trigger an exception.
  */

  try {
    {
      Test t(s, "Detect opening a test with a test still open");

      try {
        {
          Test tc2(ts, "Test Tester Test Name 2");
          t.fail("second test created without exception");
          ec ++;
        }
        t.fail("second test closed without exception");
        ec ++;
      }
      catch (Oops &e) {
        t << e << endl;
      }
    }
    Test t(s, "close original test after nested test rejected");
  }
  catch (Oops &e) {
    Test t(s, "close original test after nested test rejected");
    t << e << endl;
    t.fail("opening second test prevented proper closure of first.");
    ec ++;
  }

  return ec;
}

int test_testing_test_init(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Test Tester Log Name");
  Suite ts(tl, "Test Tester Suite Name");
  Test tc(ts, "Test Tester Test Name");

  return 0
    + test_compare(s, "test link to suite", &ts, &tc.ref,
                   "Test object does not link to Suite object")
    + test_compare(s, "suite link to test", ts.curr, &tc,
                   "Suite object does not link to Test object")
    + test_compare(s, "log test count", 1u, tl.tests,
                   "Log object not counting tests correctly")
    + test_compare(s, "suite test count", 1u, ts.tests,
                   "Suite object not counting tests correctly")
    + test_compare(s, "test fails init", 0u, tc.fails,
                   "Test fails not initialized to zero")
    + test_compare(s, "test skips init", 0u, tc.skips,
                   "Test skips not initialized to zero")
    + test_compare(s, "test errors init", 0u, tc.errors,
                   "Test errors not initialized to zero")
    ;
}

int test_testing_test_init2(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Test Tester Log Name");
  Suite ts(tl, "Test Tester Suite Name");
  Test(ts, "Test Tester Test Name 1");
  Test tc(ts, "Test Tester Test Name 2");

  return 0
    + test_compare(s, "test link to suite", &ts, &tc.ref,
                   "Test object does not link to Suite object")
    + test_compare(s, "suite link to test", ts.curr, &tc,
                   "Suite object does not link to Test object")
    + test_compare(s, "log test count", 2u, tl.tests,
                   "Log object not counting tests correctly")
    + test_compare(s, "suite test count", 2u, ts.tests,
                   "Suite object not counting tests correctly")
    + test_compare(s, "test fails init", 0u, tc.fails,
                   "Test fails not initialized to zero")
    + test_compare(s, "test skips init", 0u, tc.skips,
                   "Test skips not initialized to zero")
    + test_compare(s, "test errors init", 0u, tc.errors,
                   "Test errors not initialized to zero")
    ;
}

int test_testing_test_init4(Suite &s) {
  ostringstream               oss;
  Log tl(oss, "Test Tester Log Name");
  {
    Suite ts(tl, "Test Tester Suite Name 1");
    Test(ts, "Test Tester Test Name 1");
    Test(ts, "Test Tester Test Name 2");
  }
  Suite ts(tl, "Test Tester Suite Name 2");
  Test(ts, "Test Tester Test Name 1");
  Test tc(ts, "Test Tester Test Name 2");

  return 0
    + test_compare(s, "test link to suite", &ts, &tc.ref,
                   "Test object does not link to Suite object")
    + test_compare(s, "suite link to test", ts.curr, &tc,
                   "Suite object does not link to Test object")
    + test_compare(s, "log test count", 4u, tl.tests,
                   "Log object not counting tests correctly")
    + test_compare(s, "suite test count", 2u, ts.tests,
                   "Suite object not counting tests correctly")
    + test_compare(s, "test fails init", 0u, tc.fails,
                   "Test fails not initialized to zero")
    + test_compare(s, "test skips init", 0u, tc.skips,
                   "Test skips not initialized to zero")
    + test_compare(s, "test errors init", 0u, tc.errors,
                   "Test errors not initialized to zero")
    ;
}

int test_testing_test_obj(Suite &s) {
  ostringstream               oss;

  Log tl(oss, "Test Tester Log");
  Suite ts(tl, "Test Tester Suite Name");

  oss.str("");

  {
    Test tc(ts, "Test Tester Test Name");
  }

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    || test_testing_log_line (s, "top of testcase entity", vos, off, "    <testcase name=\"Test Tester Test Name\">")
    || test_testing_log_line (s, "end of testcase entity", vos, off, "    </testcase>")
    || test_testing_log_eof (s, "text after end of testcase", vos, off);
}

int test_testing_test_fail(Suite &s) {

  ostringstream               oss;

  Log tl(oss, "Fail Tester Log");
  Suite ts(tl, "Fail Tester Suite Name");
  Test tc(ts, "Fail Tester Test Name");

  tc.fail("Fail Tester Condition Name (before clear)");
  oss.str("");
  tc.fail("Fail Tester Condition Name");

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    + test_compare(s, "test fails inc", 2u, tc.fails,
                   "Test fails not incremented correctly by failure")
    + test_compare(s, "test skips (by fail)", 0u, tc.skips,
                   "Test skips changed by failure")
    + test_compare(s, "test errors (by fail)", 0u, tc.errors,
                   "Test errors changed by failure")

    + test_compare(s, "suite failed tests inc", 1u, ts.failed_tests,
                   "Suite fails not incremented correctly by failure")
    + test_compare(s, "suite skipped tests (by fail)", 0u, ts.skipped_tests,
                   "Suite skips modified by failure")
    + test_compare(s, "suite errored tests (by fail)", 0u, ts.errored_tests,
                   "Suite errors modified by failure")

    + test_compare(s, "suite fails inc", 2u, ts.total_fails,
                   "Suite fails not incremented correctly by failure")
    + test_compare(s, "suite skips (by fail)", 0u, ts.total_skips,
                   "Suite skips modified by failure")
    + test_compare(s, "suite errors (by fail)", 0u, ts.total_errors,
                   "Suite errors modified by failure")


    + test_compare(s, "log failed tests inc", 1u, tl.failed_tests,
                   "Log fails not incremented correctly by failure")
    + test_compare(s, "log skipped tests (by fail)", 0u, tl.skipped_tests,
                   "Log skips modified by failure")
    + test_compare(s, "log errored tests (by fail)", 0u, tl.errored_tests,
                   "Log errors modified by failure")

    + test_compare(s, "log fails inc", 2u, tl.total_fails,
                   "Log fails not incremented correctly by failure")
    + test_compare(s, "log skips (by fail)", 0u, tl.total_skips,
                   "Log skips modified by failure")
    + test_compare(s, "log errors (by fail)", 0u, tl.total_errors,
                   "Log errors modified by failure")

    || test_testing_log_line (s, "top of failure entity", vos, off, "      <failure message=\"Fail Tester Condition Name\">")
    || test_testing_log_line (s, "end of failure entity", vos, off, "      </failure>")
    || test_testing_log_eof (s, "text after end of failure entity", vos, off);

}

int test_testing_test_text(Suite &s) {

  ostringstream               oss;

  Log tl(oss, "Text Tester Log");
  Suite ts(tl, "Text Tester Suite Name");
  Test tc(ts, "Text Tester Test Name");

  oss.str("");

  tc << "Text Tester Detail Line #1" << endl;
  tc << "Text Tester Detail Line #2\n";
  tc << "Text Tester Detail Line #3";

  tc.fail("Text Tester Condition Name");

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    || test_testing_log_line (s, "top of failure entity", vos, off, "      <failure message=\"Text Tester Condition Name\">")
    || test_testing_log_line (s, "supporting text line 1", vos, off, "Text Tester Detail Line #1")
    || test_testing_log_line (s, "supporting text line 2", vos, off, "Text Tester Detail Line #2")
    || test_testing_log_line (s, "supporting text line 3", vos, off, "Text Tester Detail Line #3")
    || test_testing_log_line (s, "end of failure entity", vos, off, "      </failure>")
    || test_testing_log_eof (s, "text after end of failure entity", vos, off);
}

int test_testing_test_skip(Suite &s) {

  ostringstream               oss;

  Log tl(oss, "Skip Tester Log");
  Suite ts(tl, "Skip Tester Suite Name");
  Test tc(ts, "Skip Tester Test Name");

  tc.skip("Skip Tester Condition Name (before clear)");
  oss.str("");
  tc << "Skip Tester Detail Line #1" << endl;
  tc << "Skip Tester Detail Line #2\n";
  tc << "Skip Tester Detail Line #3";
  tc.skip("Skip Tester Condition Name");

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    + test_compare(s, "test skips inc", 2u, tc.skips,
                   "Test skips not incremented correctly by skip")
    + test_compare(s, "test fails (by skip)", 0u, tc.fails,
                   "Test fails changed by skip")
    + test_compare(s, "test errors (by skip)", 0u, tc.errors,
                   "Test errors changed by skip")

    + test_compare(s, "suite failed tests inc", 0u, ts.failed_tests,
                   "Suite fails modified by skip")
    + test_compare(s, "suite skipped tests (by fail)", 1u, ts.skipped_tests,
                   "Suite skips not incremented correctly by skip")
    + test_compare(s, "suite errored tests (by fail)", 0u, ts.errored_tests,
                   "Suite errors modified by skip")

    + test_compare(s, "suite fails inc", 0u, ts.total_fails,
                   "Suite fails modified by skip")
    + test_compare(s, "suite skips (by fail)", 2u, ts.total_skips,
                   "Suite skips not incremented correctly by skip")
    + test_compare(s, "suite errors (by fail)", 0u, ts.total_errors,
                   "Suite errors modified by skip")

    + test_compare(s, "log failed tests inc", 0u, tl.failed_tests,
                   "Log fails modified by skip")
    + test_compare(s, "log skipped tests (by fail)", 1u, tl.skipped_tests,
                   "Log skips not incremented correctly by skip")
    + test_compare(s, "log errored tests (by fail)", 0u, tl.errored_tests,
                   "Log errors modified by skip")

    + test_compare(s, "log fails inc", 0u, tl.total_fails,
                   "Log fails modified by skip")
    + test_compare(s, "log skips (by fail)", 2u, tl.total_skips,
                   "Log skips not incremented correctly by skip")
    + test_compare(s, "log errors (by fail)", 0u, tl.total_errors,
                   "Log errors modified by skip")

    || test_testing_log_line (s, "top of skipped entity", vos, off, "      <skipped message=\"Skip Tester Condition Name\">")
    || test_testing_log_line (s, "supporting skip line 1", vos, off, "Skip Tester Detail Line #1")
    || test_testing_log_line (s, "supporting skip line 2", vos, off, "Skip Tester Detail Line #2")
    || test_testing_log_line (s, "supporting skip line 3", vos, off, "Skip Tester Detail Line #3")
    || test_testing_log_line (s, "end of skipped entity", vos, off, "      </skipped>")
    || test_testing_log_eof (s, "text after end of skipped entity", vos, off)
    ;

}

int test_testing_test_error(Suite &s) {

  ostringstream               oss;

  Log tl(oss, "Error Tester Log");
  Suite ts(tl, "Error Tester Suite Name");
  Test tc(ts, "Error Tester Test Name");

  tc.error("Error Tester Condition Name (before clear)");
  oss.str("");
  tc << "Error Tester Detail Line #1" << endl;
  tc << "Error Tester Detail Line #2\n";
  tc << "Error Tester Detail Line #3";
  tc.error("Error Tester Condition Name");

  vector<string>              vos(lines(oss));
  unsigned                    off = 0;

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially dependent;
  ** use boolean `||` operator so that if one test fails,
  ** tests that depend on it are not attempted.
  */
  return 0
    + test_compare(s, "test errors inc", 2u, tc.errors,
                   "Test errors not incremented correctly by error")
    + test_compare(s, "test skips (by error)", 0u, tc.skips,
                   "Test skips changed by error")
    + test_compare(s, "test fails (by error)", 0u, tc.fails,
                   "Test fails changed by error")

    + test_compare(s, "suite failed tests inc", 0u, ts.failed_tests,
                   "Suite fails modified by error")
    + test_compare(s, "suite skipped tests (by fail)", 0u, ts.skipped_tests,
                   "Suite skips modified by error")
    + test_compare(s, "suite errored tests (by fail)", 1u, ts.errored_tests,
                   "Suite errors not incremented correctly by error")

    + test_compare(s, "suite fails inc", 0u, ts.total_fails,
                   "Suite fails modified by error")
    + test_compare(s, "suite skips (by fail)", 0u, ts.total_skips,
                   "Suite skips modified by error")
    + test_compare(s, "suite errors (by fail)", 2u, ts.total_errors,
                   "Suite errors not incremented correctly by error")

    + test_compare(s, "log failed tests inc", 0u, tl.failed_tests,
                   "Log fails modified by error")
    + test_compare(s, "log skipped tests (by fail)", 0u, tl.skipped_tests,
                   "Log skips modified by error")
    + test_compare(s, "log errored tests (by fail)", 1u, tl.errored_tests,
                   "Log errors not incremented correctly by error")

    + test_compare(s, "log fails inc", 0u, tl.total_fails,
                   "Log fails modified by error")
    + test_compare(s, "log skips (by fail)", 0u, tl.total_skips,
                   "Log skips modified by error")
    + test_compare(s, "log errors (by fail)", 2u, tl.total_errors,
                   "Log errors not incremented correctly by error")

    || test_testing_log_line (s, "top of error entity", vos, off, "      <error message=\"Error Tester Condition Name\">")
    || test_testing_log_line (s, "supporting error line 1", vos, off, "Error Tester Detail Line #1")
    || test_testing_log_line (s, "supporting error line 2", vos, off, "Error Tester Detail Line #2")
    || test_testing_log_line (s, "supporting error line 3", vos, off, "Error Tester Detail Line #3")
    || test_testing_log_line (s, "end of error entity", vos, off, "      </error>")
    || test_testing_log_eof (s, "text after end of error entity", vos, off)
    ;

}

int test_testing_test(Log &log) {

  Suite               s(log, "Farsyte::Testing::Test");

  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */

  return 0
    + test_testing_test_init(s)
    + test_testing_test_init2(s)
    + test_testing_test_init4(s)
    + test_testing_test_ierr(s)
    + test_testing_test_obj(s)
    + test_testing_test_fail(s)
    + test_testing_test_text(s)
    + test_testing_test_skip(s)
    + test_testing_test_error(s)
    ;

}

int test_testing(Log &log) {
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */
  return 0
    + test_testing_log(log)
    + test_testing_suite(log)
    + test_testing_test(log)
    ;
}

int main(void) {

  Log                 log(cout, "Testing Library");

  int ec = test_testing(log);

  if (ec)
    fprintf(stderr, "%7d FAIL test_testing\n", ec);
  else
    fprintf(stderr, "%7d PASS test_testing\n", ec);

  return 0;
}
