#pragma once

/** \file
 * \brief Manage BIST for a Package.
 */

#include <iostream>
#include <string>

namespace Bist {
    class Pkg {
        friend class Fun;
    public:
        std::ostream &log;
        Pkg(std::ostream &s,
            std::string const &n);
        ~Pkg();

    private:

        static bool bist_pend;
        static bool bist();

        static bool bist_text(Pkg &p);
    };
}
