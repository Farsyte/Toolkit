#pragma once

/** \file
 * \brief Manage BIST for a Function.
 */

#include <iostream>
#include <string>

namespace Bist {
    class Pkg;
    class Fun {
        friend class Pkg;
    public:
        Pkg &pkg;
        std::ostream &log;
        Fun(Pkg &p,
            std::string const &n);
        ~Fun();

        bool pass();
        bool skip();
        bool fail();
        bool error();

        static bool bist(std::ostream &so);

    private:

        static bool bist_noop(Pkg &p);
        static bool bist_pass(Pkg &p);
        static bool bist_skip(Pkg &p);
        static bool bist_fail(Pkg &p);
        static bool bist_error(Pkg &p);

        bool bist(int line, std::istream &si, std::string const &ex);
        bool bist(int line, std::istream &si);
    };
}
