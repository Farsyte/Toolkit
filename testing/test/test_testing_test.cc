#include "testing.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <assert.h>

using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using Farsyte::Utility::literal;
using Farsyte::Utility::quoted;
using Farsyte::Utility::streamlines;
using std::cerr;
using std::setw;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

static int test_testing_test_ierr(Suite &s) {
    int ec = 0;
    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test tc1(ts, "Test Tester Test Name 1");

    /*
    ** More complicated test: trying to construct
    ** a new Test object when one is already
    ** open for that log should trigger an exception.
    */

    Test t(s, "Detect opening a test with a test still open");

    try {
        {
            Test tc2(ts, "Test Tester Test Name 2");
            t.fail("second test created without exception");
            ec++;
        }
    }
    catch (Oops &e) {
        t << e << endl;
        t.pass("prevented nesting Test objects");
    }

    return ec;
}

static int test_testing_test_init(Suite &s) {
    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test tc(ts, "Test Tester Test Name");

    Test t(s, "Test object initialization");

    return 0
            + t.eq(&tc.ref, &ts, "Test link to Suite object")
            + t.eq(ts.curr, &tc, "Suite link to Test object")
            + t.eq(tl.tests, 1, "Log count of tests incremented")
            + t.eq(ts.tests, 1, "Suite count of tests incremented")
            + t.eq(tc.fails, 0, "Test count or condition FAILs clear")
            + t.eq(tc.skips, 0, "Test count of condition SKIPs clear")
            + t.eq(tc.errors, 0, "Test count of testing ERROSs clear");
}

static int test_testing_test_init2(Suite &s) {
    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    Suite ts(tl, "Test Tester Suite Name");
    Test(ts, "Test Tester Test Name 1");
    Test tc(ts, "Test Tester Test Name 2");

    Test t(s, "Second Test Object Init");

    return 0
            + t.eq(&tc.ref, &ts, "Test link to Suite")
            + t.eq(ts.curr, &tc, "Suite link to Test")
            + t.eq(tl.tests, 2, "Log counter of Tests")
            + t.eq(ts.tests, 2, "Suite counter of Tests")
            + t.eq(tc.fails, 0, "Test counter of FAILs")
            + t.eq(tc.skips, 0, "Test counter of SKIPs")
            + t.eq(tc.errors, 0, "Test counter of ERRORs");
}

static int test_testing_test_init4(Suite &s) {
    ostringstream oss;
    Log tl(oss, "Test Tester Log Name");
    {
        Suite ts(tl, "Test Tester Suite Name 1");
        Test(ts, "Test Tester Test Name 1");
        Test(ts, "Test Tester Test Name 2");
    }
    Suite ts(tl, "Test Tester Suite Name 2");
    Test(ts, "Test Tester Test Name 1");
    Test tc(ts, "Test Tester Test Name 2");

    Test t(s, "Multi-suite Multi-test init check");

    return 0
            + t.eq(&tc.ref, &ts, "Test link to Suite")
            + t.eq(ts.curr, &tc, "Suite link to Test")
            + t.eq(tl.tests, 4, "Log test counter")
            + t.eq(ts.tests, 2, "Suite test counter")
            + t.eq(tc.fails, 0, "Test counter of FAILs")
            + t.eq(tc.skips, 0, "Test counter of SKIPs")
            + t.eq(tc.errors, 0, "Test counter of ERRORs");
}

static int test_testing_test_obj(Suite &s) {
    ostringstream oss;

    Log tl(oss, "Test Tester Log");
    Suite ts(tl, "Test Tester Suite Name");

    oss.str("");

    // Create and immediately destroy a Test object:
    // all we want is the net effect on the Log stream.

    (void) Test(ts, "Test Tester Test Name");

    vector<string> vos(streamlines(oss));

    Test t(s, "XML output from Test object");
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return 0
            || t.ge(vos.size(), 2u, "enough XML output.")
            || t.eq(vos[0], "    <testcase name=\"Test Tester Test Name\">", "<testcase>")
            || t.eq(vos[1], "    </testcase>", "</testcase>")
            || t.eq(vos.size(), 2u, "no extra XML output.");
}

static int test_testing_test_fail(Suite &s) {

    ostringstream oss;

    Log tl(oss, "Fail Tester Log");
    Suite ts(tl, "Fail Tester Suite Name");
    Test tc(ts, "Fail Tester Test Name");

    tc.fail("Fail Tester Condition Name (before clear)");
    oss.str("");
    tc.fail("Fail Tester Condition Name");

    vector<string> vos(streamlines(oss));

    int ec = 0;

    {
        Test t(s, "XML output from Test::fail()");
        ec = ec
                || t.ge(vos.size(), 2u, "enough XML output")
                || t.eq(vos[0], "      <failure message=\"Fail Tester Condition Name\">", "<failure>")
                || t.eq(vos[1], "      </failure>", "</failure>")
                || t.eq(vos.size(), 2u, "not too much XML output");
    }
    {
        Test t(s, "Bookkeeping update from Test::fail()");
        ec = ec
                + t.eq(tc.fails, 2, "Test FAILs counter")
                + t.eq(tc.skips, 0, "Test SKIPs counter")
                + t.eq(tc.errors, 0, "Test ERRORs counter")

                + t.eq(ts.failed_tests, 1, "Suite count of Test FAILs")
                + t.eq(ts.skipped_tests, 0, "Suite count of Test SKIPs")
                + t.eq(ts.errored_tests, 0, "Suite count of Test ERRORs")

                + t.eq(ts.total_fails, 2, "Suite cont of Cond FAILs")
                + t.eq(ts.total_skips, 0, "Suite count of Cond SKIPs")
                + t.eq(ts.total_errors, 0, "Suite count of Cond ERRORs")

                + t.eq(tl.failed_tests, 1, "Log count of Test FAILs")
                + t.eq(tl.skipped_tests, 0, "Log count of Test FAILs")
                + t.eq(tl.errored_tests, 0, "Log count of Test ERRORs")

                + t.eq(tl.total_fails, 2, "Log count of Cond FAILs")
                + t.eq(tl.total_skips, 0, "Log count of Cond SKIPs")
                + t.eq(tl.total_errors, 0, "Log count of Cond ERRORs");
    }

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return ec;
}

static int test_testing_test_text(Suite &s) {

    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <failure message=\"Text Tester Condition Name\">"),
            Farsyte::Utility::quoted("Text Tester Detail Line #1"),
            Farsyte::Utility::quoted("Text Tester Detail Line #2"),
            Farsyte::Utility::quoted("Text Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </failure>"),
    };
    static const vector<string> msg = {
            "open failure entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close failure entity"
    };

    ostringstream oss;

    Log tl(oss, "Text Tester Log");
    Suite ts(tl, "Text Tester Suite Name");
    Test tc(ts, "Text Tester Test Name");

    oss.str("");

    tc << "Text Tester Detail Line #1" << endl;
    tc << "Text Tester Detail Line #2\n";
    tc << "Text Tester Detail Line #3";

    tc.fail("Text Tester Condition Name");

    vector<string> vos(streamlines(oss));

    Test t(s, "XML output of Test::fail evidence");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return 0
            || t.ge(vos.size(), 5u, "enough XML output.")
            || t.eq(Farsyte::Utility::quoted(vos[0]), exp[0], msg[0])
            || t.eq(Farsyte::Utility::quoted(vos[1]), exp[1], msg[1])
            || t.eq(Farsyte::Utility::quoted(vos[2]), exp[2], msg[2])
            || t.eq(Farsyte::Utility::quoted(vos[3]), exp[3], msg[3])
            || t.eq(Farsyte::Utility::quoted(vos[4]), exp[4], msg[4])
            || t.eq(vos.size(), 5u, "no extra XML output.");
}

static int test_testing_test_skip(Suite &s) {
    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <skipped message=\"Skip Tester Condition Name\">"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #1"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #2"),
            Farsyte::Utility::quoted("Skip Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </skipped>"),
    };
    static const vector<string> msg = {
            "open skipped entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close skipped entity"
    };

    ostringstream oss;

    Log tl(oss, "Skip Tester Log");
    Suite ts(tl, "Skip Tester Suite Name");
    Test tc(ts, "Skip Tester Test Name");

    tc.skip("Skip Tester Condition Name (before clear)");
    oss.str("");
    tc << "Skip Tester Detail Line #1" << endl;
    tc << "Skip Tester Detail Line #2\n";
    tc << "Skip Tester Detail Line #3";
    tc.skip("Skip Tester Condition Name");

    vector<string> vos(streamlines(oss));

    int ec = 0;

    {
        Test t(s, "XML output from Test::skip with evidence");
        ec = ec
                + t.ge(vos.size(), 5u, "Enough XML output")
                + t.eq(Farsyte::Utility::quoted(vos[0]), exp[0], msg[0])
                + t.eq(Farsyte::Utility::quoted(vos[1]), exp[1], msg[1])
                + t.eq(Farsyte::Utility::quoted(vos[2]), exp[2], msg[2])
                + t.eq(Farsyte::Utility::quoted(vos[3]), exp[3], msg[3])
                + t.eq(Farsyte::Utility::quoted(vos[4]), exp[4], msg[4])
                + t.ge(vos.size(), 5u, "Enough XML output");
    }

    {
        Test t(s, "Bookkeeping update from Test::skip");
        ec = ec
                + t.eq(tc.fails, 0, "Test FAILs counter")
                + t.eq(tc.skips, 2, "Test SKIPs counter")
                + t.eq(tc.errors, 0, "Test ERRORs counter")

                + t.eq(ts.failed_tests, 0, "Suite count of Test FAILs")
                + t.eq(ts.skipped_tests, 1, "Suite count of Test SKIPs")
                + t.eq(ts.errored_tests, 0, "Suite count of Test ERRORs")

                + t.eq(ts.total_fails, 0, "Suite cont of Cond FAILs")
                + t.eq(ts.total_skips, 2, "Suite count of Cond SKIPs")
                + t.eq(ts.total_errors, 0, "Suite count of Cond ERRORs")

                + t.eq(tl.failed_tests, 0, "Log count of Test FAILs")
                + t.eq(tl.skipped_tests, 1, "Log count of Test FAILs")
                + t.eq(tl.errored_tests, 0, "Log count of Test ERRORs")

                + t.eq(tl.total_fails, 0, "Log count of Cond FAILs")
                + t.eq(tl.total_skips, 2, "Log count of Cond SKIPs")
                + t.eq(tl.total_errors, 0, "Log count of Cond ERRORs");
    }
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return ec;

}

static int test_testing_test_error(Suite &s) {
    static const vector<string> exp = {
            Farsyte::Utility::quoted("      <error message=\"Error Tester Condition Name\">"),
            Farsyte::Utility::quoted("Error Tester Detail Line #1"),
            Farsyte::Utility::quoted("Error Tester Detail Line #2"),
            Farsyte::Utility::quoted("Error Tester Detail Line #3"),
            Farsyte::Utility::quoted("      </error>"),
    };
    static const vector<string> msg = {
            "open error entity",
            "evidence line 1",
            "evidence line 2",
            "evidence line 3",
            "close error entity"
    };

    ostringstream oss;

    Log tl(oss, "Error Tester Log");
    Suite ts(tl, "Error Tester Suite Name");
    Test tc(ts, "Error Tester Test Name");

    tc.error("Error Tester Condition Name (before clear)");
    oss.str("");
    tc << "Error Tester Detail Line #1" << endl;
    tc << "Error Tester Detail Line #2\n";
    tc << "Error Tester Detail Line #3";
    tc.error("Error Tester Condition Name");

    vector<string> vos(streamlines(oss));

    int ec = 0;

    {
        Test t(s, "XML output from Test::error");
        ec = ec
                || t.ge(vos.size(), 5u, "Enough XML output.")
                || t.eq(Farsyte::Utility::quoted(vos[0]), exp[0], msg[0])
                || t.eq(Farsyte::Utility::quoted(vos[1]), exp[1], msg[1])
                || t.eq(Farsyte::Utility::quoted(vos[2]), exp[2], msg[2])
                || t.eq(Farsyte::Utility::quoted(vos[3]), exp[3], msg[3])
                || t.eq(Farsyte::Utility::quoted(vos[4]), exp[4], msg[4])
                || t.eq(vos.size(), 5u, "No extra XML output.");
    }

    {
        Test t(s, "Bookkeeping update from Test::error");
        ec = ec
                + t.eq(tc.fails, 0, "Test FAILs counter")
                + t.eq(tc.skips, 0, "Test SKIPs counter")
                + t.eq(tc.errors, 2, "Test ERRORs counter")

                + t.eq(ts.failed_tests, 0, "Suite count of Test FAILs")
                + t.eq(ts.skipped_tests, 0, "Suite count of Test SKIPs")
                + t.eq(ts.errored_tests, 1, "Suite count of Test ERRORs")

                + t.eq(ts.total_fails, 0, "Suite cont of Cond FAILs")
                + t.eq(ts.total_skips, 0, "Suite count of Cond SKIPs")
                + t.eq(ts.total_errors, 2, "Suite count of Cond ERRORs")

                + t.eq(tl.failed_tests, 0, "Log count of Test FAILs")
                + t.eq(tl.skipped_tests, 0, "Log count of Test FAILs")
                + t.eq(tl.errored_tests, 1, "Log count of Test ERRORs")

                + t.eq(tl.total_fails, 0, "Log count of Cond FAILs")
                + t.eq(tl.total_skips, 0, "Log count of Cond SKIPs")
                + t.eq(tl.total_errors, 2, "Log count of Cond ERRORs");
    }

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return ec;
}

static int test_testing_test(Log &log) {

    Suite s(log, "Farsyte::Testing::Test");

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
            + test_testing_test_error(s);
}

static int test_testing(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_testing_test(log);
}

int main(void) {
    ofstream xml("test_testing_test_log.xml");
    assert(xml);
    Log log(xml, "Testing Library");

    int ec = test_testing(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_testing_test" << endl;
    else
        cerr << setw(7) << ec << " PASS test_testing_test" << endl;

    return 0;
}
