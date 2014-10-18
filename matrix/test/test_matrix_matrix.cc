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

/** Pick a type for a test matrix */
typedef Matrix<3, 2, int> Matrix23i;

/** Type for transposed test matrix */
typedef Matrix<2, 3, int> Matrix32i;

/* -- ================================================================ -- */

UT_CASE(Matrix, Meta) {

    EXPECT_EQ(Matrix23i::rows(), 2);            // Matrix Rows
    EXPECT_EQ(Matrix23i::cols(), 3);            // Matrix Cols
    EXPECT_EQ(Matrix23i::size(), 6);            // Matrix Size

};

UT_CASE(Matrix, CtorEqNe) {

    typedef Matrix23i::A IV;

    Matrix23i I;
    Matrix23i A = IV {1, 0, 0, 0, 0, 0};
    Matrix23i B = IV {0, 1, 0, 0, 0, 0};
    Matrix23i C = IV {0, 0, 1, 0, 0, 0};
    Matrix23i D = IV {0, 0, 0, 1, 0, 0};
    Matrix23i E = IV {0, 0, 0, 0, 1, 0};
    Matrix23i F = IV {0, 0, 0, 0, 0, 1};

    EXPECT_EQ((bool)0, (bool)(A != A));         // (A != A) is False
    EXPECT_EQ((bool)0, (bool)(A == B));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(A == C));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(A == D));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(A == E));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(A == F));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(A == I));         // (A == A) is False
    EXPECT_EQ((bool)0, (bool)(B != B));         // (B != B) is False
    EXPECT_EQ((bool)0, (bool)(B == A));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(B == C));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(B == D));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(B == E));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(B == F));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(B == I));         // (B == B) is False
    EXPECT_EQ((bool)0, (bool)(C != C));         // (C != C) is False
    EXPECT_EQ((bool)0, (bool)(C == A));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(C == B));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(C == D));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(C == E));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(C == F));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(C == I));         // (C == C) is False
    EXPECT_EQ((bool)0, (bool)(D != D));         // (D != D) is False
    EXPECT_EQ((bool)0, (bool)(D == A));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(D == B));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(D == C));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(D == E));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(D == F));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(D == I));         // (D == D) is False
    EXPECT_EQ((bool)0, (bool)(E != E));         // (E != E) is False
    EXPECT_EQ((bool)0, (bool)(E == A));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(E == B));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(E == C));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(E == D));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(E == F));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(E == I));         // (E == E) is False
    EXPECT_EQ((bool)0, (bool)(F != F));         // (F != F) is False
    EXPECT_EQ((bool)0, (bool)(F == A));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(F == B));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(F == C));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(F == D));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(F == E));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(F == I));         // (F == F) is False
    EXPECT_EQ((bool)0, (bool)(I != I));         // (I != I) is False
    EXPECT_EQ((bool)0, (bool)(I == A));         // (I == I) is False
    EXPECT_EQ((bool)0, (bool)(I == B));         // (I == I) is False
    EXPECT_EQ((bool)0, (bool)(I == C));         // (I == I) is False
    EXPECT_EQ((bool)0, (bool)(I == D));         // (I == I) is False
    EXPECT_EQ((bool)0, (bool)(I == E));         // (I == I) is False
    EXPECT_EQ((bool)0, (bool)(I == F));         // (I == I) is False

    EXPECT_NE((bool)0, (bool)(A != B));         // (A != B) is True
    EXPECT_NE((bool)0, (bool)(A != C));         // (A != C) is True
    EXPECT_NE((bool)0, (bool)(A != D));         // (A != D) is True
    EXPECT_NE((bool)0, (bool)(A != E));         // (A != E) is True
    EXPECT_NE((bool)0, (bool)(A != F));         // (A != F) is True
    EXPECT_NE((bool)0, (bool)(A != I));         // (A != I) is True
    EXPECT_NE((bool)0, (bool)(A == A));         // (A == A) is True
    EXPECT_NE((bool)0, (bool)(B != A));         // (B != A) is True
    EXPECT_NE((bool)0, (bool)(B != C));         // (B != C) is True
    EXPECT_NE((bool)0, (bool)(B != D));         // (B != D) is True
    EXPECT_NE((bool)0, (bool)(B != E));         // (B != E) is True
    EXPECT_NE((bool)0, (bool)(B != F));         // (B != F) is True
    EXPECT_NE((bool)0, (bool)(B != I));         // (B != I) is True
    EXPECT_NE((bool)0, (bool)(B == B));         // (B == B) is True
    EXPECT_NE((bool)0, (bool)(C != A));         // (C != A) is True
    EXPECT_NE((bool)0, (bool)(C != B));         // (C != B) is True
    EXPECT_NE((bool)0, (bool)(C != D));         // (C != D) is True
    EXPECT_NE((bool)0, (bool)(C != E));         // (C != E) is True
    EXPECT_NE((bool)0, (bool)(C != F));         // (C != F) is True
    EXPECT_NE((bool)0, (bool)(C != I));         // (C != I) is True
    EXPECT_NE((bool)0, (bool)(C == C));         // (C == C) is True
    EXPECT_NE((bool)0, (bool)(D != A));         // (D != A) is True
    EXPECT_NE((bool)0, (bool)(D != B));         // (D != B) is True
    EXPECT_NE((bool)0, (bool)(D != C));         // (D != C) is True
    EXPECT_NE((bool)0, (bool)(D != E));         // (D != E) is True
    EXPECT_NE((bool)0, (bool)(D != F));         // (D != F) is True
    EXPECT_NE((bool)0, (bool)(D != I));         // (D != I) is True
    EXPECT_NE((bool)0, (bool)(D == D));         // (D == D) is True
    EXPECT_NE((bool)0, (bool)(E != A));         // (E != A) is True
    EXPECT_NE((bool)0, (bool)(E != B));         // (E != B) is True
    EXPECT_NE((bool)0, (bool)(E != C));         // (E != C) is True
    EXPECT_NE((bool)0, (bool)(E != D));         // (E != D) is True
    EXPECT_NE((bool)0, (bool)(E != F));         // (E != F) is True
    EXPECT_NE((bool)0, (bool)(E != I));         // (E != I) is True
    EXPECT_NE((bool)0, (bool)(E == E));         // (E == E) is True
    EXPECT_NE((bool)0, (bool)(F != A));         // (F != A) is True
    EXPECT_NE((bool)0, (bool)(F != B));         // (F != B) is True
    EXPECT_NE((bool)0, (bool)(F != C));         // (F != C) is True
    EXPECT_NE((bool)0, (bool)(F != D));         // (F != D) is True
    EXPECT_NE((bool)0, (bool)(F != E));         // (F != E) is True
    EXPECT_NE((bool)0, (bool)(F != I));         // (F != I) is True
    EXPECT_NE((bool)0, (bool)(F == F));         // (F == F) is True
    EXPECT_NE((bool)0, (bool)(I != A));         // (I != A) is True
    EXPECT_NE((bool)0, (bool)(I != B));         // (I != B) is True
    EXPECT_NE((bool)0, (bool)(I != C));         // (I != C) is True
    EXPECT_NE((bool)0, (bool)(I != D));         // (I != D) is True
    EXPECT_NE((bool)0, (bool)(I != E));         // (I != E) is True
    EXPECT_NE((bool)0, (bool)(I != F));         // (I != F) is True
    EXPECT_NE((bool)0, (bool)(I == I));         // (I == I) is True

};

UT_CASE(Matrix, Access) {

    typedef Matrix23i::A IV;

    Matrix23i A = IV {1, 3, 5, 2, 4, 6};

    A(1, 1) = 8;
    A(1, 2) = A(0, 0);

    EXPECT_EQ(A[0], 1);
    EXPECT_EQ(A[1], 3);
    EXPECT_EQ(A[2], 5);
    EXPECT_EQ(A[3], 2);
    EXPECT_EQ(A[4], 8);
    EXPECT_EQ(A[5], 1);

};

UT_CASE(Matrix, Add) {

    typedef Matrix23i::A IV;

    Matrix23i S;
    Matrix23i A = IV {16, 13, 10, 7, 4, 1};
    Matrix23i I = IV {1, 2, 3, 4, 5, 6};
    A += I;

    auto ApI = A + I;
    auto ApnI = A + (-I);

// I unchanged
    EXPECT_EQ(I[0], 1);
    EXPECT_EQ(I[1], 2);
    EXPECT_EQ(I[2], 3);
    EXPECT_EQ(I[3], 4);
    EXPECT_EQ(I[4], 5);
    EXPECT_EQ(I[5], 6);

// A incremented once
    EXPECT_EQ(A[0], 17);
    EXPECT_EQ(A[1], 15);
    EXPECT_EQ(A[2], 13);
    EXPECT_EQ(A[3], 11);
    EXPECT_EQ(A[4], 9);
    EXPECT_EQ(A[5], 7);

// Second Sum
    EXPECT_EQ(ApI[0], 18);
    EXPECT_EQ(ApI[1], 17);
    EXPECT_EQ(ApI[2], 16);
    EXPECT_EQ(ApI[3], 15);
    EXPECT_EQ(ApI[4], 14);
    EXPECT_EQ(ApI[5], 13);

// Add Negative
    EXPECT_EQ(ApnI[0], 16);
    EXPECT_EQ(ApnI[1], 13);
    EXPECT_EQ(ApnI[2], 10);
    EXPECT_EQ(ApnI[3], 7);
    EXPECT_EQ(ApnI[4], 4);
    EXPECT_EQ(ApnI[5], 1);

};

UT_CASE(Matrix, Sub) {

    typedef Matrix23i::A IV;

    Matrix23i D;
    Matrix23i A = IV {18, 17, 16, 15, 14, 13};
    Matrix23i I = IV {1, 2, 3, 4, 5, 6};
    A -= I;

    auto AmI = A - I;
    auto AmnI = A - (-I);

// I unchanged
    EXPECT_EQ(I[0], 1);
    EXPECT_EQ(I[1], 2);
    EXPECT_EQ(I[2], 3);
    EXPECT_EQ(I[3], 4);
    EXPECT_EQ(I[4], 5);
    EXPECT_EQ(I[5], 6);

// A decremented once
    EXPECT_EQ(A[0], 17);
    EXPECT_EQ(A[1], 15);
    EXPECT_EQ(A[2], 13);
    EXPECT_EQ(A[3], 11);
    EXPECT_EQ(A[4], 9);
    EXPECT_EQ(A[5], 7);

// second difference
    EXPECT_EQ(AmI[0], 16);
    EXPECT_EQ(AmI[1], 13);
    EXPECT_EQ(AmI[2], 10);
    EXPECT_EQ(AmI[3], 7);
    EXPECT_EQ(AmI[4], 4);
    EXPECT_EQ(AmI[5], 1);

// Sub Negative
    EXPECT_EQ(AmnI[0], 18);
    EXPECT_EQ(AmnI[1], 17);
    EXPECT_EQ(AmnI[2], 16);
    EXPECT_EQ(AmnI[3], 15);
    EXPECT_EQ(AmnI[4], 14);
    EXPECT_EQ(AmnI[5], 13);

};

UT_CASE(Matrix, Mul) {

    typedef Matrix23i::A IV;

    Matrix23i A = IV {13, 69, 32, 82, 21, 20};
    Matrix23i B = IV {91, 26, 69, 25, 22, 41};

    auto ABt = A * ~B;
    auto AtB = ~A * B;

    EXPECT_EQ(ABt[0], 5185);
    EXPECT_EQ(ABt[1], 3155);
    EXPECT_EQ(ABt[2], 9388);
    EXPECT_EQ(ABt[3], 3332);

    EXPECT_EQ(AtB[0], 3233);
    EXPECT_EQ(AtB[1], 2142);
    EXPECT_EQ(AtB[2], 4259);
    EXPECT_EQ(AtB[3], 6804);
    EXPECT_EQ(AtB[4], 2256);
    EXPECT_EQ(AtB[5], 5622);
    EXPECT_EQ(AtB[6], 3412);
    EXPECT_EQ(AtB[7], 1272);
    EXPECT_EQ(AtB[8], 3028);
};

UT_CASE(Matrix, Scale) {

    typedef Matrix23i::A IV;

    Matrix23i A = IV {     3      ,      5      ,      7      ,      11      ,      13      ,      17     };
    Matrix23i B = IV {     3*23*3 ,      5*23*3 ,      7*23*3 ,      11*23*3 ,      13*23*3 ,      17*23*3};
    Matrix23i C = IV {2*27*3*23*3 , 2*27*5*23*3 , 2*27*7*23*3 , 2*27*11*23*3 , 2*27*13*23*3 , 2*27*17*23*3};
    Matrix23i D = IV {  27*3*23   ,   27*5*23   ,   27*7*23   ,   27*11*23   ,   27*13*23   ,   27*17*23  };

    EXPECT_EQ(A * (23 * 3), B);         // A * (23*3)
    EXPECT_EQ((2 * 27) * B, C);         // (2*27) * B
    EXPECT_EQ(C / 6, D);                // C / 6
};
