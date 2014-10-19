#include "simple_quat.hh"
#include "testing.hh"

using Farsyte::Simple::Quat;
using Farsyte::Simple::T;
using Farsyte::Simple::V;

using std::cerr;
using std::setw;

UT_CASE(Quat, Compare) {

    Quat const Zero;
    Quat const Unit{1, {0,0,0}};
    Quat const DirX{0, {1, 0, 0}};
    Quat const DirY{0, {0, 1, 0}};
    Quat const DirZ{0, {0, 0, 1}};

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
    Quat       Uniq{2,{4,5,6}};

    EXPECT_EQ(Zero.scalar(), T());
    EXPECT_EQ(Zero.vector(), V());
    EXPECT_EQ(Uniq.scalar(), 2);
    EXPECT_EQ(Uniq.vector(), (V{4,5,6}));

    Uniq.scalar() = 6;
    Uniq.vector() = {5,4,2};

    EXPECT_EQ(Uniq.scalar(), 6);
    EXPECT_EQ(Uniq.vector(), (V{5,4,2}));
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
//     | {  2, {  4,  5,  6 }} | =   9
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
    Quat	Q { 2, { 4, 5, 6 }};
    EXPECT_EQ(-Q, (Quat{-2,{-4,-5,-6}}));
    EXPECT_EQ(~Q, (Quat{ 2,{-4,-5,-6}}));
};
