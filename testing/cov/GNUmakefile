# -*- makefile-gmake -*-
include ../../GNUmakefile.sub

GCDA		:= ${wildcard ${OBJD}*.gcda}

ifneq ($(GCDA),)
build::
	$C gcov -r ${GCDA} | sed 'N;s/\n/ /' | \
                sed -n '/File/p' | \
		sed "s|File '${LIBD}|gcov: |" | \
		sed "s|' Lines executed:| |"
endif

clean::
	$C $R *.gcov
