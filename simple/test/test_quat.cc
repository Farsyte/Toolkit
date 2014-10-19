#include "simple_quat.hh"
#include "testing.hh"

using Farsyte::Simple::Quat;
using Farsyte::Simple::T;
using Farsyte::Simple::V;

using std::cerr;
using std::setw;

UT_CASE(Quat, Compare) {

    // Default constructor makes an all-zero quaternion.
    Quat const Zero;

    // Initialization from a scalar builds a quaternion
    // with a zero imaginary part.
    Quat const Unit{1};

    // Initialization from a vector builds a quaternion
    // that is "pure" -- the imaginary parts are taken
    // from the vector, and the real part is zero.
    Quat const DirX{{1, 0, 0}};
    Quat const DirY{{0, 1, 0}};
    Quat const DirZ{{0, 0, 1}};

    EXPECT_EQ(Zero, Zero);
    EXPECT_EQ(Unit, Unit);
    EXPECT_EQ(DirX, DirX);
    EXPECT_EQ(DirY, DirY);
    EXPECT_EQ(DirZ, DirZ);

    EXPECT_NE(Zero, Unit);
    EXPECT_NE(Zero, DirX);
    EXPECT_NE(Zero, DirY);
    EXPECT_NE(Zero, DirZ);

    EXPECT_NE(Unit, Zero);
    EXPECT_NE(Unit, DirX);
    EXPECT_NE(Unit, DirY);
    EXPECT_NE(Unit, DirZ);

    EXPECT_NE(DirX, Zero);
    EXPECT_NE(DirX, Unit);
    EXPECT_NE(DirX, DirY);
    EXPECT_NE(DirX, DirZ);

    EXPECT_NE(DirY, Zero);
    EXPECT_NE(DirY, Unit);
    EXPECT_NE(DirY, DirX);
    EXPECT_NE(DirY, DirZ);

    EXPECT_NE(DirZ, Zero);
    EXPECT_NE(DirZ, Unit);
    EXPECT_NE(DirZ, DirX);
    EXPECT_NE(DirZ, DirY);
};

UT_CASE(Quat, Access) {

    Quat const Zero;
    Quat       Uniq{2, {4, 5, 6}};

    EXPECT_EQ(Zero.w, T());
    EXPECT_EQ(Zero.v, V());
    EXPECT_EQ(Uniq.w, 2);
    EXPECT_EQ(Uniq.v, (V{4, 5, 6}));

    Uniq.w = 6;
    Uniq.v = {5, 4, 2};

    EXPECT_EQ(Uniq.w, 6);
    EXPECT_EQ(Uniq.v, (V{5, 4, 2}));
};

UT_CASE(Quat, Add) {
    Quat A{10, {7, 4, 1}};
    Quat const I{1, {2, 3, 4}};

    EXPECT_EQ(I, (Quat{1, {2, 3, 4}}));
    EXPECT_EQ(A += I, (Quat{11, {9, 7, 5}}));
    EXPECT_EQ(A, (Quat{11, {9, 7, 5}}));
    EXPECT_EQ(A + I, (Quat{12, {11, 10, 9}}));
    EXPECT_EQ(A + (-I), (Quat{10, {7, 4, 1}}));
};

UT_CASE(Quat, Sub) {
    Quat A{12, {11, 10, 9}};
    Quat const I{1, {2, 3, 4}};

    EXPECT_EQ(I, (Quat{1, {2, 3, 4}}));
    EXPECT_EQ(A -= I, (Quat{11, {9, 7, 5}}));
    EXPECT_EQ(A, (Quat{11, {9, 7, 5}}));
    EXPECT_EQ(A - I, (Quat{10, {7, 4, 1}}));
    EXPECT_EQ(A - (-I), (Quat{12, {11, 10, 9}}));
};

UT_CASE(Quat, Scale) {
    Quat const C = { 14, { 22, 26, 34 }};
    Quat       A = {  9, { 12, 15, 18 }};

    EXPECT_EQ(A *= 2, (Quat{18, {24, 30, 36}}));
    EXPECT_EQ(C * 2, (Quat{28, {44, 52, 68}}));
    EXPECT_EQ(2 * C, (Quat{28, {44, 52, 68}}));
    EXPECT_EQ(C / 2, (Quat{7, {11, 13, 17}}));
    EXPECT_EQ(A /= 3, (Quat{6, {8, 10, 12}}));

};


// An integer quaternion with integer norm:
//     | {  2, {  4, 5, 6 }} | =   9
//
// An integer quaternion with norm 100:
//     | { 34, { 38, 50, 70 }} | = 100


UT_CASE(Quat, Norm) {
    Quat       A { 2, { 4, 5, 6 }};
    Quat const C { 34, { 38, 50, 70 }};

    EXPECT_EQ(normsq(A), 81);
    EXPECT_EQ(norm(C), 100);

};

UT_CASE(Quat, ConjNeg) {
    Quat        Q { 2, { 4, 5, 6 }};
    EXPECT_EQ(-Q, (Quat{-2, {-4, -5, -6}}));
    EXPECT_EQ(~Q, (Quat{ 2, {-4, -5, -6}}));
};

UT_CASE(Quat, Mul) {

    Quat const Zero;
    Quat const Unit{1};
    Quat const DirX{{3, 0, 0}};
    Quat const DirY{{0, 5, 0}};
    Quat const DirZ{{0, 0, 7}};

    Quat       A { 2, { 4, 5, 6 }};
    Quat const C { 34, { 38, 50, 70 }};

    // Zero times anything is zero.
    // Anything times zero is zero.

    EXPECT_EQ(Zero * Zero, Zero);

    EXPECT_EQ(Zero * Unit, Zero);
    EXPECT_EQ(Zero * DirX, Zero);
    EXPECT_EQ(Zero * DirY, Zero);
    EXPECT_EQ(Zero * DirZ, Zero);

    // Unit times anything is itself.
    // Anything times unit is itself.

    EXPECT_EQ(Unit * Zero, Zero);
    EXPECT_EQ(DirX * Zero, Zero);
    EXPECT_EQ(DirY * Zero, Zero);
    EXPECT_EQ(DirZ * Zero, Zero);

    EXPECT_EQ(Unit * Unit, Unit);

    EXPECT_EQ(Unit * DirX, DirX);
    EXPECT_EQ(Unit * DirY, DirY);
    EXPECT_EQ(Unit * DirZ, DirZ);

    EXPECT_EQ(DirX * Unit, DirX);
    EXPECT_EQ(DirY * Unit, DirY);
    EXPECT_EQ(DirZ * Unit, DirZ);

    // For quaternions aligned along the imaginary
    // axes, the square of the quaternion is a
    // negative real value.

    EXPECT_EQ(DirX * DirX, (Quat{-9}));
    EXPECT_EQ(DirY * DirY, (Quat{-25}));
    EXPECT_EQ(DirZ * DirZ, (Quat{-49}));

    // Quaternion multiplication is not commutative.

    EXPECT_EQ(DirX * DirY, (Quat{{0, 0, 15}}));
    EXPECT_EQ(DirY * DirX, (Quat{{0, 0, -15}}));

    EXPECT_EQ(DirX * DirZ, (Quat{{0, -21, 0}}));
    EXPECT_EQ(DirZ * DirX, (Quat{{0, 21, 0}}));

    EXPECT_EQ(DirY * DirZ, (Quat{{35, 0, 0}}));
    EXPECT_EQ(DirZ * DirY, (Quat{{-35, 0, 0}}));

    // Multiplication of a quaternion by its conjugate
    // gives the square of the two-norm.

    EXPECT_EQ(A*~A, (Quat{normsq(A)}));
    EXPECT_EQ(~A*A, (Quat{normsq(A)}));
    EXPECT_EQ(C*~C, (Quat{normsq(C)}));
    EXPECT_EQ(~C*C, (Quat{normsq(C)}));

};
