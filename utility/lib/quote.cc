#include "utility.h"

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;

string Farsyte::Utility::quote_for_lit(char ch, char qc) {
    if ((32 <= ch) && (ch < 127)) {
        if ((ch == qc) || (ch == '\\'))
            return "\\" + string(1, ch);
        return string(1, ch);
    }
    return "";
}

string Farsyte::Utility::quote_for_lit(string const &str) {
    ostringstream	oss;
    for (size_t i = 0; i < str.size(); ++i)
        oss << quote_for_lit(str[i], '"');
    return oss.str();
}

string Farsyte::Utility::literal(string const &str) {
    ostringstream	oss;
    oss << '"';
    for (size_t i = 0; i < str.size(); ++i)
        oss << quote_for_lit(str[i], '"');
    oss << '"';
    return oss.str();
}
