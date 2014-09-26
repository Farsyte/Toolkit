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
        int a, int b,
        int c, int d,
        Matrix22i const &M) {

    t << title << endl
            << "      expected                observed\n"
            << "    ____    ____            ____    ____\n"
            << setw(8) << a
            << setw(8) << b
            << setw(8) << " "
            << setw(8) << M(0, 0)
            << setw(8) << M(0, 1)
            << endl
            << setw(8) << c
            << setw(8) << d
            << setw(8) << " "
            << setw(8) << M(1, 0)
            << setw(8) << M(1, 1)
            << endl;
    if ((a == M(0, 0)) && (b == M(0, 1)) &&
            (c == M(1, 0)) && (d == M(1, 1))) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

static int case_equals(
        Test &t, string const &title,
        int a, int b, int c,
        int d, int e, int f,
        Matrix23i const &M) {

    t << title << endl
            << "          expected                        observed\n"
            << "    ____    ____    ____            ____    ____    ____\n"
            << setw(8) << a
            << setw(8) << b
            << setw(8) << c
            << setw(8) << " "
            << setw(8) << M(0, 0)
            << setw(8) << M(0, 1)
            << setw(8) << M(0, 2)
            << endl
            << setw(8) << d
            << setw(8) << e
            << setw(8) << f
            << setw(8) << " "
            << setw(8) << M(1, 0)
            << setw(8) << M(1, 1)
            << setw(8) << M(1, 2)
            << endl;
    if ((a == M(0, 0)) && (b == M(0, 1)) && (c == M(0, 2)) &&
            (d == M(1, 0)) && (e == M(1, 1)) && (f == M(1, 2))) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

static int case_equals(
        Test &t, string const &title,
        int a, int b, int c,
        int d, int e, int f,
        int g, int h, int i,
        Matrix33i const &M) {

    t << title << endl
            << "          expected                        observed\n"
            << "    ____    ____    ____            ____    ____    ____\n"
            << setw(8) << a
            << setw(8) << b
            << setw(8) << c
            << setw(8) << " "
            << setw(8) << M(0, 0)
            << setw(8) << M(0, 1)
            << setw(8) << M(0, 2)
            << endl
            << setw(8) << d
            << setw(8) << e
            << setw(8) << f
            << setw(8) << " "
            << setw(8) << M(1, 0)
            << setw(8) << M(1, 1)
            << setw(8) << M(1, 2)
            << endl
            << setw(8) << g
            << setw(8) << h
            << setw(8) << i
            << setw(8) << " "
            << setw(8) << M(2, 0)
            << setw(8) << M(2, 1)
            << setw(8) << M(2, 2)
            << endl;
    if ((a == M(0, 0)) && (b == M(0, 1)) && (c == M(0, 2)) &&
            (d == M(1, 0)) && (e == M(1, 1)) && (f == M(1, 2)) &&
            (g == M(2, 0)) && (h == M(2, 1)) && (i == M(2, 2))) {
        t.pass(title);
        return 0;
    } else {
        t.fail(title + " failed");
        return 1;
    }
}

/* -- ================================================================ -- */

static int test_matrix_matrix_meta(Suite &s) {

    Test t(s, "Class Parameter Methods");

    return 0
            + case_equals(t, "Matrix Rows", 2, Matrix23i::rows())
            + case_equals(t, "Matrix Cols", 3, Matrix23i::cols())
            + case_equals(t, "Matrix Size", 6, Matrix23i::size());
}

static int test_matrix_matrix_ctor_eq_ne(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Construct and Compare");
    Matrix23i I;
    Matrix23i A = IV {1, 0, 0, 0, 0, 0};
    Matrix23i B = IV {0, 1, 0, 0, 0, 0};
    Matrix23i C = IV {0, 0, 1, 0, 0, 0};
    Matrix23i D = IV {0, 0, 0, 1, 0, 0};
    Matrix23i E = IV {0, 0, 0, 0, 1, 0};
    Matrix23i F = IV {0, 0, 0, 0, 0, 1};

    return 0
            + case_equals(t, "Default initialized to Zero", 0, 0, 0, 0, 0, 0, I)
            + case_equals(t, "A Cell Initialization", 1, 0, 0, 0, 0, 0, A)
            + case_equals(t, "B Cell Initialization", 0, 1, 0, 0, 0, 0, B)
            + case_equals(t, "C Cell Initialization", 0, 0, 1, 0, 0, 0, C)
            + case_equals(t, "D Cell Initialization", 0, 0, 0, 1, 0, 0, D)
            + case_equals(t, "E Cell Initialization", 0, 0, 0, 0, 1, 0, E)
            + case_equals(t, "F Cell Initialization", 0, 0, 0, 0, 0, 1, F)

            + case_T(t, "(I == I) is True", (I == I))
            + case_F(t, "(I != I) is False", (I != I))
            + case_T(t, "(I != A) is True", (I != A))
            + case_F(t, "(I == I) is False", (I == A))
            + case_T(t, "(I != B) is True", (I != B))
            + case_F(t, "(I == I) is False", (I == B))
            + case_T(t, "(I != C) is True", (I != C))
            + case_F(t, "(I == I) is False", (I == C))
            + case_T(t, "(I != D) is True", (I != D))
            + case_F(t, "(I == I) is False", (I == D))
            + case_T(t, "(I != E) is True", (I != E))
            + case_F(t, "(I == I) is False", (I == E))
            + case_T(t, "(I != F) is True", (I != F))
            + case_F(t, "(I == I) is False", (I == F))

            + case_T(t, "(A == A) is True", (A == A))
            + case_F(t, "(A != A) is False", (A != A))
            + case_T(t, "(A != I) is True", (A != I))
            + case_F(t, "(A == A) is False", (A == I))
            + case_T(t, "(A != B) is True", (A != B))
            + case_F(t, "(A == A) is False", (A == B))
            + case_T(t, "(A != C) is True", (A != C))
            + case_F(t, "(A == A) is False", (A == C))
            + case_T(t, "(A != D) is True", (A != D))
            + case_F(t, "(A == A) is False", (A == D))
            + case_T(t, "(A != E) is True", (A != E))
            + case_F(t, "(A == A) is False", (A == E))
            + case_T(t, "(A != F) is True", (A != F))
            + case_F(t, "(A == A) is False", (A == F))

            + case_T(t, "(B == B) is True", (B == B))
            + case_F(t, "(B != B) is False", (B != B))
            + case_T(t, "(B != I) is True", (B != I))
            + case_F(t, "(B == B) is False", (B == I))
            + case_T(t, "(B != A) is True", (B != A))
            + case_F(t, "(B == B) is False", (B == A))
            + case_T(t, "(B != C) is True", (B != C))
            + case_F(t, "(B == B) is False", (B == C))
            + case_T(t, "(B != D) is True", (B != D))
            + case_F(t, "(B == B) is False", (B == D))
            + case_T(t, "(B != E) is True", (B != E))
            + case_F(t, "(B == B) is False", (B == E))
            + case_T(t, "(B != F) is True", (B != F))
            + case_F(t, "(B == B) is False", (B == F))

            + case_T(t, "(C == C) is True", (C == C))
            + case_F(t, "(C != C) is False", (C != C))
            + case_T(t, "(C != I) is True", (C != I))
            + case_F(t, "(C == C) is False", (C == I))
            + case_T(t, "(C != A) is True", (C != A))
            + case_F(t, "(C == C) is False", (C == A))
            + case_T(t, "(C != B) is True", (C != B))
            + case_F(t, "(C == C) is False", (C == B))
            + case_T(t, "(C != D) is True", (C != D))
            + case_F(t, "(C == C) is False", (C == D))
            + case_T(t, "(C != E) is True", (C != E))
            + case_F(t, "(C == C) is False", (C == E))
            + case_T(t, "(C != F) is True", (C != F))
            + case_F(t, "(C == C) is False", (C == F))

            + case_T(t, "(D == D) is True", (D == D))
            + case_F(t, "(D != D) is False", (D != D))
            + case_T(t, "(D != I) is True", (D != I))
            + case_F(t, "(D == D) is False", (D == I))
            + case_T(t, "(D != A) is True", (D != A))
            + case_F(t, "(D == D) is False", (D == A))
            + case_T(t, "(D != B) is True", (D != B))
            + case_F(t, "(D == D) is False", (D == B))
            + case_T(t, "(D != C) is True", (D != C))
            + case_F(t, "(D == D) is False", (D == C))
            + case_T(t, "(D != E) is True", (D != E))
            + case_F(t, "(D == D) is False", (D == E))
            + case_T(t, "(D != F) is True", (D != F))
            + case_F(t, "(D == D) is False", (D == F))

            + case_T(t, "(E == E) is True", (E == E))
            + case_F(t, "(E != E) is False", (E != E))
            + case_T(t, "(E != I) is True", (E != I))
            + case_F(t, "(E == E) is False", (E == I))
            + case_T(t, "(E != A) is True", (E != A))
            + case_F(t, "(E == E) is False", (E == A))
            + case_T(t, "(E != B) is True", (E != B))
            + case_F(t, "(E == E) is False", (E == B))
            + case_T(t, "(E != C) is True", (E != C))
            + case_F(t, "(E == E) is False", (E == C))
            + case_T(t, "(E != D) is True", (E != D))
            + case_F(t, "(E == E) is False", (E == D))
            + case_T(t, "(E != F) is True", (E != F))
            + case_F(t, "(E == E) is False", (E == F))

            + case_T(t, "(F == F) is True", (F == F))
            + case_F(t, "(F != F) is False", (F != F))
            + case_T(t, "(F != I) is True", (F != I))
            + case_F(t, "(F == F) is False", (F == I))
            + case_T(t, "(F != A) is True", (F != A))
            + case_F(t, "(F == F) is False", (F == A))
            + case_T(t, "(F != B) is True", (F != B))
            + case_F(t, "(F == F) is False", (F == B))
            + case_T(t, "(F != C) is True", (F != C))
            + case_F(t, "(F == F) is False", (F == C))
            + case_T(t, "(F != D) is True", (F != D))
            + case_F(t, "(F == F) is False", (F == D))
            + case_T(t, "(F != E) is True", (F != E))
            + case_F(t, "(F == F) is False", (F == E));
}

static int test_matrix_matrix_access(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Member Access and Update");

    Matrix23i A = IV {1, 3, 5, 2, 4, 6};

    A(1, 1) = 8;
    A(1, 2) = A(0, 0);

    return 0
            + case_equals(t, "Matrix after access and update", 1, 3, 5, 2, 8, 1, A);
}

static int test_matrix_matrix_add(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Addition");

    Matrix23i S;
    Matrix23i A = IV {16, 13, 10, 7, 4, 1};
    Matrix23i I = IV {1, 2, 3, 4, 5, 6};
    A += I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, 4, 5, 6, I)
            + case_equals(t, "A incremented once", 17, 15, 13, 11, 9, 7, A)
            + case_equals(t, "Second Sum", 18, 17, 16, 15, 14, 13, A + I)
            + case_equals(t, "Add Negative", 16, 13, 10, 7, 4, 1, A + (-I));
}

static int test_matrix_matrix_sub(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Difference");

    Matrix23i D;
    Matrix23i A = IV {18, 17, 16, 15, 14, 13};
    Matrix23i I = IV {1, 2, 3, 4, 5, 6};
    A -= I;

    return 0
            + case_equals(t, "I unchanged", 1, 2, 3, 4, 5, 6, I)
            + case_equals(t, "A decremented once", 17, 15, 13, 11, 9, 7, A)
            + case_equals(t, "second difference", 16, 13, 10, 7, 4, 1, A - I)
            + case_equals(t, "Sub Negative", 18, 17, 16, 15, 14, 13, A - (-I));
}

static int test_matrix_matrix_mul(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Product (and transpose)");

    Matrix23i A = IV {13, 69, 32, 82, 21, 20};
    Matrix23i B = IV {91, 26, 69, 25, 22, 41};

    return 0
            + case_equals(t, "A*~B",
            5185, 3155,
            9388, 3332, A * ~B)

            + case_equals(t, "~A*B",
            3233, 2142, 4259,
            6804, 2256, 5622,
            3412, 1272, 3028, ~A * B);
}

static int test_matrix_matrix_scale(Suite &s) {

    typedef Matrix23i::A IV;

    Test t(s, "Matrix Scaling Operations");

    Matrix23i A = IV {     3      ,      5      ,      7      ,      11      ,      13      ,      17     };
    Matrix23i B = IV {     3*23*3 ,      5*23*3 ,      7*23*3 ,      11*23*3 ,      13*23*3 ,      17*23*3};
    Matrix23i C = IV {2*27*3*23*3 , 2*27*5*23*3 , 2*27*7*23*3 , 2*27*11*23*3 , 2*27*13*23*3 , 2*27*17*23*3};
    Matrix23i D = IV {  27*3*23   ,   27*5*23   ,   27*7*23   ,   27*11*23   ,   27*13*23   ,   27*17*23  };

    return 0
      + t.eq(A * (23*3), B, "A * (23*3)")
      + t.eq((2*27) * B, C, "(2*27) * B")
      + t.eq(C / 6, D, "C / 6")
      ;
}

static int test_matrix_matrix(Log &log) {

    /*
    ** Tests specific to the Matrix Template
    */
    Suite s(log, "Farsyte::Matrix::Matrix");

    /*
    ** return convention: 0 is success, nonzero is failure.
    ** the subtests of this unit are sequentially independent;
    ** use boolean '|' operator to run multiple tests
    ** and return fail if any failed, after running all.
    */

    return 0
            + test_matrix_matrix_meta(s)
            + test_matrix_matrix_ctor_eq_ne(s)
            + test_matrix_matrix_access(s)
            + test_matrix_matrix_add(s)
            + test_matrix_matrix_sub(s)
            + test_matrix_matrix_mul(s)
            + test_matrix_matrix_scale(s);

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
            + test_matrix_matrix(log);
}

int main(void) {

    ofstream xml("test_matrix_matrix_log.xml");
    assert(xml);
    Log log(xml, "Matrix Library");

    int ec = test_matrix(log);

    if (ec)
        cerr << setw(7) << ec << " FAIL test_matrix_matrix" << endl;
    else
        cerr << setw(7) << ec << " PASS test_matrix_matrix" << endl;

    return 0;
}
