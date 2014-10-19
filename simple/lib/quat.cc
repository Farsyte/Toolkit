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

        Quat::Quat(T const & wi, V const & vi)
            : w(wi), v(vi)
        {
        }

        bool Quat::operator==(Quat const &that) const {
            return (w == that.w) && (v == that.v);
        }

        bool Quat::operator!=(Quat const &that) const {
            return (w != that.w) || (v != that.v);
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

        Quat operator-(Quat const &a) {
            Quat z;
            z -= a;
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
              << setw(w) << r.scalar() << ","
              << setw(w) << r.vector() << "}";
            return s;
        }

    }
}
