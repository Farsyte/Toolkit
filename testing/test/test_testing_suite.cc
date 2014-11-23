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

UT_CASE(Suite, Init) {

    ostringstream oss;
    Log tl(oss, "Suite Tester Log Name");
    Suite ts(tl, "Suite Tester Suite Name");

    EXPECT_EQ(&ts.ref, &tl);            // Suite link to Log object
    EXPECT_EQ(tl.curr, &ts);            // Log link to Suite object
    EXPECT_EQ(ts.curr, (void *) 0);     // Suite link to Test object
    EXPECT_EQ(tl.suites, 1);            // Log count of Suite objects
    EXPECT_EQ(ts.tests, 0);             // Suite count of Test objects

    EXPECT_EQ(ts.failed_tests, 0);                              // suite failed test count
    EXPECT_EQ(ts.skipped_tests, 0);                             // suite skipped test count
    EXPECT_EQ(ts.errored_tests, 0);                             // suite errored test count
    EXPECT_EQ(ts.total_fails, 0);                               // suite failed condition count
    EXPECT_EQ(ts.total_skips, 0);                               // suite skipped condition count
    EXPECT_EQ(ts.total_errors, 0);                              // suite total error count

    EXPECT_EQ(tl.failed_tests, 0);                              // log failed test count
    EXPECT_EQ(tl.skipped_tests, 0);                             // log skipped test count
    EXPECT_EQ(tl.errored_tests, 0);                             // log errored test count
    EXPECT_EQ(tl.total_fails, 0);                               // log failed condition count
    EXPECT_EQ(tl.total_skips, 0);                               // log skipped condition count
    EXPECT_EQ(tl.total_errors, 0);                              // log total error count
}

UT_CASE(Suite, Init2) {
    ostringstream oss;
    Log tl(oss, "Suite Tester Log Name");
    Suite(tl, "Suite Tester Suite Name1");
    Suite ts(tl, "Suite Tester Suite Name2");

    EXPECT_EQ(&ts.ref, &tl);                                    // Second Suite links to Log
    EXPECT_EQ(tl.curr, &ts);                                    // Log links to Second Suite
    EXPECT_EQ(ts.curr, (void *) 0);                             // Second Suite link to Test is NULL
    EXPECT_EQ(tl.suites, 2);                                    // Log count of Suites
}

UT_CASE(Suite, Ierr) {

    ostringstream oss;
    Log tl(oss, "Suite Tester Log Name");
    Suite ts1(tl, "Suite Tester Suite Name 1");

    // Opening a second suite inside a Log
    // triggers an exception.

    Suite *sp = 0;
    EXPECT_EX(sp = new Suite(tl, "Suite Tester Suite Name 2"));
    if (sp) delete sp;
}

UT_CASE(Suite, Output) {

    ostringstream oss;

    Log tl(oss, "Suite Tester Log");

    oss.str("");

    // Create, then immeidately discard a temporary suite:
    // we just want to see the net addition to the log.
    (void) Suite(tl, "Suite Tester Suite Name");

    vector<string> vos(streamlines(oss));

    ASSERT_GE(vos.size(), 1u); EXPECT_EQ(vos[0], "  <testsuite name=\"Suite Tester Suite Name\">"); // add <testsuite>
    ASSERT_GE(vos.size(), 2u); EXPECT_EQ(vos[1], "  </testsuite>");                        // Add </testsuite>
    EXPECT_EQ(vos.size(), 2u);                                  // no extra text
}
