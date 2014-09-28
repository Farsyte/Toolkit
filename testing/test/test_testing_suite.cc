#include "testing.hh"
#include "utility.hh"
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


/** Verify the next entry in a string list is as expected.
*/

/** Verify that we are at the end of the string list.
*/

/** Test that Log objects have correct initial state.
*/



static int test_testing_suite_init(Suite &s) {
    ostringstream oss;
    int ec = 0;
    Log tl(oss, "Suite Tester Log Name");
    Suite ts(tl, "Suite Tester Suite Name");

    {
        Test t(s, "Initial Suite Primary Bookkeeping");
        ec = ec
                + t.eq(&ts.ref, &tl, "Suite link to Log object")
                + t.eq(tl.curr, &ts, "Log link to Suite object")
                + t.eq(ts.curr, (void *) 0, "Suite link to Test object")
                + t.eq(tl.suites, 1, "Log count of Suite objects")
                + t.eq(ts.tests, 0, "Suite count of Test objects");
    }

    {
        Test t(s, "Initial Suite Result Counters");
        ec = ec
                + t.eq(ts.failed_tests, 0, "suite failed test count")
                + t.eq(ts.skipped_tests, 0, "suite skipped test count")
                + t.eq(ts.errored_tests, 0, "suite errored test count")
                + t.eq(ts.total_fails, 0, "suite failed condition count")
                + t.eq(ts.total_skips, 0, "suite skipped condition count")
                + t.eq(ts.total_errors, 0, "suite total error count");
    }

    {
        Test t(s, "Initial Log Result Counters");
        ec = ec
                + t.eq(tl.failed_tests, 0, "log failed test count")
                + t.eq(tl.skipped_tests, 0, "log skipped test count")
                + t.eq(tl.errored_tests, 0, "log errored test count")
                + t.eq(tl.total_fails, 0, "log failed condition count")
                + t.eq(tl.total_skips, 0, "log skipped condition count")
                + t.eq(tl.total_errors, 0, "log total error count");
    }

    return ec;
}

static int test_testing_suite_init2(Suite &s) {
    ostringstream oss;
    Log tl(oss, "Suite Tester Log Name");
    Suite(tl, "Suite Tester Suite Name1");
    Suite ts(tl, "Suite Tester Suite Name2");

    Test t(s, "Initialization of Second Suite");

    return 0
            + t.eq(&ts.ref, &tl, "Second Suite links to Log")
            + t.eq(tl.curr, &ts, "Log links to Second Suite")
            + t.eq(ts.curr, (void *) 0, "Second Suite link to Test is NULL")
            + t.eq(tl.suites, 2, "Log count of Suites");
}

static int test_testing_suite_ierr(Suite &s) {
    int ec = 0;
    ostringstream oss;
    Log tl(oss, "Suite Tester Log Name");
    Suite ts1(tl, "Suite Tester Suite Name 1");

    /*
    ** More complicated test: trying to construct
    ** a new Suite object when one is already
    ** open for that log should trigger an exception.
    */

    Test t(s, "Detect opening a suite with a suite still open");

    try {
        Suite ts2(tl, "Suite Tester Suite Name 2");
        t.fail("second suite created without exception");
        ec++;
    }
    catch (Oops &e) {
        t << e << endl;
        t.pass("Suite nesting properly rejected");
    }

    return ec;
}

static int test_testing_suite_out(Suite &s) {

    ostringstream oss;

    Log tl(oss, "Suite Tester Log");

    oss.str("");

    // Create, then immeidately discard a temporary suite:
    // we just want to see the net addition to the log.
    (void) Suite(tl, "Suite Tester Suite Name");

    vector<string> vos(streamlines(oss));

    Test t(s, "XML output by Suite");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return 0
            || t.ge(vos.size(), 2u, "long enough")
            || t.eq(vos[0], "  <testsuite name=\"Suite Tester Suite Name\">", "add <testsuite>")
            || t.eq(vos[1], "  </testsuite>", "Add </testsuite>")
            || t.eq(vos.size(), 2u, "no extra text");
}

static int test_testing_suite(Log &log) {
    Suite s(log, "Farsyte::Testing::Suite");
    return 0
            || test_testing_suite_init(s)
            || test_testing_suite_init2(s)
            || test_testing_suite_ierr(s)
            || test_testing_suite_out(s);
}


static int test_testing(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_testing_suite(log);
}

int main(void) {
    ofstream xml("test_testing_suite_log.xml");
    assert(xml);
    Log log(xml, "Testing Library");

    int ec = test_testing(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_testing_suite" << endl;
    else
        cerr << setw(7) << ec << " PASS test_testing_suite" << endl;

    return 0;
}
