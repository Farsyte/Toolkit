#ifndef _testing_oops_h
#define _testing_oops_h "testing oops v0.1" /**< for header vs library matching */

/** \file
* * \brief Testing Oops Interface
*/

#include <string>

namespace Farsyte {
    namespace Testing {

        /** The Oops Object.
        *
        * Base class for Exception heirarchy
        * for the Testing library.
        * Errors in the Testing library or in
        * the way test code uses the testing library
        * MAY be reported by throwing an object of
        * a class derived from Oops.
        */
        class Oops {
        public:
            std::string file;
            /**< source file name. */
            int line;
            /**< source line number. */
            std::string cond;
            /**< one-line failed condition text */
            mutable bool pend; /**< true if not yet dealt with */

            /** Create a new Oops object.
            * \param f - source file name.
            * \param l - source line number.
            * \param c - condition that was violated.
            */
            Oops(
                    std::string f,
                    int l,
                    std::string c);

            /** Print exception details to output stream.
            * \param s what stream gets the output text.
            * \returns the stream after sending the text.
            * This method produces all available details
            * from this exception object onto the specified
            * output stream (and marks the object as having
            * been printed).
            */
            virtual std::ostream &print(std::ostream &s) const;

            /** Cancel exception printing.
            *
            * This method simply marks the object as having
            * been printed, without the overhead of actually
            * printing the details.
            */
            virtual void cancel() const;

            /** Object Destructor.
            *
            * If the object has not been printed (or cancelled),
            * prints the exception details to the standard error
            * output. All resources owned by the object are released.
            */
            virtual ~Oops();
        };


    }
}

#endif//_testing_oops_h
