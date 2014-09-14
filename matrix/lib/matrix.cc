#include "matrix.h"

namespace Farsyte {
  namespace Matrix {

    ThreeVec::ThreeVec()
      : ColMe()
    {
    }

    ThreeVec::ThreeVec(double x, double y, double z)
      : ColMe(C{{x,y,z}})
    {
    }

    ThreeVec::ThreeVec(MatMe const &p)
      : ColMe(p)
    {
    }

    /** Cross-Product operation.
     * \param L  First operand for product.
     * \param R  Second operand for product.
     * \returns Matrix whose elements are the sum of corresponding input elements.
     */
    ThreeVec cross(
      ThreeVec const &L,
      ThreeVec const &R)
    {
      return ThreeVec(
        L(2)*R(3) - L(3)*R(2),
        L(3)*R(1) - L(1)*R(3),
        L(1)*R(2) - L(2)*R(1));
    }

  }
}
