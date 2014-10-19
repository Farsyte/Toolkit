#include <iostream>
#include <iomanip>

using std::cerr;
using std::endl;
using std::setw;

int main(int argc, char **argv) {
    cerr << argv[0] << endl;
    for (int argi = 1; argi < argc; ++argi)
        cerr << setw(6) << argi << ": " << argv[argi] << endl;
    return 0;
}
