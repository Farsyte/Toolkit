#include "utility.h"

using std::ostringstream;
using std::istringstream;
using std::vector;
using std::string;
using Farsyte::Utility::streamlines;

/** Get array of lines sent to a string stream.
*/
vector<string>
Farsyte::Utility::streamlines(ostringstream &oss) {
    string str(oss.str());
    istringstream iss(str);
    string line;
    vector<string> vos;
    while (getline(iss, line))
        vos.push_back(line);
    return vos;
}

