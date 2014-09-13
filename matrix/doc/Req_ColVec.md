Requirements for the ColVec Class
-----------------------------------

The ColVec Template shall provide:

  * Inheritance from Matrix template
  * template parameters:
    * `T` that determines the data type used for the elements
    * `N` that determines the number of rows in the colVec
  * public class types:
    * `value_type` indicating the type of the elements
      * reference, const_reference, pointer, and const_pointer
        as customary in the C++ standard library.
  * public class methods:
    * `size()` returning the total number of elements in the vector
  * constructors:
    * default constructor initializes each element to T().
	* construction from an initializer list
	* construction of a duplicate column vector
  * array subscript conventions:
	* Subscripts start at 1.
	* Row subscript runs up to N inclusive.
  * accessors:
	* read-only reference access by row index
	* modifiable reference access by row index
	* operation is UNDEFINED if the index is out of range
  * comparison:
    * equality comparison that returns true if corresponding elements compare equal.
