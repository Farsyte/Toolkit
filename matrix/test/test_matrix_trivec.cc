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

/* -- ================================================================ -- */

static int test_matrix_trivec_meta(Suite &s) {

    Test t(s, "Class Parameter Methods");

    return 0
            + t.eq(TriVec::rows(), 3, "TriVec Rows")
            + t.eq(TriVec::cols(), 1, "TriVec Cols")
            + t.eq(TriVec::size(), 3, "TriVec Size");
}

static int test_matrix_trivec_ctor_eq_ne(Suite &s) {

    Test t(s, "Construct and Compare");

    TriVec D;
    TriVec X{1, 0, 0};
    TriVec Y{0, 1, 0};
    TriVec Z{0, 0, 1};

    return 0

            + t.is_T(D == D, "(D == D) is True")
            + t.is_T(X == X, "(X == X) is True")
            + t.is_T(Y == Y, "(Y == Y) is True")
            + t.is_T(Z == Z, "(Z == Z) is True")

            + t.is_T(D != X, "(D != X) is True")
            + t.is_T(D != Y, "(D != Y) is True")
            + t.is_T(D != Z, "(D != Z) is True")
            + t.is_T(X != D, "(X != D) is True")
            + t.is_T(X != Y, "(X != Y) is True")
            + t.is_T(X != Z, "(X != Z) is True")
            + t.is_T(Y != D, "(Y != D) is True")
            + t.is_T(Y != X, "(Y != X) is True")
            + t.is_T(Y != Z, "(Y != Z) is True")
            + t.is_T(Z != D, "(Z != D) is True")
            + t.is_T(Z != X, "(Z != X) is True")
            + t.is_T(Z != Y, "(Z != Y) is True")

            + t.is_F(D != D, "(D != D) is False")
            + t.is_F(X != X, "(X != X) is False")
            + t.is_F(Y != Y, "(Y != Y) is False")
            + t.is_F(Z != Z, "(Z != Z) is False")

            + t.is_F(D == X, "(D == X) is False")
            + t.is_F(D == Y, "(D == Y) is False")
            + t.is_F(D == Z, "(D == Z) is False")
            + t.is_F(X == D, "(X == D) is False")
            + t.is_F(X == Y, "(X == Y) is False")
            + t.is_F(X == Z, "(X == Z) is False")
            + t.is_F(Y == D, "(Y == D) is False")
            + t.is_F(Y == X, "(Y == X) is False")
            + t.is_F(Y == Z, "(Y == Z) is False")
            + t.is_F(Z == D, "(Z == D) is False")
            + t.is_F(Z == X, "(Z == X) is False")
            + t.is_F(Z == Y, "(Z == Y) is False");
}

static int test_matrix_trivec_access(Suite &s) {

    Test t(s, "Member Access and Update");

    TriVec V{3, 5, 7};

    V[1] = 4;
    V[2] = V[0];

    return 0
            + t.eq(V, TriVec{3, 4, 3}, "Vector after access and update");
}

static int test_matrix_trivec_add(Suite &s) {

    Test t(s, "Addition");

    TriVec A{7, 4, 1};
    TriVec I{1, 2, 3};
    A += I;

    return 0
            + t.eq(I, TriVec{1, 2, 3}, "I unchanged")
            + t.eq(A, TriVec{8, 6, 4}, "A incremented once")
            + t.eq(A + I, TriVec{9, 8, 7}, "Second Sum")
            + t.eq(A + (-I), TriVec{7, 4, 1}, "Add Negative");
}

static int test_matrix_trivec_sub(Suite &s) {

    Test t(s, "Difference");

    TriVec D;
    TriVec A{9, 8, 7};
    TriVec I{1, 2, 3};
    A -= I;

    return 0
            + t.eq(I, TriVec{1, 2, 3}, "I unchanged")
            + t.eq(A, TriVec{8, 6, 4}, "A decremented once")
            + t.eq(A - I, TriVec{7, 4, 1}, "second difference")
            + t.eq(A - (-I), TriVec{9, 8, 7}, "Sub Negative");
}

static int test_matrix_trivec_cross(Suite &s) {

    Test t(s, "Cross Product");

    TriVec X{1, 0, 0};
    TriVec Y{0, 2, 0};
    TriVec Z{0, 0, 3};

    return 0
            + t.eq(cross(X, X), TriVec{0, 0, 0}, "cross(X,X)")
            + t.eq(cross(Y, Y), TriVec{0, 0, 0}, "cross(Y,Y)")
            + t.eq(cross(Z, Z), TriVec{0, 0, 0}, "cross(Z,Z)")

            + t.eq(cross(X, Y), TriVec{0, 0, 2}, "cross(X,Y)")
            + t.eq(cross(Y, Z), TriVec{6, 0, 0}, "cross(Y,Z)")
            + t.eq(cross(Z, X), TriVec{0, 3, 0}, "cross(Z,X)")

            + t.eq(cross(X, Z), TriVec{0, -3, 0}, "cross(X,Z)")
            + t.eq(cross(Y, X), TriVec{0, 0, -2}, "cross(Y,X)")
            + t.eq(cross(Z, Y), TriVec{-6, 0, 0}, "cross(Z,Y)");
}

static int test_matrix_trivec(Log &log) {

    /*
    ** Tests specific to the TriVec Class
    */
    Suite s(log, "Farsyte::Matrix::TriVec");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** the subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
            + test_matrix_trivec_meta(s)
            + test_matrix_trivec_ctor_eq_ne(s)
            + test_matrix_trivec_access(s)
            + test_matrix_trivec_add(s)
            + test_matrix_trivec_sub(s)
            + test_matrix_trivec_cross(s);

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
            + test_matrix_trivec(log);
}

int main(void) {

    ofstream xml("test_matrix_trivec_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix_trivec" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix_trivec" << endl;

    return 0;
}
