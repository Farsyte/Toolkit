XML Expected by the JUnit Parser
================================

Bamboo expects to see a collection of test results, each of which has
the following data attached:

  * Test Class and Case Names
  * Elapsed Time
  * PASS or FAIL indication
  * Supporting text for FAIL cases

The Bamboo JUnit Parser recognizes the following XML elements:

Element: testsuites
-------------------

Recognized but no data is retained.

Element: testsuite
------------------

Copy the `name` attribute into `suiteClassName` on entry.

Typical usage by this package:

		<testsuite name="TestClassName">
			...
		</testsuite>


Element: properties
-------------------

Recognized but no data is retained.

Element: property
-----------------

Recognized but no data is retained.

Element: testcase
-----------------

This element (and the elements it contains) represents the results of
a single test. If the `classname` attribute is provided and does not
contain a `$` character, it is used to represent the Class Name of the
test; otherwise, the `suiteClassName` currently in effect is used.
The `name` attribute gives the actual name of the test case.  The
`time` attribute indictes the duration of the test.

At the *close* of the element, the test case is added to the "failed"
test list if any subelement marked the test case as having failures;
otherwise, it is added to the "passed" test list.

Element: error
--------------

This element records that an error occurred while running the
currently open test case, attaching the content of the element as
supporting text.

Element: failure
----------------

This element records that a condition has failed in the currently open
test case. The content of the `message` property, concatinated with a
line separator and the content of the element, are attached to the
failure as supporting text.

Element: system-out
-------------------

If a test case is currently open, the content of this element is
attached to the test case as its system output. If there is no test
case currently open, the content of the element is stashed as a global
system output. Note that the output stash is replaced, not accumulated.

Element: system-err
-------------------

The content of this element is captured as a global error output,
replacing any prior global error output.

Element: skipped
----------------

Recognized but no data is retained.
		
In particular note that `skipped` elements do not cause the enclosing
test case to be marked as failed.

