#include "matrix.h"

#include <sstream>
#include <stdexcept>

using std::ostringstream;
using std::string;

namespace Farsyte {
  namespace Matrix {

    string matrix_range_error(
      int Nr, int Nc, int ri, int ci)
    {
      ostringstream msg;
      msg << "matrix subscript range error\n";
      if ((ri < 0) || (ri >= Nr))
        msg << "    ri (" << ri << ")"
            << " is not in the range 0.." << (Nr-1)
            << " inclusive.\n";
      if ((ci < 0) || (ci >= Nc))
        msg << "    ci (" << ci << ")"
            << " is not in the range 0.." << (Nc-1)
            << " inclusive.\n";
      return msg.str();
    }

    ThreeVec::ThreeVec()
      : ColMe()
    {
    }

    ThreeVec::ThreeVec(double x, double y, double z)
      : ColMe(A{{x,y,z}})
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
      Matrix<1,3,double> const &L,
      Matrix<1,3,double> const &R)
    {
      return ThreeVec(
        L[1]*R[2] - L[2]*R[1],
        L[2]*R[0] - L[0]*R[2],
        L[0]*R[1] - L[1]*R[0]);
    }

  }
}
