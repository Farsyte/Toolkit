# -*- makefile-gmake -*-

matrix.lib.cc	:= ${wildcard matrix/lib/*.cc}
matrix.obj.o	= ${matrix.lib.cc:matrix/lib/%.cc=matrix/obj/%.o}
matrix.lib.a	= lib/matrix.a

${matrix.obj.o}:        matrix/obj/%.o:         matrix/lib/%.cc
	$P '[cc] %s%s\n' 'matrix/lib/' '$*'
	$Q $(COMPILE.cc) -Imatrix/inc -Iinc -MD -MF matrix/dep/$*.d $(OUTPUT_OPTION) $<

objs::            ${matrix.obj.o}

matrix.lib.a    = lib/libmatrix.a

${matrix.lib.a}:	${matrix.obj.o}
	$P '[ar] %s\n' 'matrix'
	$Q $R $@
	$Q ar q $@ ${matrix.obj.o}

libs::            ${matrix.lib.a}

matrix.test.cc		= ${wildcard matrix/test/test_*.cc}
matrix.test.bin		= ${matrix.test.cc:matrix/test/%.cc=matrix/bin/%.exe}
matrix.test.out		= ${matrix.test.bin:matrix/bin/%.exe=matrix/log/%_log.xml}

${matrix.test.bin}:	$${testing.lib.a}
${matrix.test.bin}:	${matrix.lib.a}

${matrix.test.bin}:     matrix/bin/%.exe:       matrix/test/%.cc
	$Q $P '[ld] %s%s\n' 'matrix/bin/' '$*'
	$Q $(LINK.cc) -Iinc matrix/test/$*.cc -Llib -ltesting -lmatrix -o $@

tests::                 ${matrix.test.bin}

${matrix.test.out}:     matrix/log/%_log.xml:   matrix/bin/%.exe
	$Q $P '[rt] %s%s\n' 'matrix/bin' '$*'
	$Q $< > $@

runtests::              ${matrix.test.out}

build::			objs libs tests runtests

clean::
	$C $R ${matrix.obj.o}
	$C $R ${matrix.lib.a}
	$C $R ${matrix.test.bin}
	$C $R ${matrix.test.out}
	$C $R matrix/dep/*.d

-include ${wildcard matrix/dep/*.d}

.PHONY:         build objs libs tests clean
