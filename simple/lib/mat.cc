#include "simple_mat.hh"
#include <iomanip>

using std::setw;

namespace Farsyte {
    namespace Simple {


        Mat::Mat() {
        }

        Mat::Mat(T const &v) {
            a[0][0] = v;
            a[1][1] = v;
            a[2][2] = v;
        }

        Mat::Mat(Row const &d) {
            a[0][0] = d[0];
            a[1][1] = d[1];
            a[2][2] = d[2];
        }

        Mat::Mat(T const &x, T const &y, T const &z) {
            a[0][0] = x;
            a[1][1] = y;
            a[2][2] = z;
        }

        Mat::Mat(Row const &r0, Row const &r1, Row const &r2) {
            a[0] = r0;
            a[1] = r1;
            a[2] = r2;
        }

        Mat::Mat(Col const &d) {
            a[0][0] = d[0];
            a[1][1] = d[1];
            a[2][2] = d[2];
        }

        Row const &Mat::operator[](int r) const {
            return a[r];
        }

        Row &Mat::operator[](int r) {
            return a[r];
        }

        T const &Mat::operator()(int r, int c) const {
            return a[r][c];
        }

        T &Mat::operator()(int r, int c) {
            return a[r][c];
        }

        bool Mat::operator==(Mat const &that) const {
            return (a[0] == that[0] && a[1] == that[1] && a[2] == that[2]);
        }

        bool Mat::operator!=(Mat const &that) const {
            return (a[0] != that[0] || a[1] != that[1] || a[2] != that[2]);
        }

        Mat &Mat::operator+=(Mat const &that) {
            for (int i = 0; i < Nr; ++i)
                a[i] += that[i];
            return *this;
        }

        Mat &Mat::operator-=(Mat const &that) {
            for (int i = 0; i < Nr; ++i)
                a[i] -= that[i];
            return *this;
        }

        Mat &Mat::operator*=(T by) {
            for (int i = 0; i < Nr; ++i)
                a[i] *= by;
            return *this;
        }

        Mat &Mat::operator/=(T by) {
            for (int i = 0; i < Nr; ++i)
                a[i] /= by;
            return *this;
        }

        Mat operator+(Mat a, Mat const &b) {
            a += b;
            return a;
        }

        Mat operator-(Mat a, Mat const &b) {
            a -= b;
            return a;
        }

        Mat operator-(Mat const &b) {
            Mat a;
            a -= b;
            return a;
        }

        Mat operator*(T b, Mat a) {
            a *= b;
            return a;
        }

        Mat operator*(Mat a, T b) {
            a *= b;
            return a;
        }

        Mat operator/(Mat a, T b) {
            a /= b;
            return a;
        }

        Mat operator*(
            Mat const &a,
            Mat const &b) {
            Mat m;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j) {
                    T s = a(i, 0) * b(0, j);
                    for (int k = 1; k < 3; ++k) {
                        s += a(i, k) * b(k, j);
                    }
                    m(i, j) = s;
                }
            return m;
        }

        V operator*(M const &m, V const &v) {
            return V(m(0,0)*v[0] + m(0,1)*v[1] + m(0,2)*v[2],
                     m(1,0)*v[0] + m(1,1)*v[1] + m(1,2)*v[2],
                     m(2,0)*v[0] + m(2,1)*v[1] + m(2,2)*v[2]);
        }


        std::ostream &operator<<(
            std::ostream &str,
            Mat const &m) {
            int w = (int) str.width();
            str << setw(1) << "{"
                << setw(w) << m[0] << ","
                << setw(w) << m[1] << ","
                << setw(w) << m[2] << "}";
            return str;
        }

    }
}
