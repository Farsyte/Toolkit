#include "simple_col.hh"

#include <stdexcept>
#include <cmath>
#include <iomanip>

using std::setw;
using std::out_of_range;

namespace Farsyte {
    namespace Simple {

        Col::Col() {
            for (int i = 0; i < Nr; ++i)
                a[i] = T();
        }

        Col::Col(T c0, T c1, T c2) {
            a[0] = c0;
            a[1] = c1;
            a[2] = c2;
        }

        T const & Col::operator[](int i) const {
            if ((i < 0) || (i >= Nr))
                throw out_of_range("Col Index");
            return a[i];
        }

        T &Col::operator[](int i) {
            if ((i < 0) || (i >= Nr))
                throw out_of_range("Col Index");
            return a[i];
        }

        bool Col::operator==(Col const &that) const {
            for (int i = 0; i < Nr; ++i)
                if (a[i] != that.a[i])
                    return false;
            return true;
        }

        bool Col::operator!=(Col const &that) const {
            for (int i = 0; i < Nr; ++i)
                if (a[i] != that.a[i])
                    return true;
            return false;
        }

        Col &Col::operator+=(Col const &that) {
            for (int i = 0; i < Nr; ++i)
                a[i] += that.a[i];
            return *this;
        }

        Col &Col::operator-=(Col const &that) {
            for (int i = 0; i < Nr; ++i)
                a[i] -= that.a[i];
            return *this;
        }

        Col &Col::operator*=(T by) {
            for (int i = 0; i < Nr; ++i)
                a[i] *= by;
            return *this;
        }

        Col &Col::operator/=(T by) {
            for (int i = 0; i < Nr; ++i)
                a[i] /= by;
            return *this;
        }

        Col operator-(Col const &a) {
            Col z;
            z -= a;
            return z;
        }

        Col operator+(Col a, Col const &b) {
            a += b;
            return a;
        }

        Col operator-(Col a, Col const &b) {
            a -= b;
            return a;
        }

        Col operator*(Col a, T const &b) {
            a *= b;
            return a;
        }

        Col operator*(T const &b, Col a) {
            a *= b;
            return a;
        }

        Col operator/(Col a, T const &b) {
            a /= b;
            return a;
        }

        Col cross(
            Col const &a,
            Col const &b) {
            return Col(
                a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0]);
        }

        T dot(Col const &a, Col const &b) {
            return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        }

        T normsq(Col const &a) {
            return a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
        }


        T norm(Col const &a) {
            return sqrt(normsq(a));
        }

        std::ostream &operator<<(std::ostream &s, Col const &r) {
            int w = (int) s.width();
            s << setw(1) << "{"
              << setw(w) << r[0] << ","
              << setw(w) << r[1] << ","
              << setw(w) << r[2] << "}";
            return s;
        }

    }
}
