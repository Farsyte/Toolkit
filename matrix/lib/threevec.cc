#include "matrix_threevec.hh"

#include <sstream>

using std::ostringstream;
using std::string;

namespace Farsyte {
    namespace Matrix {


        ThreeVec::ThreeVec()
                : ColMe() {
        }

        ThreeVec::ThreeVec(double x, double y, double z)
                : ColMe(A{{x, y, z}}) {
        }

        ThreeVec::ThreeVec(MatMe const &p)
                : ColMe(p) {
        }

        /** Cross-Product operation.
        * \param L  First operand for product.
        * \param R  Second operand for product.
        * \returns Matrix whose elements are the sum of corresponding input elements.
        */
        ThreeVec cross(
                Matrix<1, 3, double> const &L,
                Matrix<1, 3, double> const &R) {
            return ThreeVec(
                    L[1] * R[2] - L[2] * R[1],
                    L[2] * R[0] - L[0] * R[2],
                    L[0] * R[1] - L[1] * R[0]);
        }

    }
}
