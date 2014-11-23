#include "orbit.hh"

using std::string;
using std::vector;

namespace Farsyte {
    namespace Orbit {

        const char ** orbit_versions() {
            static const char * ret[] = {
                _orbit_h,
                0
            };
            return ret;
        }

    }
}
