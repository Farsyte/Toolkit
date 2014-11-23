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

/** Corresponding 4x4 matrix */
typedef Matrix<4, 4, int> Mat4x4i;

/** Because ColVec<> initializers are harsh. */
static ColVec4i IV(int w, int x, int y, int z) {
    ColVec4i R;
    R[0] = w;
    R[1] = x;
    R[2] = y;
    R[3] = z;
    return R;
}

/* -- ================================================================ -- */

UT_CASE(ColVec, Meta) {

    EXPECT_EQ(ColVec4i::rows(), 4);             // ColVec Rows
    EXPECT_EQ(ColVec4i::cols(), 1);             // ColVec Cols
    EXPECT_EQ(ColVec4i::size(), 4);             // ColVec Size

}

UT_CASE(ColVec, CtorEqNe) {


    ColVec4i D;
    ColVec4i W = IV (1, 0, 0, 0);
    ColVec4i X = IV (0, 1, 0, 0);
    ColVec4i Y = IV (0, 0, 1, 0);
    ColVec4i Z = IV (0, 0, 0, 1);

    EXPECT_NE((bool)0, (bool)(D == D));         // (D == D) is True
    EXPECT_NE((bool)0, (bool)(W == W));         // (W == W) is True
    EXPECT_NE((bool)0, (bool)(X == X));         // (X == X) is True
    EXPECT_NE((bool)0, (bool)(Y == Y));         // (Y == Y) is True
    EXPECT_NE((bool)0, (bool)(Z == Z));         // (Z == Z) is True

    EXPECT_NE((bool)0, (bool)(D != W));         // (D != W) is True
    EXPECT_NE((bool)0, (bool)(D != X));         // (D != X) is True
    EXPECT_NE((bool)0, (bool)(D != Y));         // (D != Y) is True
    EXPECT_NE((bool)0, (bool)(D != Z));         // (D != Z) is True

    EXPECT_NE((bool)0, (bool)(W != D));         // (W != D) is True
    EXPECT_NE((bool)0, (bool)(W != X));         // (W != X) is True
    EXPECT_NE((bool)0, (bool)(W != Y));         // (W != Y) is True
    EXPECT_NE((bool)0, (bool)(W != Z));         // (W != Z) is True

    EXPECT_NE((bool)0, (bool)(X != D));         // (X != D) is True
    EXPECT_NE((bool)0, (bool)(X != W));         // (X != W) is True
    EXPECT_NE((bool)0, (bool)(X != Y));         // (X != Y) is True
    EXPECT_NE((bool)0, (bool)(X != Z));         // (X != Z) is True

    EXPECT_NE((bool)0, (bool)(Y != D));         // (Y != D) is True
    EXPECT_NE((bool)0, (bool)(Y != W));         // (Y != W) is True
    EXPECT_NE((bool)0, (bool)(Y != X));         // (Y != X) is True
    EXPECT_NE((bool)0, (bool)(Y != Z));         // (Y != Z) is True

    EXPECT_NE((bool)0, (bool)(Z != D));         // (Z != D) is True
    EXPECT_NE((bool)0, (bool)(Z != W));         // (Z != W) is True
    EXPECT_NE((bool)0, (bool)(Z != X));         // (Z != X) is True
    EXPECT_NE((bool)0, (bool)(Z != Y));         // (Z != Y) is True

    EXPECT_EQ((bool)0, (bool)(D != D));         // (D != D) is False
    EXPECT_EQ((bool)0, (bool)(W != W));         // (W != W) is False
    EXPECT_EQ((bool)0, (bool)(X != X));         // (X != X) is False
    EXPECT_EQ((bool)0, (bool)(Y != Y));         // (Y != Y) is False
    EXPECT_EQ((bool)0, (bool)(Z != Z));         // (Z != Z) is False

    EXPECT_EQ((bool)0, (bool)(D == W));         // (D == W) is False
    EXPECT_EQ((bool)0, (bool)(D == X));         // (D == X) is False
    EXPECT_EQ((bool)0, (bool)(D == Y));         // (D == Y) is False
    EXPECT_EQ((bool)0, (bool)(D == Z));         // (D == Z) is False

    EXPECT_EQ((bool)0, (bool)(W == D));         // (W == D) is False
    EXPECT_EQ((bool)0, (bool)(W == X));         // (W == X) is False
    EXPECT_EQ((bool)0, (bool)(W == Y));         // (W == Y) is False
    EXPECT_EQ((bool)0, (bool)(W == Z));         // (W == Z) is False

    EXPECT_EQ((bool)0, (bool)(X == D));         // (X == D) is False
    EXPECT_EQ((bool)0, (bool)(X == D));         // (X == W) is False
    EXPECT_EQ((bool)0, (bool)(X == Y));         // (X == Y) is False
    EXPECT_EQ((bool)0, (bool)(X == Z));         // (X == Z) is False

    EXPECT_EQ((bool)0, (bool)(Y == D));         // (Y == D) is False
    EXPECT_EQ((bool)0, (bool)(Y == W));         // (Y == W) is False
    EXPECT_EQ((bool)0, (bool)(Y == X));         // (Y == X) is False
    EXPECT_EQ((bool)0, (bool)(Y == Z));         // (Y == Z) is False

    EXPECT_EQ((bool)0, (bool)(Z == D));         // (Z == D) is False
    EXPECT_EQ((bool)0, (bool)(Z == W));         // (Z == W) is False
    EXPECT_EQ((bool)0, (bool)(Z == X));         // (Z == X) is False
    EXPECT_EQ((bool)0, (bool)(Z == Y));;        // (Z == Y) is False

}

UT_CASE(ColVec, Access) {

    ColVec4i V = IV (1, 3, 5, 7);

    V[2] = 4;
    V[3] = V[0];

    EXPECT_EQ(V[0], 1);
    EXPECT_EQ(V[1], 3);
    EXPECT_EQ(V[2], 4);
    EXPECT_EQ(V[3], 1);

}

UT_CASE(ColVec, Add) {

    ColVec4i S;
    ColVec4i A = IV (10, 7, 4, 1);
    ColVec4i I = IV (1, 2, 3, 4);
    A += I;

    ColVec4i ApI = A + I;
    ColVec4i ApnI = A + (-I);

    // I unchanged
    EXPECT_EQ(I[0], 1); EXPECT_EQ(I[1], 2); EXPECT_EQ(I[2], 3); EXPECT_EQ(I[3], 4);

    // A incremented once
    EXPECT_EQ(A[0], 11); EXPECT_EQ(A[1], 9); EXPECT_EQ(A[2], 7); EXPECT_EQ(A[3], 5);

    // Second Sum
    EXPECT_EQ(ApI[0], 12); EXPECT_EQ(ApI[1], 11); EXPECT_EQ(ApI[2], 10); EXPECT_EQ(ApI[3], 9);

    // Add Negative
    EXPECT_EQ(ApnI[0], 10); EXPECT_EQ(ApnI[1], 7); EXPECT_EQ(ApnI[2], 4); EXPECT_EQ(ApnI[3], 1);

}

UT_CASE(ColVec, Sub) {


    ColVec4i D;
    ColVec4i A = IV (9, 8, 7, 6);
    ColVec4i I = IV (1, 2, 3, 4);
    A -= I;

    ColVec4i AmI = A - I;
    ColVec4i AmnI = A - (-I);

    // I unchanged
    EXPECT_EQ(I[0], 1); EXPECT_EQ(I[1], 2); EXPECT_EQ(I[2], 3); EXPECT_EQ(I[3], 4);

    // A decremented once
    EXPECT_EQ(A[0], 8); EXPECT_EQ(A[1], 6); EXPECT_EQ(A[2], 4); EXPECT_EQ(A[3], 2);

    // second difference
    EXPECT_EQ(AmI[0], 7); EXPECT_EQ(AmI[1], 4); EXPECT_EQ(AmI[2], 1); EXPECT_EQ(AmI[3], -2);

    // Sub Negative
    EXPECT_EQ(AmnI[0], 9); EXPECT_EQ(AmnI[1], 8); EXPECT_EQ(AmnI[2], 7); EXPECT_EQ(AmnI[3], 6);

}

UT_CASE(ColVec, Mul) {

    ColVec4i A = IV (9, 8, 7, 6);
    ColVec4i I = IV (1, 2, 3, 4);

    Mat4x4i AIt = A * ~I;          // a 4x4 matrix
    int AtI = ~A * I;          // an integer!

    EXPECT_EQ(AIt.rows(), 4);           // AIt number of rows
    EXPECT_EQ(AIt.cols(), 4);           // AIt number of columns
    EXPECT_EQ(AIt.size(), 16);          // AIt number of elements
    EXPECT_EQ(AtI, 70);                 // dot(A,I) value
}
