#include "utility.h"

using std::string;
using std::vector;

vector<string> const & Farsyte::Utility::utility_versions ()
{
  static const vector<string> ret{
      _utility_h,
  };
  return ret;
}
