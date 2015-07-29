#pragma once

#include <iostream>

namespace Matrix {

template<int M, int N, typename Data>
struct R {
    Data _[M][N];

    static bool bist(std::ostream &s) {
        s << __PRETTY_FUNCTION__ << std::endl;
        return (bool)s;
    }
};

}
