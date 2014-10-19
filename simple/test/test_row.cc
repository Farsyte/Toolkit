#include "simple_row.hh"
#include "testing.hh"

using Farsyte::Simple::Row;
using Farsyte::Simple::T;

using std::cerr;
using std::setw;

UT_CASE(Row, Compare) {

    Row const Zero;
    Row const DirX{1, 0, 0};
    Row const DirY{0, 1, 0};
    Row const DirZ{0, 0, 1};

    EXPECT_EQ(Zero, Zero);
    EXPECT_EQ(DirX, DirX);
    EXPECT_EQ(DirY, DirY);
    EXPECT_EQ(DirZ, DirZ);

    EXPECT_NE(Zero, DirX);
    EXPECT_NE(Zero, DirY);
    EXPECT_NE(Zero, DirZ);

    EXPECT_NE(DirX, Zero);
    EXPECT_NE(DirX, DirY);
    EXPECT_NE(DirX, DirZ);

    EXPECT_NE(DirY, Zero);
    EXPECT_NE(DirY, DirX);
    EXPECT_NE(DirY, DirZ);

    EXPECT_NE(DirZ, Zero);
    EXPECT_NE(DirZ, DirX);
    EXPECT_NE(DirZ, DirY);
};

UT_CASE(Row, Access) {

    Row const Zero;
    Row V975{9, 7, 5};

    EXPECT_EQ(0, Zero[0]);
    EXPECT_EQ(0, Zero[1]);
    EXPECT_EQ(0, Zero[2]);

    EXPECT_EQ(9, V975[0]);
    EXPECT_EQ(7, V975[1]);
    EXPECT_EQ(5, V975[2]);

    V975[2] = V975[0];
    V975[1] = 3;

    EXPECT_EQ(9, V975[0]);
    EXPECT_EQ(3, V975[1]);
    EXPECT_EQ(9, V975[2]);
};

UT_CASE(Row, Add) {
    Row A{7, 4, 1};
    Row const I{1, 2, 3};

    EXPECT_EQ(I, Row(1, 2, 3));
    EXPECT_EQ(A += I, Row(8, 6, 4));
    EXPECT_EQ(A, Row(8, 6, 4));
    EXPECT_EQ(A + I, Row(9, 8, 7));
    EXPECT_EQ(A + (-I), Row(7, 4, 1));
};

UT_CASE(Row, Sub) {

    Row A{9, 8, 7};
    Row I{1, 2, 3};

    EXPECT_EQ(I, Row(1, 2, 3));
    EXPECT_EQ(A -= I, Row(8, 6, 4));
    EXPECT_EQ(A, Row(8, 6, 4));
    EXPECT_EQ(A - I, Row(7, 4, 1));
    EXPECT_EQ(A - (-I), Row(9, 8, 7));
};

UT_CASE(Row, Scale) {
    Row A{12, 15, 18};
    Row const C{22, 26, 34};

    EXPECT_EQ(A *= 2, Row(24, 30, 36));
    EXPECT_EQ(C * 2, Row(44, 52, 68));
    EXPECT_EQ(2 * C, Row(44, 52, 68));
    EXPECT_EQ(C / 2, Row(11, 13, 17));
    EXPECT_EQ(A /= 3, Row(8, 10, 12));

};


UT_CASE(Row, Dot) {

    Row V{3, 4, 7};

    Row X{3, 0, 0};
    Row Y{0, 2, 0};
    Row Z{0, 0, 1};

    EXPECT_EQ(dot(X, X), 9);
    EXPECT_EQ(dot(Y, Y), 4);
    EXPECT_EQ(dot(Z, Z), 1);

    EXPECT_EQ(dot(X, Y), T());
    EXPECT_EQ(dot(Y, Z), T());
    EXPECT_EQ(dot(Z, X), T());

    EXPECT_EQ(dot(X, Z), T());
    EXPECT_EQ(dot(Y, X), T());
    EXPECT_EQ(dot(Z, Y), T());

    EXPECT_EQ(dot(X, V), 9);
    EXPECT_EQ(dot(Y, V), 8);
    EXPECT_EQ(dot(Z, V), 7);

};

UT_CASE(Row, Cross) {

    Row X{1, 0, 0};
    Row Y{0, 2, 0};
    Row Z{0, 0, 3};

    EXPECT_EQ(cross(X, X), Row(0, 0, 0));
    EXPECT_EQ(cross(Y, Y), Row(0, 0, 0));
    EXPECT_EQ(cross(Z, Z), Row(0, 0, 0));

    EXPECT_EQ(cross(X, Y), Row(0, 0, 2));
    EXPECT_EQ(cross(Y, Z), Row(6, 0, 0));
    EXPECT_EQ(cross(Z, X), Row(0, 3, 0));

    EXPECT_EQ(cross(X, Z), Row(0, -3, 0));
    EXPECT_EQ(cross(Y, X), Row(0, 0, -2));
    EXPECT_EQ(cross(Z, Y), Row(-6, 0, 0));

};

UT_CASE(Row, Norm) {
    // 2^2 + 3^2 + 6^2 = 7^2

    Row const N{2, 3, 6};
    EXPECT_EQ(normsq(N), 49);
    EXPECT_EQ(norm(N), 7);

};
