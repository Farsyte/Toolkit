# -*- makefile-gmake -*-
include ../../GNUmakefile.sub

GCDA            := ${wildcard ${OBJD}*.gcda}

ifneq ($(GCDA),)

build::
	$C gcov ${GCDA} | sed 'N;s/\n/ /'                            | \
		grep "^File '${top.abs}"                             | \
		sed "s|File '${top.abs}|gcov: |"                     | \
		sed "s|' Lines executed:| |"
	$Q for gcov in *.gcov                                        ; \
	   do                                                          \
	       head -1 "$$gcov"                                      | \
	       grep -q ' 0:Source:${LIBD}'                          || \
	       rm -f "$$gcov"                                        ; \
	   done

endif

clean::
	$C $R *.gcov
