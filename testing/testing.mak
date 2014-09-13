# -*- makefile-gmake -*-

testing.lib.cc	:= ${wildcard testing/lib/*.cc}
testing.obj.o	= ${testing.lib.cc:testing/lib/%.cc=testing/obj/%.o}
testing.lib.a	= lib/testing.a

${testing.obj.o}:       testing/obj/%.o:        testing/lib/%.cc
	$P '[cc] %s%s\n' 'testing/lib/' '$*'
	$Q $(COMPILE.cc) -Itesting/inc -Iinc -MD -MF testing/dep/$*.d $(OUTPUT_OPTION) $<

objs::            ${testing.obj.o}

testing.lib.a   = lib/libtesting.a

${testing.lib.a}:	${testing.obj.o}
	$P '[ar] %s\n' 'testing'
	$Q $R $@
	$Q ar q $@ ${testing.obj.o}

libs::            ${testing.lib.a}

testing.test.cc		:= ${wildcard testing/test/test_*.cc}
testing.test.bin	= ${testing.test.cc:testing/test/%.cc=testing/bin/%.exe}
testing.test.out	= ${testing.test.bin:testing/bin/%.exe=testing/log/%_log.xml}

${testing.test.bin}:	${testing.lib.a}

${testing.test.bin}:    testing/bin/%.exe:      testing/test/%.cc
	$Q $P '[ld] %s%s\n' 'testing/bin/' '$*'
	$Q $(LINK.cc) -Iinc testing/test/$*.cc -Llib -ltesting -o $@

tests::                 ${testing.test.bin}

${testing.test.out}:    testing/log/%_log.xml:  testing/bin/%.exe
	$< > $@

runtests::              ${testing.test.out}

build::			objs libs tests runtests

clean::
	$C $R ${testing.obj.o}
	$C $R ${testing.lib.a}
	$C $R ${testing.test.bin}
	$C $R ${testing.test.out}
	$C $R testing/dep/*.d

-include ${wildcard testing/dep/*.d}

.PHONY:         build objs libs tests clean
