#include "matrix_quat.hh"

#include <sstream>
#include <iomanip>

using std::ostringstream;
using std::ostream;
using std::setw;
using std::string;

namespace Farsyte {
    namespace Matrix {

        Quat::Quat() {
        }

        ostream &operator<<(ostream &s, Quat const &v) {
            auto w = s.width();     // apply width to each element,
            return
                    s << setw(1) << "<"   // not to the leading bracket!
                            << ">";
        }

    }
}
