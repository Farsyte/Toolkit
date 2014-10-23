#include "orbit.hh"

using std::string;
using std::vector;

namespace Farsyte {
    namespace Orbit {

        vector<string> const &orbit_versions() {
            static const vector<string> ret{
                _orbit_h,
                    };
            return ret;
        }

    }
}
