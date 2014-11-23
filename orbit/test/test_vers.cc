#include "orbit.hh"
#include "testing.hh"

using std::string;
using std::vector;

UT_CASE(Orbit, Versions) {
    
    const char ** vers = Farsyte::Orbit::orbit_versions();

    ASSERT_NotNull(vers);
    ASSERT_NotNull(vers[0]);
    EXPECT_EQ(vers[0], string(_orbit_h));
    
}
