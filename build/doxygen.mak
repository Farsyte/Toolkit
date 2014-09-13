# -*- makefile-gmake -*-

all.doxy        := ${shell find . -name Doxyfile -print}
doxy.log        = ${all.doxy:%=%.log}
doxy.err        = ${all.doxy:%=%.err}
doxy.html	= ${all.doxy:%/Doxyfile=%/html}
doxy.latex	= ${all.doxy:%/Doxyfile=%/latex}

# By default, we only run doxygen if the logput log file has been
# removed. The alternative, here, is to add ${doxy.log} to the
# list of phony targets, forcing a rebuild every time.
#
# Projects that want doxygen rerun when files change can add a
#	Doxygen.log:	list-of-files
# dependency as appropriate.

${doxy.log}:    %.log:          %
	$C $R ${dir $@}html ${dir $@}latex
	$P '[dx] %s\n' '${dir $*}'
	$Q (cd ${dir $@}; doxygen) 2>&1 > $*.log | \
	   sed 's|^$(PWD)/||' > $*.err
	$Q cat $*.err

dox doxygenate::	${doxy.log}

undox::
	$C $R ${doxy.log} ${doxy.err} ${doxy.html} ${doxy.latex}

.PHONY:         dox undox doxygenate
