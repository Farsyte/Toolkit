#include "utility.hh"

using std::string;
using std::vector;

const char ** Farsyte::Utility::utility_versions() {
    static const char * ret[] = {
            _utility_h,
            0
    };
    return ret;
}
