#include "matrix_quat.hh"

#include <sstream>

using std::ostringstream;
using std::ostream;
using std::setw;
using std::string;

namespace Farsyte {
    namespace Matrix {

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
