Requirements for the Matrix Class
-----------------------------------

The Matrix Class shall provide:

  * template parameters:
    * `T` that determines the data type used for the elements
    * `Nr` that determines the number of rows in the matrix
    * `Nc` that determines the number of columns in the matrix
  * public class types:
    * `value_type` indicating the type of the elements
      * reference, const_reference, pointer, and const_pointer
        as customary in the C++ standard library.
  * public class methods:
    * `rows()` returning the number of rows in the matrix
    * `cols()` returning the number of columns in the matrix
    * `size()` returning the total number of elements in the matrix
  * constructors:
    * default constructor initializes each element to T().
    * diagonal constructor that assigns a specified value to diagonal elements.
  * comparison:
    * equality comparison that returns true if corresponding elements compare equal.
