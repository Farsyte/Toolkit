#include "matrix_trivec.hh"

#include <sstream>

using std::ostringstream;
using std::ostream;
using std::setw;
using std::string;

namespace Farsyte {
    namespace Matrix {


        TriVec::TriVec()
                : ColMe() {
        }

        TriVec::TriVec(double x, double y, double z)
                : ColMe() {
            (*this)[0] = x;
            (*this)[1] = y;
            (*this)[2] = z;
        }

        TriVec::TriVec(MatMe const &p)
                : ColMe(p) {
        }

        /** Cross-Product operation.
        * \param L  First operand for product.
        * \param R  Second operand for product.
        * \returns Matrix whose elements are the sum of corresponding input elements.
        */
        TriVec cross(
                Matrix<1, 3, double> const &L,
                Matrix<1, 3, double> const &R) {
            return TriVec(
                    L[1] * R[2] - L[2] * R[1],
                    L[2] * R[0] - L[0] * R[2],
                    L[0] * R[1] - L[1] * R[0]);
        }

        ostream &operator<<(ostream &s, TriVec const &v) {
            int w = (int)
                    s.width();
            return
                    s << setw(1) << "["   // not to the leading bracket!
                            << setw(w) << v[0] << ","
                            << setw(w) << v[1] << ","
                            << setw(w) << v[2] << "]";
        }

    }
}
