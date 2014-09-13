Requirements for the Matrix Class
-----------------------------------

The Matrix Template shall provide:

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
    * construction of a duplicate matrix
    * For subclasses: array constructor for value construction.
  * array subscript conventions:
    * First subscript is Row, second subscript is Column.
	* Subscripts start at 1.
	* Row subscript runs up to Nr inclusive.
	* Column subscript runs up to Nc inclusive.
	* Data stored in Column-Major order
  * accessors:
	* read-only reference access by row and column index
	* modifiable reference access by row and column index
	* operation is UNDEFINED if the index is out of range
  * comparison:
    * equality comparison that returns true if corresponding elements compare equal.
