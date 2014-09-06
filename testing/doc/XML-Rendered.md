Bamboo Rendering of XML Data
============================

Example Test File:

        <?xml version="1.0" encoding="UTF-8"?>
        <testsuites name="ut_demo_log.xml">
          <testsuite name="suite1">
            <testcase name="test1">
            </testcase>
            <testcase name="test2">
              <failure message="justfail">
              </failure>
              <failure message="cond2">
        cond2 supporting text line 1
        cond2 supporting text line 2
              </failure>
            </testcase>
            <testcase name="test3">
              <failure message="cond1">
        cond1 supporting text line 1
        cond1 supporting text line 2 with no EOL
              </failure>
            </testcase>
          </testsuite>
        </testsuites>


The build summary presents three or four counts:

  * New failures in this run
  * Existing failures common with prior run
  * Failures fixed in this run
  * Failures in Quarantine (only if nonzero)

Below that, results are presented in detail, grouped
into new failures, existing failures, and tests fixed.
Each result is in an expandable and collapsable row
of the table.

When collapsed, the row provides:

  * Suite name, from `name` attribute of `testsuite` element
  * Test name, from `name` element of `testcase` eleemnt
  * Failing since (hotlink)
  * Containing Job (hotlink)
  * Duration, from `time` attribute of `testcase` element
  * Tool Menu

If the row is expanded, a text box appears containing the `message`
attribute of each `failure` message, followed a blank line and all of
the supporting text attached to that failure.  Note that there may be
multiple `failure` elements associated with each `testcase` element,
and the data from them are presented sequentially, separated by a
blank line.

Information about Quarantined tests is not presented on the Build
Summary page but appears if you click on the Quarantine count.

