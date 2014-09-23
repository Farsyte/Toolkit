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
using std::cerr;
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
static int test_testing_log_line(
        Suite &s,
        string const &title,
        vector<string> const &vos,
        unsigned &off,
        string const &exp) {
    Test t(s, title);

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** if any test fails, do not try remaining tests.
    */

    int ec = 0
            || t.ge(vos.size(), off, "XML Text generated")
            || t.eq(vos[off], exp, "XML Text matches");

    if (ec < 1)
        ++off;

    return ec;
}

/** Verify that we are at the end of the string list.
*/
static int test_testing_log_eof(
        Suite &s,
        string const &title,
        vector<string> const &vos,
        unsigned off) {
    Test t(s, title);

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** if any test fails, do not try remaining tests.
    */

    return t.eq(off, vos.size(), "XML End of File");
}

/** Test that Log objects have correct initial state.
*/
static int test_testing_log_init(Suite &s) {
    ostringstream oss;
    Log tl(oss, "Log Tester Log Name");

    Test t(s, "Initial state of Log");

    return 0
            + t.eq(&tl.out, &oss, "output stream reference")
            + t.eq(tl.curr, (void *) 0, "initial Suite link")
            + t.eq(tl.suites, 0, "initial Suite count")
            + t.eq(tl.tests, 0, "initial Test count");
}

static int test_testing_log_out(Suite &s) {

    ostringstream oss;

    {
        Log tl(oss, "Log Tester Log Name");
    }

    vector<string> vos(streamlines(oss));
    unsigned off = 0;

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially dependent;
    ** use boolean `||` operator so that if one test fails,
    ** tests that depend on it are not attempted.
    */
    return 0
            || test_testing_log_line(s, "XML Header", vos, off, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
            || test_testing_log_line(s, "top of testsuites entity", vos, off, "<testsuites name=\"Log Tester Log Name\">")
            || test_testing_log_line(s, "end of testsuites entity", vos, off, "</testsuites>")
            || test_testing_log_eof(s, "text after end of testsuites", vos, off);

}

static int test_testing_log(Log &log) {
    Suite s(log, "Farsyte::Testing::Log");

    return 0
            || test_testing_log_init(s)
            || test_testing_log_out(s);
}


static int test_testing(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_testing_log(log);
}

int main(void) {
    ofstream xml("test_testing_log_log.xml");
    assert(xml);
    Log log(xml, "Testing Library");

    int ec = test_testing(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_testing_log" << endl;
    else
        cerr << setw(7) << ec << " PASS test_testing_log" << endl;

    return 0;
}
