#include "simple_col.hh"
#include "testing.hh"

using Farsyte::Simple::Col;
using Farsyte::Simple::T;

using std::cerr;
using std::setw;

UT_CASE(Col, Compare) {

    Col const Zero;
    Col const DirX{1, 0, 0};
    Col const DirY{0, 1, 0};
    Col const DirZ{0, 0, 1};

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

UT_CASE(Col, Access) {

    Col const Zero;
    Col V975{9, 7, 5};

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

UT_CASE(Col, Add) {
    Col A{7, 4, 1};
    Col const I{1, 2, 3};

    EXPECT_EQ(I, Col(1, 2, 3));
    EXPECT_EQ(A += I, Col(8, 6, 4));
    EXPECT_EQ(A, Col(8, 6, 4));
    EXPECT_EQ(A + I, Col(9, 8, 7));
    EXPECT_EQ(A + (-I), Col(7, 4, 1));
};

UT_CASE(Col, Sub) {

    Col A{9, 8, 7};
    Col I{1, 2, 3};

    EXPECT_EQ(I, Col(1, 2, 3));
    EXPECT_EQ(A -= I, Col(8, 6, 4));
    EXPECT_EQ(A, Col(8, 6, 4));
    EXPECT_EQ(A - I, Col(7, 4, 1));
    EXPECT_EQ(A - (-I), Col(9, 8, 7));
};

UT_CASE(Col, Scale) {
    Col A{12, 15, 18};
    Col const C{22, 26, 34};

    EXPECT_EQ(A *= 2, Col(24, 30, 36));
    EXPECT_EQ(C * 2, Col(44, 52, 68));
    EXPECT_EQ(2 * C, Col(44, 52, 68));
    EXPECT_EQ(C / 2, Col(11, 13, 17));
    EXPECT_EQ(A /= 3, Col(8, 10, 12));

};


UT_CASE(Col, Dot) {

    Col V{3, 4, 7};

    Col X{3, 0, 0};
    Col Y{0, 2, 0};
    Col Z{0, 0, 1};

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

UT_CASE(Col, Cross) {

    Col X{1, 0, 0};
    Col Y{0, 2, 0};
    Col Z{0, 0, 3};

    EXPECT_EQ(cross(X, X), Col(0, 0, 0));
    EXPECT_EQ(cross(Y, Y), Col(0, 0, 0));
    EXPECT_EQ(cross(Z, Z), Col(0, 0, 0));

    EXPECT_EQ(cross(X, Y), Col(0, 0, 2));
    EXPECT_EQ(cross(Y, Z), Col(6, 0, 0));
    EXPECT_EQ(cross(Z, X), Col(0, 3, 0));

    EXPECT_EQ(cross(X, Z), Col(0, -3, 0));
    EXPECT_EQ(cross(Y, X), Col(0, 0, -2));
    EXPECT_EQ(cross(Z, Y), Col(-6, 0, 0));

};

UT_CASE(Col, Norm) {
    // 2^2 + 3^2 + 6^2 = 7^2

    Col const N{2, 3, 6};
    EXPECT_EQ(normsq(N), 49);
    EXPECT_EQ(norm(N), 7);

};
