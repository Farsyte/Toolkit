Documentation for the publicly exported interfaces
to the libraries provided by the Farsyte Toolkit.

A Note on Namespaces
--------------------

All interfaces live within the `Farsyte` namespace, to avoid
collisions with simiarly named things defined elsewhere.

Header File Overview
====================

Farsyte::Utility "utility.hh"
----------------

The `utility.hh` header collects general utility code that
is not associated with any of the larger packages within
the toolkit project. This could be code that is shared
across multiple packages (without an obvious owner), or it
could be entire packages that are simply too small to
warrant tracking as their own library.

Farsyte::Testing "testing.h"
----------------

The `testing.hh` header provides declarations for the API
for the library that is used to record test results in a
form that allows an automated build system (currently the
Bamboo continuous intergration system from Atlassian) to
track testing results.

The `Testing` Library implements four classes:

  * The [Oops](classFarsyte_1_1Testing_1_1Oops.html) class
	is the base class for exceptions thrown within
	the `Testing` library representing failures of
	the library or failure to follow the requirements
	of the library when calling it.

  * The [Test](classFarsyte_1_1Testing_1_1Test.html) class
	represents a single test, counting as one test when presenting
	counts of tests passed or failed. Tests may indicate one or more
	conditions that fail or were skipped, with supporting text, as
	well as errors occurring in the testing process.
	It is not uncommon for a Test to correspond to a single method
    name within a class, and for the code to test various aspects of
    the method in sequence.
	If two Test objects have the same test name and the same suite
    name, their results will be combined during reporting.

  * The [Suite](classFarsyte_1_1Testing_1_1Suite.html) class
	represents a collection of Test objects that are logically
	related; tests with the same Suite name are grouped together when
	reporting summaries of test results.
    It is not uncommon for a Suite to correspond to a single Class to
    be tested within a library.
	If two Suite objects have the same name, their results will be
    combined during reporting (even if they come from tests in quite
    different subprojects). Risks associated with this can be
    mitigated by assuring that class names are distinct between
    subprojects of a superproject, when tests are run across the
    entire superproject as a unit.

  * The [Log](classFarsyte_1_1Testing_1_1Log.html) class
	corresponds to a single stream of test output produced by
	sequentially running a series test suites, each of which
	sequentially runs a series of test cases. Note that the Log class
	allows test programs to have multiple Log objects open at once,
	allowing a test program to persue multiple test series in parallel
	if this is appropriate and useful.

  * The [Fixture](classFarsyte_1_1Testing_1_1Fixture.html) class
	provides a simple light testing framework that encapsulates
	the use of the various Testing classes above within macros
	intended to make the tests themselves easier to read. Code
	using this facility should use it via the varios `UT_` macros
	provided in the header files.

Farsyte::Simple "simple.hh"
---------------

The `simple.hh` header provides declarations for the API
for the library that implements non-template versions of
Matrix, Vector, and Quaternion math. The simplification
is that the components are all `double` and the dimensions
are all `THREE` (except of course Quaternion, which is
a scalar plus a three-vector).

  * The [Col](classFarsyte_1_1Simple_1_1Col.html) class
	encapsulates a column three-vector. Operations
	supported include (C Struct style) construction,
	comparison, subscripting, Add/Subtract, Scale
	up and down by a scalar value, dot product, cross
	product, square of the two-norm and the two-norm,
	as well as a simple "print to stream" method.
	This class is the preferred representation for
	use when manipulating three-vectors.

  * The [Row](classFarsyte_1_1Simple_1_1Row.html) class
	encapsulates a row three-vector. Operations
	supported include (C Struct style) construction,
	comparison, subscripting, Add/Subtract, Scale
	up and down by a scalar value, dot product, cross
	product, square of the two-norm and the two-norm,
	as well as a simple "print to stream" method.

  * The [Mat](classFarsyte_1_1Simple_1_1Mat.html) class
	encapsulates a three-by-thee matrix. Operations
	supported include a number of constructors,
	comparison, subscripting, Add/Subtract, Scale
	up and down by a scalar value, matrix multiply,
	multiply matrix by column vector, and a simple
    "print-to-stream" method.

  * The [Quat](classFarsyte_1_1Simple_1_1Quat.html) class
	encapsulates a Quaternion (four coefficient
	hypercomplex variable). Operations
	supported include a number of constructors,
	comparison, component access, Add/Subtract, Scale
	up and down by a scalar value, square of the
	two-norm, two-norm, quaternion multiply,
	inversion, quaternion divide, extraction of a
	corresponding scale-and-rotate matrix, operating
	directly on a vector, and a simple
    "print-to-stream" method.
	
Farsyte::Matrix "matrix.hh"
---------------

The template-based Matrix / Vector / Quaternion code is
currently on hold pending updates to development tools.

Matrix math is provided as a generalized template for dense
rectangular matrices, a derived template for working with column
vectors, and a class representing a position in a three dimensional
state space (such as distance north, east, and above the flagpole).

The `Matrix` Library implements two templates and one class:

  * The [Matrix](classFarsyte_1_1Matrix_1_1Matrix.html) class
	template supports dense rectangular matrices with any small
	positive integer number of rows and columns, containing data
	elements of any data type that supports the desired operations.
	This class currently provides class methods retrieving the
	dimensions of the matrix, and member methods providing the
	operations listed here.  More operations will be added once I am
	happy with code quality, test coverage, and documentation for
	these operations:
    * Initialization
    * Addition
    * Difference
    * Negation
    * Transpose

  * The [ColVec](classFarsyte_1_1Matrix_1_1Colvec.html) class template
 	is a proxy class providing the obvious API adjustments to use
	for column vectors, which are simply a one-column matrix.
	The API differences mainly involve not having to redundantly
 	specify column numbers when working with a ColVec class.

  * The [TriVec](classFarsyte_1_1Matrix_1_1TriVec.html) class
	likewise provides for a three-element column vector such as might
	be used to represent a Position (north, east and above the
	flagpole), Velocity, Direction, and so on.
	The `TriVec` class adds the Cross Product operation, which is
    not provided for general Matrix and Column Vector objects.

