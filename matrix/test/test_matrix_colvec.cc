#include "matrix.hh"
#include "testing.hh"
#include "utility.hh"
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
using Farsyte::Matrix::TriVec;
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

static int case_T(
        Test &t, string const &title,
        bool cond) {
    t << title << endl;
    if (cond) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

static int case_F(
        Test &t, string const &title,
        bool cond) {
    t << title << endl;
    if (!cond) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}


static int case_equals(
        Test &t, string const &title,
        int w, int x, int y, int z,
        ColVec4i const &r) {

    t << title << endl
            << "  expected: "
            << setw(16) << w
            << setw(16) << x
            << setw(16) << y
            << setw(16) << z
            << endl
            << "  observed: "
            << setw(16) << r[0]
            << setw(16) << r[1]
            << setw(16) << r[2]
            << setw(16) << r[3]
            << endl;
    if ((w == r[0]) && (x == r[1]) && (y == r[2]) && (z == r[3])) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

/* -- ================================================================ -- */

static int test_matrix_colvec_meta(Suite &s) {

    Test t(s, "Class Parameter Methods");

    return 0
            + case_equals(t, "ColVec Rows", 4, ColVec4i::rows())
            + case_equals(t, "ColVec Cols", 1, ColVec4i::cols())
            + case_equals(t, "ColVec Size", 4, ColVec4i::size());
}

static int test_matrix_colvec_ctor_eq_ne(Suite &s) {

    typedef ColVec4i::A IV;

    Test t(s, "Construct and Compare");

    ColVec4i D;
    ColVec4i W = IV {1, 0, 0, 0};
    ColVec4i X = IV {0, 1, 0, 0};
    ColVec4i Y = IV {0, 0, 1, 0};
    ColVec4i Z = IV {0, 0, 0, 1};

    return 0
            + case_equals(t, "Default initialized to Zero", 0, 0, 0, 0, D)
            + case_equals(t, "W Axis Initialization", 1, 0, 0, 0, W)
            + case_equals(t, "X Axis Initialization", 0, 1, 0, 0, X)
            + case_equals(t, "Y Axis Initialization", 0, 0, 1, 0, Y)
            + case_equals(t, "Z Axis Initialization", 0, 0, 0, 1, Z)

            + case_T(t, "(D == D) is True", (D == D))
            + case_T(t, "(W == W) is True", (W == W))
            + case_T(t, "(X == X) is True", (X == X))
            + case_T(t, "(Y == Y) is True", (Y == Y))
            + case_T(t, "(Z == Z) is True", (Z == Z))

            + case_T(t, "(D != W) is True", (D != W))
            + case_T(t, "(D != X) is True", (D != X))
            + case_T(t, "(D != Y) is True", (D != Y))
            + case_T(t, "(D != Z) is True", (D != Z))

            + case_T(t, "(W != D) is True", (W != D))
            + case_T(t, "(W != X) is True", (W != X))
            + case_T(t, "(W != Y) is True", (W != Y))
            + case_T(t, "(W != Z) is True", (W != Z))

            + case_T(t, "(X != D) is True", (X != D))
            + case_T(t, "(X != W) is True", (X != W))
            + case_T(t, "(X != Y) is True", (X != Y))
            + case_T(t, "(X != Z) is True", (X != Z))

            + case_T(t, "(Y != D) is True", (Y != D))
            + case_T(t, "(Y != W) is True", (Y != W))
            + case_T(t, "(Y != X) is True", (Y != X))
            + case_T(t, "(Y != Z) is True", (Y != Z))

            + case_T(t, "(Z != D) is True", (Z != D))
            + case_T(t, "(Z != W) is True", (Z != W))
            + case_T(t, "(Z != X) is True", (Z != X))
            + case_T(t, "(Z != Y) is True", (Z != Y))

            + case_F(t, "(D != D) is False", (D != D))
            + case_F(t, "(W != W) is False", (W != W))
            + case_F(t, "(X != X) is False", (X != X))
            + case_F(t, "(Y != Y) is False", (Y != Y))
            + case_F(t, "(Z != Z) is False", (Z != Z))

            + case_F(t, "(D == W) is False", (D == W))
            + case_F(t, "(D == X) is False", (D == X))
            + case_F(t, "(D == Y) is False", (D == Y))
            + case_F(t, "(D == Z) is False", (D == Z))

            + case_F(t, "(W == D) is False", (W == D))
            + case_F(t, "(W == X) is False", (W == X))
            + case_F(t, "(W == Y) is False", (W == Y))
            + case_F(t, "(W == Z) is False", (W == Z))

            + case_F(t, "(X == D) is False", (X == D))
            + case_F(t, "(X == W) is False", (X == D))
            + case_F(t, "(X == Y) is False", (X == Y))
            + case_F(t, "(X == Z) is False", (X == Z))

            + case_F(t, "(Y == D) is False", (Y == D))
            + case_F(t, "(Y == W) is False", (Y == W))
            + case_F(t, "(Y == X) is False", (Y == X))
            + case_F(t, "(Y == Z) is False", (Y == Z))

            + case_F(t, "(Z == D) is False", (Z == D))
            + case_F(t, "(Z == W) is False", (Z == W))
            + case_F(t, "(Z == X) is False", (Z == X))
            + case_F(t, "(Z == Y) is False", (Z == Y));
}

static int test_matrix_colvec_access(Suite &s) {

    typedef ColVec4i::A IV;

    Test t(s, "Member Access and Update");

    ColVec4i V = IV {1, 3, 5, 7};

    V[2] = 4;
    V[3] = V[0];

    return 0
            + case_equals(t, "Vector after access and update", 1, 3, 4, 1, V);
}

static int test_matrix_colvec_add(Suite &s) {

    typedef ColVec4i::A IV;

    Test t(s, "Addition");

    ColVec4i S;
    ColVec4i A = IV {10, 7, 4, 1};
    ColVec4i I = IV {1, 2, 3, 4};
    A += I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, 4, I)
            + case_equals(t, "A incremented once", 11, 9, 7, 5, A)
            + case_equals(t, "Second Sum", 12, 11, 10, 9, A + I)
            + case_equals(t, "Add Negative", 10, 7, 4, 1, A + (-I));
}

static int test_matrix_colvec_sub(Suite &s) {

    typedef ColVec4i::A IV;

    Test t(s, "Difference");

    ColVec4i D;
    ColVec4i A = IV {9, 8, 7, 6};
    ColVec4i I = IV {1, 2, 3, 4};
    A -= I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, 4, I)
            + case_equals(t, "A decremented once", 8, 6, 4, 2, A)
            + case_equals(t, "second difference", 7, 4, 1, -2, A - I)
            + case_equals(t, "Sub Negative", 9, 8, 7, 6, A - (-I));
}

static int test_matrix_colvec(Log &log) {

    /*
    ** Tests specific to the ColVec Template
    */
    Suite s(log, "Farsyte::Matrix::ColVec");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** the subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
            + test_matrix_colvec_meta(s)
            + test_matrix_colvec_ctor_eq_ne(s)
            + test_matrix_colvec_access(s)
            + test_matrix_colvec_add(s)
            + test_matrix_colvec_sub(s);

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
            + test_matrix_colvec(log);
}

int main(void) {

    ofstream xml("test_matrix_colvec_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix_colvec" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix_colvec" << endl;

    return 0;
}
