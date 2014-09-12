# -*- makefile-gmake -*-

utility.lib.cc	:= ${wildcard utility/lib/*.cc}
utility.obj.o	= ${utility.lib.cc:utility/lib/%.cc=utility/obj/%.o}
utility.lib.a	= lib/utility.a

${utility.obj.o}:       utility/obj/%.o:        utility/lib/%.cc
	$P '[cc] %s%s\n' 'utility/lib/' '$*'
	$Q $(COMPILE.cc) -Iutility/inc -Iinc -MD -MF utility/dep/$*.d $(OUTPUT_OPTION) $<

objs::            ${utility.obj.o}

utility.lib.a   = lib/libutility.a

${utility.lib.a}:	${utility.obj.o}
	$P '[ar] %s\n' 'utility'
	$Q $R $@
	$Q ar q $@ ${utility.obj.o}

libs::            ${utility.lib.a}

utility.test.cc		= ${wildcard utility/test/test_*.cc}
utility.test.bin	= ${utility.test.cc:utility/test/%.cc=utility/bin/%.exe}
utility.test.out	= ${utility.test.bin:utility/bin/%.exe=utility/log/%_log.xml}

${utility.test.bin}:	${testing.lib.a}
${utility.test.bin}:	${utility.lib.a}

${utility.test.bin}:    utility/bin/%.exe:      utility/test/%.cc
	$Q $P '[ld] %s%s\n' 'utility/bin/' '$*'
	$Q $(LINK.cc) -Iinc utility/test/$*.cc -Llib -ltesting -lutility -o $@

tests::                 ${utility.test.bin}

${utility.test.out}:    utility/log/%_log.xml:  utility/bin/%.exe
	$< > $@

runtests::              ${utility.test.out}

build::			objs libs tests runtests

clean::
	$C $R ${utility.obj.o}
	$C $R ${utility.lib.a}
	$C $R ${utility.test.bin}
	$C $R ${utility.test.out}
	$C $R utility/dep/*.d

-include ${wildcard utility/dep/*.d}

.PHONY:         build objs libs tests clean
