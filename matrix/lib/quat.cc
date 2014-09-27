#include "matrix_quat.hh"

#include <sstream>

using std::ostringstream;
using std::ostream;
using std::setw;
using std::string;

namespace Farsyte {
    namespace Matrix {

        Quat::Quat()
                : w(0), v() {
        }

        Quat::Quat(double iw, TriVec const &iv)
                : w(iw), v(iv) {
        }

        ostream &operator<<(ostream &s, Quat const &q) {
            int w = (int)
                    s.width();
            return
                    s << setw(1) << "<"
                            << setw(w) << q.scalar() << ","
                            << setw(w) << q.vector()
                            << ">";
        }

    }
}
