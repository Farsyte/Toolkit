#include "matrix.h"
#include "testing.h"
#include "utility.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Farsyte::Matrix::ColVec;
using Farsyte::Matrix::Matrix;
using Farsyte::Matrix::ThreeVec;
using Farsyte::Testing::Log;
using Farsyte::Testing::Oops;
using Farsyte::Testing::Suite;
using Farsyte::Testing::Test;
using std::cout;
using std::endl;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::setw;
using std::string;
using std::vector;

/** Pick a specific ColVec for primary ColVec testing. */
typedef ColVec<4,int>   ColVec4i;

ColVec4i FourVec(int w, int x, int y, int z) {
  typedef typename ColVec4i::A A;
  return A {w, x, y, z};
}

/** Pick a specific ColVec for primary ColVec testing. */
typedef Matrix<3,2,int> Matrix23i;

Matrix23i RectMat(
  int a, int b, int c,
  int d, int e, int f)
{
  typedef typename Matrix23i::A A;
  return A {a,b,c, d,e,f};
}

/** Need the type of the transpose as well. */
typedef Matrix<2,3,int> Matrix32i;

Matrix32i RectMatT(
  int a, int b,
  int c, int d,
  int e, int f)
{
  typedef typename Matrix32i::A A;
  return A { a,b, c,d, e,f };
}

/** Types needed for matrix products. */
typedef Matrix<2,2,int> Matrix22i;

Matrix22i SquareMat2(
  int a, int b,
  int c, int d)
{
  typedef typename Matrix22i::A A;
  return A {a,b, c,d};
}

typedef Matrix<3,3,int> Matrix33i;

Matrix33i SquareMat3(
  int a, int b, int c,
  int d, int e, int f,
  int g, int h, int i)
{
  typedef typename Matrix33i::A A;
  return A {a,b,c, d,e,f, g,h,i};
}

template<typename T>
int case_equals(
  Test &t, string const &title,
  T const & exp,
  T const & act)
{

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

int case_T(
  Test &t, string const &title,
  bool cond)
{
  t << title << endl;
  if (cond) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int case_F(
  Test &t, string const &title,
  bool cond)
{
  t << title << endl;
  if (!cond) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int case_equals(
  Test &t, string const &title,
  double x, double y, double z,
  ThreeVec const &r)
{

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

int case_equals(
  Test &t, string const &title,
  int w, int x, int y, int z,
  ColVec4i const &r)
{

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

int case_equals(
  Test &t, string const &title,
  int a, int b,
  int c, int d,
  Matrix22i const &M)
{

  t << title << endl
    << "      expected                observed\n"
    << "    ____    ____            ____    ____\n"
    << setw(8) << a
    << setw(8) << b
    << setw(8) << " "
    << setw(8) << M(0,0)
    << setw(8) << M(0,1)
    << endl
    << setw(8) << c
    << setw(8) << d
    << setw(8) << " "
    << setw(8) << M(1,0)
    << setw(8) << M(1,1)
    << endl;
  if ((a == M(0,0)) && (b == M(0,1)) &&
      (c == M(1,0)) && (d == M(1,1))) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int case_equals(
  Test &t, string const &title,
  int a, int b, int c,
  int d, int e, int f,
  Matrix23i const &M)
{

  t << title << endl
    << "          expected                        observed\n"
    << "    ____    ____    ____            ____    ____    ____\n"
    << setw(8) << a
    << setw(8) << b
    << setw(8) << c
    << setw(8) << " "
    << setw(8) << M(0,0)
    << setw(8) << M(0,1)
    << setw(8) << M(0,2)
    << endl
    << setw(8) << d
    << setw(8) << e
    << setw(8) << f
    << setw(8) << " "
    << setw(8) << M(1,0)
    << setw(8) << M(1,1)
    << setw(8) << M(1,2)
    << endl;
  if ((a == M(0,0)) && (b == M(0,1)) && (c == M(0,2)) &&
      (d == M(1,0)) && (e == M(1,1)) && (f == M(1,2))) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int case_equals(
  Test &t, string const &title,
  int a, int b,
  int c, int d,
  int e, int f,
  Matrix32i const &M)
{

  t << title << endl
    << "      expected                observed\n"
    << "    ____    ____            ____    ____\n"
    << setw(8) << a
    << setw(8) << b
    << setw(8) << " "
    << setw(8) << M(0,0)
    << setw(8) << M(0,1)
    << endl
    << setw(8) << c
    << setw(8) << d
    << setw(8) << " "
    << setw(8) << M(1,0)
    << setw(8) << M(1,1)
    << endl
    << setw(8) << e
    << setw(8) << f
    << setw(8) << " "
    << setw(8) << M(2,0)
    << setw(8) << M(2,1)
    << endl;
  if ((a == M(0,0)) && (b == M(0,1)) &&
      (c == M(1,0)) && (d == M(1,1)) &&
      (e == M(2,0)) && (f == M(2,1))) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

int case_equals(
  Test &t, string const &title,
  int a, int b, int c,
  int d, int e, int f,
  int g, int h, int i,
  Matrix33i const &M)
{

  t << title << endl
    << "          expected                        observed\n"
    << "    ____    ____    ____            ____    ____    ____\n"
    << setw(8) << a
    << setw(8) << b
    << setw(8) << c
    << setw(8) << " "
    << setw(8) << M(0,0)
    << setw(8) << M(0,1)
    << setw(8) << M(0,2)
    << endl
    << setw(8) << d
    << setw(8) << e
    << setw(8) << f
    << setw(8) << " "
    << setw(8) << M(1,0)
    << setw(8) << M(1,1)
    << setw(8) << M(1,2)
    << endl
    << setw(8) << g
    << setw(8) << h
    << setw(8) << i
    << setw(8) << " "
    << setw(8) << M(2,0)
    << setw(8) << M(2,1)
    << setw(8) << M(2,2)
    << endl;
  if ((a == M(0,0)) && (b == M(0,1)) && (c == M(0,2)) &&
      (d == M(1,0)) && (e == M(1,1)) && (f == M(1,2)) &&
      (g == M(2,0)) && (h == M(2,1)) && (i == M(2,2))) {
    t.pass(title);
    return 0;
  } else {
    t.fail(title + " failed");
    return 1;
  }
}

/* -- ================================================================ -- */

int test_matrix_version(Log &l) {
  Suite s(l, "Farsyte::Matrix::Version");
  Test t(s, "Version Comparison");

  return 0
    + case_equals(t, "version string compare",
                  string(_matrix_h),
                  Farsyte::Matrix::matrix_version())
    ;
}

/* -- ================================================================ -- */

int test_matrix_threevec_meta(Suite &s) {

  Test t(s, "Class Parameter Methods");

  return 0
    + case_equals(t, "ThreeVec Rows", 3, ThreeVec::rows())
    + case_equals(t, "ThreeVec Cols", 1, ThreeVec::cols())
    + case_equals(t, "ThreeVec Size", 3, ThreeVec::size())
    ;
}

int test_matrix_threevec_ctor_eq_ne(Suite &s) {

  Test t(s, "Construct and Compare");

  ThreeVec D;
  ThreeVec X {1,0,0};
  ThreeVec Y {0,1,0};
  ThreeVec Z {0,0,1};

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
    + case_F(t, "(Z == Y) is False", (Z == Y))
    ;
}

int test_matrix_threevec_access(Suite &s) {

  Test t(s, "Member Access and Update");

  ThreeVec V {3,5,7};

  V[1] = 4;
  V[2] = V[0];

  return 0
    + case_equals(t, "Vector after access and update", 3,4,3, V)
    ;
}

int test_matrix_threevec_add(Suite &s) {

  Test t(s, "Addition");

  ThreeVec S;
  ThreeVec A {7,4,1};
  ThreeVec I {1,2,3};
  A += I;

  return 0
    + case_equals(t, "I unchanged", 1, 2, 3, I)
    + case_equals(t, "A incremented once", 8, 6, 4, A)
    + case_equals(t, "Second Sum", 9, 8, 7, A+I)
    + case_equals(t, "Add Negative", 7, 4, 1, A+(-I))
    ;
}

int test_matrix_threevec_sub(Suite &s) {

  Test t(s, "Difference");

  ThreeVec D;
  ThreeVec A {9,8,7};
  ThreeVec I {1,2,3};
  A -= I;

  return 0
    + case_equals(t, "I unchanged", 1, 2, 3, I)
    + case_equals(t, "A decremented once", 8, 6, 4, A)
    + case_equals(t, "second difference", 7, 4, 1, A-I)
    + case_equals(t, "Sub Negative", 9, 8, 7, A-(-I))
    ;
}

int test_matrix_threevec_cross(Suite &s) {

  Test t(s, "Construct and Compare");

  ThreeVec X {1,0,0};
  ThreeVec Y {0,2,0};
  ThreeVec Z {0,0,3};

  return 0
    + case_equals(t, "cross(X,X)", 0, 0, 0, cross(X,X))
    + case_equals(t, "cross(Y,Y)", 0, 0, 0, cross(Y,Y))
    + case_equals(t, "cross(Z,Z)", 0, 0, 0, cross(Z,Z))

    + case_equals(t, "cross(X,Y)", 0, 0, 2, cross(X,Y))
    + case_equals(t, "cross(Y,Z)", 6, 0, 0, cross(Y,Z))
    + case_equals(t, "cross(Z,X)", 0, 3, 0, cross(Z,X))

    + case_equals(t, "cross(X,Z)", 0,-3, 0, cross(X,Z))
    + case_equals(t, "cross(Y,X)", 0, 0,-2, cross(Y,X))
    + case_equals(t, "cross(Z,Y)",-6, 0, 0, cross(Z,Y))
    ;
}

int test_matrix_threevec(Log &log) {

  /*
  ** Tests specific to the ThreeVec Class
  */
  Suite               s(log, "Farsyte::Matrix::ThreeVec");

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
    + test_matrix_threevec_cross(s)
    ;

}

/* -- ================================================================ -- */

int test_matrix_colvec_meta(Suite &s) {

  Test t(s, "Class Parameter Methods");

  return 0
    + case_equals(t, "ColVec Rows", 4, ColVec4i::rows())
    + case_equals(t, "ColVec Cols", 1, ColVec4i::cols())
    + case_equals(t, "ColVec Size", 4, ColVec4i::size())
    ;
}

int test_matrix_colvec_ctor_eq_ne(Suite &s) {

  Test t(s, "Construct and Compare");

  ColVec4i D;
  ColVec4i W (FourVec(1,0,0,0));
  ColVec4i X (FourVec(0,1,0,0));
  ColVec4i Y (FourVec(0,0,1,0));
  ColVec4i Z (FourVec(0,0,0,1));

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
    + case_F(t, "(Z == Y) is False", (Z == Y))
    ;
}

int test_matrix_colvec_access(Suite &s) {

  Test t(s, "Member Access and Update");

  ColVec4i V (FourVec(1,3,5,7));

  V[2] = 4;
  V[3] = V[0];

  return 0
    + case_equals(t, "Vector after access and update", 1,3,4,1, V)
    ;
}

int test_matrix_colvec_add(Suite &s) {

  Test t(s, "Addition");

  ColVec4i S;
  ColVec4i A = FourVec(10,7,4,1);
  ColVec4i I = FourVec(1,2,3,4);
  A += I;

  return 0
    + case_equals(t, "I unchanged", 1, 2, 3, 4, I)
    + case_equals(t, "A incremented once", 11, 9, 7, 5, A)
    + case_equals(t, "Second Sum", 12, 11, 10, 9, A+I)
    + case_equals(t, "Add Negative", 10, 7, 4, 1, A+(-I))
    ;
}

int test_matrix_colvec_sub(Suite &s) {

  Test t(s, "Difference");

  ColVec4i D;
  ColVec4i A = FourVec(9,8,7,6);
  ColVec4i I = FourVec(1,2,3,4);
  A -= I;

  return 0
    + case_equals(t, "I unchanged", 1, 2, 3, 4, I)
    + case_equals(t, "A decremented once", 8, 6, 4, 2, A)
    + case_equals(t, "second difference", 7, 4, 1, -2, A-I)
    + case_equals(t, "Sub Negative", 9, 8, 7, 6, A-(-I))
    ;
}

int test_matrix_colvec(Log &log) {

  /*
  ** Tests specific to the ColVec Template
  */
  Suite               s(log, "Farsyte::Matrix::ColVec");

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
    + test_matrix_colvec_sub(s)
    ;

}

/* -- ================================================================ -- */

int test_matrix_matrix_meta(Suite &s) {

  Test t(s, "Class Parameter Methods");

  return 0
    + case_equals(t, "Matrix Rows", 2, Matrix23i::rows())
    + case_equals(t, "Matrix Cols", 3, Matrix23i::cols())
    + case_equals(t, "Matrix Size", 6, Matrix23i::size())
    ;
}

int test_matrix_matrix_ctor_eq_ne(Suite &s) {

  Test t(s, "Construct and Compare");
  Matrix23i I;
  Matrix23i A = RectMat(1,0, 0,0, 0,0);
  Matrix23i B = RectMat(0,1, 0,0, 0,0);
  Matrix23i C = RectMat(0,0, 1,0, 0,0);
  Matrix23i D = RectMat(0,0, 0,1, 0,0);
  Matrix23i E = RectMat(0,0, 0,0, 1,0);
  Matrix23i F = RectMat(0,0, 0,0, 0,1);

  return 0
    + case_equals(t, "Default initialized to Zero", 0,0, 0,0, 0,0, I)
    + case_equals(t, "A Cell Initialization", 1,0, 0,0, 0,0, A)
    + case_equals(t, "B Cell Initialization", 0,1, 0,0, 0,0, B)
    + case_equals(t, "C Cell Initialization", 0,0, 1,0, 0,0, C)
    + case_equals(t, "D Cell Initialization", 0,0, 0,1, 0,0, D)
    + case_equals(t, "E Cell Initialization", 0,0, 0,0, 1,0, E)
    + case_equals(t, "F Cell Initialization", 0,0, 0,0, 0,1, F)

    + case_T(t, "(I == I) is True",  (I == I))
    + case_F(t, "(I != I) is False", (I != I))
    + case_T(t, "(I != A) is True",  (I != A))
    + case_F(t, "(I == I) is False", (I == A))
    + case_T(t, "(I != B) is True",  (I != B))
    + case_F(t, "(I == I) is False", (I == B))
    + case_T(t, "(I != C) is True",  (I != C))
    + case_F(t, "(I == I) is False", (I == C))
    + case_T(t, "(I != D) is True",  (I != D))
    + case_F(t, "(I == I) is False", (I == D))
    + case_T(t, "(I != E) is True",  (I != E))
    + case_F(t, "(I == I) is False", (I == E))
    + case_T(t, "(I != F) is True",  (I != F))
    + case_F(t, "(I == I) is False", (I == F))

    + case_T(t, "(A == A) is True",  (A == A))
    + case_F(t, "(A != A) is False", (A != A))
    + case_T(t, "(A != I) is True",  (A != I))
    + case_F(t, "(A == A) is False", (A == I))
    + case_T(t, "(A != B) is True",  (A != B))
    + case_F(t, "(A == A) is False", (A == B))
    + case_T(t, "(A != C) is True",  (A != C))
    + case_F(t, "(A == A) is False", (A == C))
    + case_T(t, "(A != D) is True",  (A != D))
    + case_F(t, "(A == A) is False", (A == D))
    + case_T(t, "(A != E) is True",  (A != E))
    + case_F(t, "(A == A) is False", (A == E))
    + case_T(t, "(A != F) is True",  (A != F))
    + case_F(t, "(A == A) is False", (A == F))

    + case_T(t, "(B == B) is True",  (B == B))
    + case_F(t, "(B != B) is False", (B != B))
    + case_T(t, "(B != I) is True",  (B != I))
    + case_F(t, "(B == B) is False", (B == I))
    + case_T(t, "(B != A) is True",  (B != A))
    + case_F(t, "(B == B) is False", (B == A))
    + case_T(t, "(B != C) is True",  (B != C))
    + case_F(t, "(B == B) is False", (B == C))
    + case_T(t, "(B != D) is True",  (B != D))
    + case_F(t, "(B == B) is False", (B == D))
    + case_T(t, "(B != E) is True",  (B != E))
    + case_F(t, "(B == B) is False", (B == E))
    + case_T(t, "(B != F) is True",  (B != F))
    + case_F(t, "(B == B) is False", (B == F))

    + case_T(t, "(C == C) is True",  (C == C))
    + case_F(t, "(C != C) is False", (C != C))
    + case_T(t, "(C != I) is True",  (C != I))
    + case_F(t, "(C == C) is False", (C == I))
    + case_T(t, "(C != A) is True",  (C != A))
    + case_F(t, "(C == C) is False", (C == A))
    + case_T(t, "(C != B) is True",  (C != B))
    + case_F(t, "(C == C) is False", (C == B))
    + case_T(t, "(C != D) is True",  (C != D))
    + case_F(t, "(C == C) is False", (C == D))
    + case_T(t, "(C != E) is True",  (C != E))
    + case_F(t, "(C == C) is False", (C == E))
    + case_T(t, "(C != F) is True",  (C != F))
    + case_F(t, "(C == C) is False", (C == F))

    + case_T(t, "(D == D) is True",  (D == D))
    + case_F(t, "(D != D) is False", (D != D))
    + case_T(t, "(D != I) is True",  (D != I))
    + case_F(t, "(D == D) is False", (D == I))
    + case_T(t, "(D != A) is True",  (D != A))
    + case_F(t, "(D == D) is False", (D == A))
    + case_T(t, "(D != B) is True",  (D != B))
    + case_F(t, "(D == D) is False", (D == B))
    + case_T(t, "(D != C) is True",  (D != C))
    + case_F(t, "(D == D) is False", (D == C))
    + case_T(t, "(D != E) is True",  (D != E))
    + case_F(t, "(D == D) is False", (D == E))
    + case_T(t, "(D != F) is True",  (D != F))
    + case_F(t, "(D == D) is False", (D == F))

    + case_T(t, "(E == E) is True",  (E == E))
    + case_F(t, "(E != E) is False", (E != E))
    + case_T(t, "(E != I) is True",  (E != I))
    + case_F(t, "(E == E) is False", (E == I))
    + case_T(t, "(E != A) is True",  (E != A))
    + case_F(t, "(E == E) is False", (E == A))
    + case_T(t, "(E != B) is True",  (E != B))
    + case_F(t, "(E == E) is False", (E == B))
    + case_T(t, "(E != C) is True",  (E != C))
    + case_F(t, "(E == E) is False", (E == C))
    + case_T(t, "(E != D) is True",  (E != D))
    + case_F(t, "(E == E) is False", (E == D))
    + case_T(t, "(E != F) is True",  (E != F))
    + case_F(t, "(E == E) is False", (E == F))

    + case_T(t, "(F == F) is True",  (F == F))
    + case_F(t, "(F != F) is False", (F != F))
    + case_T(t, "(F != I) is True",  (F != I))
    + case_F(t, "(F == F) is False", (F == I))
    + case_T(t, "(F != A) is True",  (F != A))
    + case_F(t, "(F == F) is False", (F == A))
    + case_T(t, "(F != B) is True",  (F != B))
    + case_F(t, "(F == F) is False", (F == B))
    + case_T(t, "(F != C) is True",  (F != C))
    + case_F(t, "(F == F) is False", (F == C))
    + case_T(t, "(F != D) is True",  (F != D))
    + case_F(t, "(F == F) is False", (F == D))
    + case_T(t, "(F != E) is True",  (F != E))
    + case_F(t, "(F == F) is False", (F == E))

    ;
}

int test_matrix_matrix_access(Suite &s) {

  Test t(s, "Member Access and Update");

  Matrix23i V = RectMat(1,3,5, 2,4,6);

  V(1,1) = 8;
  V(1,2) = V(0,0);

  return 0
    + case_equals(t, "Matrix after access and update", 1,3,5, 2,8,1, V)
    ;
}

int test_matrix_matrix_add(Suite &s) {

  Test t(s, "Addition");

  Matrix23i S;
  Matrix23i A = RectMat(16,13,10,7,4,1);
  Matrix23i I = RectMat(1,2,3,4,5,6);
  A += I;

  return 0
    + case_equals(t, "I unchanged", 1,2,3, 4,5,6, I)
    + case_equals(t, "A incremented once", 17,15,13, 11,9,7, A)
    + case_equals(t, "Second Sum", 18,17,16, 15,14,13, A+I)
    + case_equals(t, "Add Negative", 16,13,10,7,4,1, A+(-I))
    ;
}

int test_matrix_matrix_sub(Suite &s) {

  Test t(s, "Difference");

  Matrix23i D;
  Matrix23i A = RectMat(18,17,16,15,14,13);
  Matrix23i I = RectMat(1,2,3,4,5,6);
  A -= I;

  return 0
    + case_equals(t, "I unchanged", 1,2,3, 4,5,6, I)
    + case_equals(t, "A decremented once", 17,15,13,11,9,7,A)
    + case_equals(t, "second difference", 16,13,10,7,4,1,A-I)
    + case_equals(t, "Sub Negative", 18,17,16,15,14,13, A-(-I))
    ;
}

int test_matrix_matrix_mul(Suite &s) {

  Test t(s, "Product (and transpose)");

  Matrix23i A = RectMat(13,69,32, 82,21,20);
  Matrix23i B = RectMat(91,26,69, 25,22,41);

  return 0
    + case_equals(t, "A*~B",
                  5185, 3155,
                  9388, 3332, A*~B)

    + case_equals(t, "~A*B",
                  3233, 2142, 4259,
                  6804, 2256, 5622,
                  3412, 1272, 3028, ~A*B)
    ;
}

int test_matrix_matrix(Log &log) {

  /*
  ** Tests specific to the Matrix Template
  */
  Suite               s(log, "Farsyte::Matrix::Matrix");

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
    ;

}

/* -- ================================================================ -- */

int test_matrix(Log &log) {
  /*
  ** return convention: 0 is success, nonzero is failure.
  ** The subtests of this unit are sequentially independent;
  ** use boolean '|' operator to run multiple tests
  ** and return fail if any failed, after running all.
  */
  return 0
    + test_matrix_version(log)
    + test_matrix_threevec(log)
    + test_matrix_colvec(log)
    + test_matrix_matrix(log)
    ;
}

int main(void) {

  Log                 log(cout, "Matrix Library");

  int ec = test_matrix(log);

  if (ec)
    fprintf(stderr, "%7d FAIL test_matrix\n", ec);
  else
    fprintf(stderr, "%7d PASS test_matrix\n", ec);

  return 0;
}
