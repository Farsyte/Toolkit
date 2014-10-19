# -*- makefile-gmake -*-

simple.lib.cc	:= ${wildcard simple/lib/*.cc}
simple.obj.o	= ${simple.lib.cc:simple/lib/%.cc=simple/obj/%.o}
simple.lib.a	= lib/simple.a

${simple.obj.o}:        simple/obj/%.o:         simple/lib/%.cc
	$P '[cc] %s%s\n' 'simple/lib/' '$*'
	$Q $(COMPILE.cc) -Isimple/inc -Iinc -MD -MF simple/dep/$*.d $(OUTPUT_OPTION) $<

objs::            ${simple.obj.o}

simple.lib.a    = lib/libsimple.a

${simple.lib.a}:	${simple.obj.o}
	$P '[ar] %s\n' 'simple'
	$Q $R $@
	$Q ar q $@ ${simple.obj.o}

libs::            ${simple.lib.a}

simple.test.cc		= ${wildcard simple/test/test_*.cc}
simple.test.bin		= ${simple.test.cc:simple/test/%.cc=simple/bin/%.exe}
simple.test.out		= ${simple.test.bin:simple/bin/%.exe=simple/log/%_log.xml}

${simple.test.bin}:	${simple.lib.a}
${simple.test.bin}:	$${testing.lib.a}
${simple.test.bin}:	$${utility.lib.a}

${simple.test.bin}:     simple/bin/%.exe:       simple/test/%.cc
	$Q $P '[ld] %s%s\n' 'simple/bin/' '$*'
	$Q $(LINK.cc) -Iinc simple/test/$*.cc -Llib -lsimple -ltesting -lutility -o $@

tests::                 ${simple.test.bin}

${simple.test.out}:     simple/log/%_log.xml:   simple/bin/%.exe
	$Q $P '[rt] %s%s\n' 'simple/bin' '$*'
	$Q $< > $@

runtests::              ${simple.test.out}

build::			objs libs tests runtests

clean::
	$C $R ${simple.obj.o}
	$C $R ${simple.lib.a}
	$C $R ${simple.test.bin}
	$C $R ${simple.test.out}
	$C $R simple/dep/*.d

-include ${wildcard simple/dep/*.d}

.PHONY:         build objs libs tests clean
