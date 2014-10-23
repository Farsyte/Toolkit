#include "orbit.hh"
#include "testing.hh"

using std::string;
using std::vector;

UT_CASE(Orbit, Versions) {
    
    vector<string> const & vers = Farsyte::Orbit::orbit_versions();

    EXPECT_GE(vers.size(), 1u);
    EXPECT_EQ(vers[0], string(_orbit_h));
    
};
