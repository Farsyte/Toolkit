#include "utility.h"

using std::ostringstream;
using std::string;

string Farsyte::Utility::htmlify (char ch)
{
  switch (ch) {
    case '"': return "&quot;";
    case '&': return "&amp;";
    case '\'': return "&apos;";
    case '<': return "&lt;";
    case '>': return "&gt;";
    case '\n': return "\n";
    case '\t': return "\t";
    default:
      if ((32 <= ch) && (ch < 127))
        return string (1, ch);
      return "&block;";
  }
}

string Farsyte::Utility::htmlify (string const &str)
{
  ostringstream oss;
  for (size_t i = 0; i < str.size (); ++i)
    oss << htmlify (str[i]);
  return oss.str ();
}
