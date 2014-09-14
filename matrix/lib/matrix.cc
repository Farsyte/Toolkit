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

  }
}
