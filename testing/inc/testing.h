#ifndef _testing_h
#define _testing_h

/** \file
 * \brief Testing Library Exported API
 *
 * This file provides data types, function prototypes and macro
 * definitions for C code using this Testing library.
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace Farsyte {
    namespace Testing {

        class Log;
        class Suite;
        class Test;
        class Oops;

        class Log {
          public:
            std::ostream & out;
            Suite *curr;
            size_t suites;
            size_t tests;

            size_t failed_tests;
            size_t skipped_tests;
            size_t errored_tests;
            size_t total_fails;
            size_t total_skips;
            size_t total_errors;

            Log(std::ostream &out, std::string const &name);
            ~Log();
        };

        class Suite {
          public:
            Log &ref;
            Test *curr;
            size_t tests;

            size_t failed_tests;
            size_t skipped_tests;
            size_t errored_tests;
            size_t total_fails;
            size_t total_skips;
            size_t total_errors;

            Suite(Log &ref, std::string const &name);
            ~Suite();
        };

        class Test 
            : public std::ostringstream
        {
          public:
            Suite &ref;
            size_t fails;
            size_t skips;
            size_t errors;

            Test(Suite &ref, std::string const &name);
            void fail(std::string const &cond);
            void skip(std::string const &cond);
            void error(std::string const &cond);
            ~Test();
        };

        class Oops {
          public:
            std::string         file;
            int                 line;
            std::string         cond;
            mutable bool        pend;

            Oops(
                std::string     f,
                int             l,
                std::string     c);

            std::ostream& print(std::ostream&s) const;

            void cancel() const;

            ~Oops();
        };
    }
}

extern std::ostream& operator<< (std::ostream&s, Farsyte::Testing::Oops const &f);

#endif//_testing_h
