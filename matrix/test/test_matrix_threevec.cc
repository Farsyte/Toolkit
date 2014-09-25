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
        double x, double y, double z,
        ThreeVec const &r) {

    t << title << endl
            << "  expected: "
            << setw(16) << x
            << setw(16) << y
            << setw(16) << z
            << endl
            << "  observed: "
            << setw(16) << r[0]
            << setw(16) << r[1]
            << setw(16) << r[2]
            << endl;
    if ((x == r[0]) && (y == r[1]) && (z == r[2])) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

/* -- ================================================================ -- */

static int test_matrix_threevec_meta(Suite &s) {

    Test t(s, "Class Parameter Methods");

    return 0
            + case_equals(t, "ThreeVec Rows", 3, ThreeVec::rows())
            + case_equals(t, "ThreeVec Cols", 1, ThreeVec::cols())
            + case_equals(t, "ThreeVec Size", 3, ThreeVec::size());
}

static int test_matrix_threevec_ctor_eq_ne(Suite &s) {

    Test t(s, "Construct and Compare");

    ThreeVec D;
    ThreeVec X{1, 0, 0};
    ThreeVec Y{0, 1, 0};
    ThreeVec Z{0, 0, 1};

    return 0
            + case_equals(t, "Default initialized to Zero", 0, 0, 0, D)
            + case_equals(t, "X Axis Initialization", 1, 0, 0, X)
            + case_equals(t, "Y Axis Initialization", 0, 1, 0, Y)
            + case_equals(t, "Z Axis Initialization", 0, 0, 1, Z)

            + case_T(t, "(D == D) is True", (D == D))
            + case_T(t, "(X == X) is True", (X == X))
            + case_T(t, "(Y == Y) is True", (Y == Y))
            + case_T(t, "(Z == Z) is True", (Z == Z))

            + case_T(t, "(D != X) is True", (D != X))
            + case_T(t, "(D != Y) is True", (D != Y))
            + case_T(t, "(D != Z) is True", (D != Z))
            + case_T(t, "(X != D) is True", (X != D))
            + case_T(t, "(X != Y) is True", (X != Y))
            + case_T(t, "(X != Z) is True", (X != Z))
            + case_T(t, "(Y != D) is True", (Y != D))
            + case_T(t, "(Y != X) is True", (Y != X))
            + case_T(t, "(Y != Z) is True", (Y != Z))
            + case_T(t, "(Z != D) is True", (Z != D))
            + case_T(t, "(Z != X) is True", (Z != X))
            + case_T(t, "(Z != Y) is True", (Z != Y))

            + case_F(t, "(D != D) is False", (D != D))
            + case_F(t, "(X != X) is False", (X != X))
            + case_F(t, "(Y != Y) is False", (Y != Y))
            + case_F(t, "(Z != Z) is False", (Z != Z))

            + case_F(t, "(D == X) is False", (D == X))
            + case_F(t, "(D == Y) is False", (D == Y))
            + case_F(t, "(D == Z) is False", (D == Z))
            + case_F(t, "(X == D) is False", (X == D))
            + case_F(t, "(X == Y) is False", (X == Y))
            + case_F(t, "(X == Z) is False", (X == Z))
            + case_F(t, "(Y == D) is False", (Y == D))
            + case_F(t, "(Y == X) is False", (Y == X))
            + case_F(t, "(Y == Z) is False", (Y == Z))
            + case_F(t, "(Z == D) is False", (Z == D))
            + case_F(t, "(Z == X) is False", (Z == X))
            + case_F(t, "(Z == Y) is False", (Z == Y));
}

static int test_matrix_threevec_access(Suite &s) {

    Test t(s, "Member Access and Update");

    ThreeVec V{3, 5, 7};

    V[1] = 4;
    V[2] = V[0];

    return 0
            + case_equals(t, "Vector after access and update", 3, 4, 3, V);
}

static int test_matrix_threevec_add(Suite &s) {

    Test t(s, "Addition");

    ThreeVec S;
    ThreeVec A{7, 4, 1};
    ThreeVec I{1, 2, 3};
    A += I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, I)
            + case_equals(t, "A incremented once", 8, 6, 4, A)
            + case_equals(t, "Second Sum", 9, 8, 7, A + I)
            + case_equals(t, "Add Negative", 7, 4, 1, A + (-I));
}

static int test_matrix_threevec_sub(Suite &s) {

    Test t(s, "Difference");

    ThreeVec D;
    ThreeVec A{9, 8, 7};
    ThreeVec I{1, 2, 3};
    A -= I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, I)
            + case_equals(t, "A decremented once", 8, 6, 4, A)
            + case_equals(t, "second difference", 7, 4, 1, A - I)
            + case_equals(t, "Sub Negative", 9, 8, 7, A - (-I));
}

static int test_matrix_threevec_cross(Suite &s) {

    Test t(s, "Construct and Compare");

    ThreeVec X{1, 0, 0};
    ThreeVec Y{0, 2, 0};
    ThreeVec Z{0, 0, 3};

    return 0
            + case_equals(t, "cross(X,X)", 0, 0, 0, cross(X, X))
            + case_equals(t, "cross(Y,Y)", 0, 0, 0, cross(Y, Y))
            + case_equals(t, "cross(Z,Z)", 0, 0, 0, cross(Z, Z))

            + case_equals(t, "cross(X,Y)", 0, 0, 2, cross(X, Y))
            + case_equals(t, "cross(Y,Z)", 6, 0, 0, cross(Y, Z))
            + case_equals(t, "cross(Z,X)", 0, 3, 0, cross(Z, X))

            + case_equals(t, "cross(X,Z)", 0, -3, 0, cross(X, Z))
            + case_equals(t, "cross(Y,X)", 0, 0, -2, cross(Y, X))
            + case_equals(t, "cross(Z,Y)", -6, 0, 0, cross(Z, Y));
}

static int test_matrix_threevec(Log &log) {

    /*
    ** Tests specific to the ThreeVec Class
    */
    Suite s(log, "Farsyte::Matrix::ThreeVec");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** the subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
            + test_matrix_threevec_meta(s)
            + test_matrix_threevec_ctor_eq_ne(s)
            + test_matrix_threevec_access(s)
            + test_matrix_threevec_add(s)
            + test_matrix_threevec_sub(s)
            + test_matrix_threevec_cross(s);

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
            + test_matrix_threevec(log);
}

int main(void) {

    ofstream xml("test_matrix_threevec_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix_threevec" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix_threevec" << endl;

    return 0;
}
