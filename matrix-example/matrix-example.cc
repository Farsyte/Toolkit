#include "matrix.hh"

#include <iostream>
using std::cout;

int main() {
    bool ec = true;

    ec = Matrix::R<3,2,int>::bist(cout) && ec;

    return ec ? EXIT_SUCCESS : EXIT_FAILURE;
}
