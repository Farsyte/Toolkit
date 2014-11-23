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

UT_CASE(Trivec, Meta) {

    EXPECT_EQ(TriVec::rows(), 3);                               // TriVec Rows
    EXPECT_EQ(TriVec::cols(), 1);                               // TriVec Cols
    EXPECT_EQ(TriVec::size(), 3);                               // TriVec Size
}

UT_CASE(TriVec, CtorEqNe) {

    TriVec D;
    TriVec X(1, 0, 0);
    TriVec Y(0, 1, 0);
    TriVec Z(0, 0, 1);

    EXPECT_NE((bool)0, (bool)(D == D));                         // (D == D) is True
    EXPECT_NE((bool)0, (bool)(X == X));                         // (X == X) is True
    EXPECT_NE((bool)0, (bool)(Y == Y));                         // (Y == Y) is True
    EXPECT_NE((bool)0, (bool)(Z == Z));                         // (Z == Z) is True

    EXPECT_NE((bool)0, (bool)(D != X));                         // (D != X) is True
    EXPECT_NE((bool)0, (bool)(D != Y));                         // (D != Y) is True
    EXPECT_NE((bool)0, (bool)(D != Z));                         // (D != Z) is True
    EXPECT_NE((bool)0, (bool)(X != D));                         // (X != D) is True
    EXPECT_NE((bool)0, (bool)(X != Y));                         // (X != Y) is True
    EXPECT_NE((bool)0, (bool)(X != Z));                         // (X != Z) is True
    EXPECT_NE((bool)0, (bool)(Y != D));                         // (Y != D) is True
    EXPECT_NE((bool)0, (bool)(Y != X));                         // (Y != X) is True
    EXPECT_NE((bool)0, (bool)(Y != Z));                         // (Y != Z) is True
    EXPECT_NE((bool)0, (bool)(Z != D));                         // (Z != D) is True
    EXPECT_NE((bool)0, (bool)(Z != X));                         // (Z != X) is True
    EXPECT_NE((bool)0, (bool)(Z != Y));                         // (Z != Y) is True

    EXPECT_EQ((bool)0, (bool)(D != D));                         // (D != D) is False
    EXPECT_EQ((bool)0, (bool)(X != X));                         // (X != X) is False
    EXPECT_EQ((bool)0, (bool)(Y != Y));                         // (Y != Y) is False
    EXPECT_EQ((bool)0, (bool)(Z != Z));                         // (Z != Z) is False

    EXPECT_EQ((bool)0, (bool)(D == X));                         // (D == X) is False
    EXPECT_EQ((bool)0, (bool)(D == Y));                         // (D == Y) is False
    EXPECT_EQ((bool)0, (bool)(D == Z));                         // (D == Z) is False
    EXPECT_EQ((bool)0, (bool)(X == D));                         // (X == D) is False
    EXPECT_EQ((bool)0, (bool)(X == Y));                         // (X == Y) is False
    EXPECT_EQ((bool)0, (bool)(X == Z));                         // (X == Z) is False
    EXPECT_EQ((bool)0, (bool)(Y == D));                         // (Y == D) is False
    EXPECT_EQ((bool)0, (bool)(Y == X));                         // (Y == X) is False
    EXPECT_EQ((bool)0, (bool)(Y == Z));                         // (Y == Z) is False
    EXPECT_EQ((bool)0, (bool)(Z == D));                         // (Z == D) is False
    EXPECT_EQ((bool)0, (bool)(Z == X));                         // (Z == X) is False
    EXPECT_EQ((bool)0, (bool)(Z == Y));                         // (Z == Y) is False
}

UT_CASE(TriVec, AccessUpdate) {

    TriVec V(3, 5, 7);

    V[1] = 4;
    V[2] = V[0];

    EXPECT_EQ(V, (TriVec(3, 4, 3)));                            // Vector after access and update
}

UT_CASE(TriVec, Add) {

    TriVec A(7, 4, 1);
    TriVec I(1, 2, 3);
    A += I;

    EXPECT_EQ(I, (TriVec(1, 2, 3)));                            // I unchanged
    EXPECT_EQ(A, (TriVec(8, 6, 4)));                            // A incremented once
    EXPECT_EQ(A + I, (TriVec(9, 8, 7)));                        // Second Sum
    EXPECT_EQ(A + (-I), (TriVec(7, 4, 1)));                     // Add Negative
}

UT_CASE(TriVec, Sub) {

    TriVec D;
    TriVec A(9, 8, 7);
    TriVec I(1, 2, 3);
    A -= I;

    EXPECT_EQ(I, (TriVec(1, 2, 3)));                            // I unchanged
    EXPECT_EQ(A, (TriVec(8, 6, 4)));                            // A decremented once
    EXPECT_EQ(A - I, (TriVec(7, 4, 1)));                        // second difference
    EXPECT_EQ(A - (-I), (TriVec(9, 8, 7)));                     // Sub Negative
}

UT_CASE(TriVec, Cross) {

    TriVec X(1, 0, 0);
    TriVec Y(0, 2, 0);
    TriVec Z(0, 0, 3);

    EXPECT_EQ(cross(X, X), (TriVec(0, 0, 0)));                  // cross(X,X)
    EXPECT_EQ(cross(Y, Y), (TriVec(0, 0, 0)));                  // cross(Y,Y)
    EXPECT_EQ(cross(Z, Z), (TriVec(0, 0, 0)));                  // cross(Z,Z)

    EXPECT_EQ(cross(X, Y), (TriVec(0, 0, 2)));                  // cross(X,Y)
    EXPECT_EQ(cross(Y, Z), (TriVec(6, 0, 0)));                  // cross(Y,Z)
    EXPECT_EQ(cross(Z, X), (TriVec(0, 3, 0)));                  // cross(Z,X)

    EXPECT_EQ(cross(X, Z), (TriVec(0, -3, 0)));                 // cross(X,Z)
    EXPECT_EQ(cross(Y, X), (TriVec(0, 0, -2)));                 // cross(Y,X)
    EXPECT_EQ(cross(Z, Y), (TriVec(-6, 0, 0)));                 // cross(Z,Y)
}
