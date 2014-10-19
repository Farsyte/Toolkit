#include "simple_quat.hh"

#include <stdexcept>
#include <cmath>
#include <iomanip>

using std::setw;
using std::out_of_range;

namespace Farsyte {
    namespace Simple {

        Quat::Quat()
            : w(), v()
        {
        }

        Quat::Quat(T const & wi)
            : w(wi), v()
        {
        }

        Quat::Quat(V const & vi)
            : w(), v(vi)
        {
        }

        Quat::Quat(T const & wi, V const & vi)
            : w(wi), v(vi)
        {
        }

        bool operator==(Quat const &a, Quat const &b) {
            return (a.w == b.w) && (a.v == b.v);
        }

        bool operator!=(Quat const &a, Quat const &b) {
            return (a.w != b.w) || (a.v != b.v);
        }

        Quat &Quat::operator+=(Quat const &that) {
            w += that.w;
            v += that.v;
            return *this;
        }

        Quat &Quat::operator-=(Quat const &that) {
            w -= that.w;
            v -= that.v;
            return *this;
        }

        Quat &Quat::operator*=(Quat const &that) {
            *this = *this * that;
            return *this;
        }

        Quat &Quat::operator/=(Quat const &that) {
            *this = *this / that;
            return *this;
        }

        Quat &Quat::operator*=(T by) {
            w *= by;
            v *= by;
            return *this;
        }

        Quat &Quat::operator/=(T by) {
            w /= by;
            v /= by;
            return *this;
        }

        Quat operator/(T const &a, Quat const &b) {
            return a * (~b / normsq(b));
        }

        Quat operator/(Quat const &a, Quat const &b) {
            return a * (~b / normsq(b));
        }

        Quat operator-(Quat const &a) {
            Quat z;
            z -= a;
            return z;
        }

        Quat operator~(Quat const &a) {
            Quat z(a.w, -a.v);
            return z;
        }

        Quat operator+(Quat a, Quat const &b) {
            a += b;
            return a;
        }

        Quat operator-(Quat a, Quat const &b) {
            a -= b;
            return a;
        }

        Quat operator*(Quat const &a, Quat const &b) {
            return Quat(a.w * b.w - dot(a.v, b.v),
                        a.w * b.v + a.v * b.w + cross(a.v, b.v));
        }

        Quat operator*(Quat a, T const &b) {
            a *= b;
            return a;
        }

        Quat operator*(T const &b, Quat a) {
            a *= b;
            return a;
        }

        Quat operator/(Quat a, T const &b) {
            a /= b;
            return a;
        }

        T normsq(Quat const &a) {
            return a.w*a.w + normsq(a.v);
        }


        T norm(Quat const &a) {
            return sqrt(normsq(a));
        }

        std::ostream &operator<<(std::ostream &s, Quat const &r) {
            int w = (int) s.width();
            s << setw(1) << "{"
              << setw(w) << r.w << ","
              << setw(w) << r.v << "}";
            return s;
        }

    }
}
