#include "utility.h"

using std::string;

string Farsyte::Utility::utility_version(int i)
{ 
  switch (i) {
  case 0: return _utility_h;
  default: return "";
  }
}
