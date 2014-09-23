#include "matrix.h"
#include "testing.h"
#include "utility.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include <iomanip>

using Farsyte::Matrix::ColVec;
using Farsyte::Matrix::Matrix;
using Farsyte::Matrix::ThreeVec;
using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using std::cerr;
using std::setw;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::setw;
using std::string;
using std::vector;

/** Pick a type for a test vector. */
typedef ColVec<4, int> ColVec4i;

/** Pick a type for a test matrix */
typedef Matrix<3, 2, int> Matrix23i;

/** Type for transposed test matrix */
typedef Matrix<2, 3, int> Matrix32i;

/** Small square matrix for multiply testing */
typedef Matrix<2, 2, int> Matrix22i;

/** Large square matrix for multiply testing */
typedef Matrix<3, 3, int> Matrix33i;


static int case_compare(
        Test &t,
        string const &title,
        string const &exp,
        string const &act) {
    char const qc = '"';
    t << title << endl
            << "  expected: " << qc << exp << qc << endl
            << "  observed: " << qc << act << qc << endl;
    if (act == exp) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

static int case_compare_ge(
        Test &t,
        string const &title,
        size_t exp,
        size_t act) {
    char const qc = '"';
    t << title << endl
            << "  expected: " << qc << exp << qc << endl
            << "  observed: " << qc << act << qc << endl;
    if (act >= exp) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

template<typename T>
int case_equals(
        Test &t, string const &title,
        T const &exp,
        T const &act) {

    t << title << endl
            << "  expected: "
            << exp << endl
            << "  observed: "
            << act << endl;
    if (exp == act) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}


/* -- ================================================================ -- */

static int test_matrix_version(Log &l) {
    Suite s(l, "Farsyte::Matrix::Version");
    Test t(s, "Version Comparison");

    vector<string> ver_list = Farsyte::Matrix::matrix_versions();
    size_t min_size = 1;
    size_t ver_size = ver_list.size();

    return 0
            + case_compare_ge(t, "at least one version string",
            min_size, ver_size)
            + case_compare(t, "version string compare",
            string(_matrix_h),
            ver_list[0]);
}

/* -- ================================================================ -- */

static int test_matrix(Log &log) {
    /*
    ** return convention: 0 is success, nonzero is failure.
    ** The subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */
    return 0
            + test_matrix_version(log);
}

int main(void) {

    ofstream xml("test_matrix_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix" << endl;

    return 0;
}
