# -*- makefile-gmake -*-

orbit.lib.cc	:= ${wildcard orbit/lib/*.cc}
orbit.obj.o	= ${orbit.lib.cc:orbit/lib/%.cc=orbit/obj/%.o}
orbit.lib.a	= lib/orbit.a

${orbit.obj.o}:        orbit/obj/%.o:         orbit/lib/%.cc
	$P '[cc] %s%s\n' 'orbit/lib/' '$*'
	$Q $(COMPILE.cc) -Iorbit/inc -Iinc -MD -MF orbit/dep/$*.d $(OUTPUT_OPTION) $<

objs::            ${orbit.obj.o}

orbit.lib.a    = lib/liborbit.a

${orbit.lib.a}:	${orbit.obj.o}
	$P '[ar] %s\n' 'orbit'
	$Q $R $@
	$Q ar q $@ ${orbit.obj.o}

libs::            ${orbit.lib.a}

orbit.test.cc		= ${wildcard orbit/test/test_*.cc}
orbit.test.bin		= ${orbit.test.cc:orbit/test/%.cc=orbit/bin/%.exe}
orbit.test.out		= ${orbit.test.bin:orbit/bin/%.exe=orbit/log/%_log.xml}

${orbit.test.bin}:	${orbit.lib.a}
${orbit.test.bin}:	$${testing.lib.a}
${orbit.test.bin}:	$${utility.lib.a}
${orbit.test.bin}:	$${simple.lib.a}

${orbit.test.bin}:     orbit/bin/%.exe:       orbit/test/%.cc
	$Q $P '[ld] %s%s\n' 'orbit/bin/' '$*'
	$Q $(LINK.cc) -Iinc orbit/test/$*.cc -Llib -lorbit -lsimple -ltesting -lutility -o $@

tests::                 ${orbit.test.bin}

${orbit.test.out}:     orbit/log/%_log.xml:   orbit/bin/%.exe
	$Q $P '[rt] %s%s\n' 'orbit/bin' '$*'
	$Q $< > $@

runtests::              ${orbit.test.out}

build::			objs libs tests runtests

clean::
	$C $R ${orbit.obj.o}
	$C $R ${orbit.lib.a}
	$C $R ${orbit.test.bin}
	$C $R ${orbit.test.out}
	$C $R orbit/dep/*.d

-include ${wildcard orbit/dep/*.d}

.PHONY:         build objs libs tests clean
