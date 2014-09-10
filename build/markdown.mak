# -*- makefile-gmake -*-

all.md          := ${shell find . -name \*.md -print}
md.html		:= ${all.md:%.md=%.html}

${md.html}:     %.html:         %.md
	$P '[md] %s\n' '$*'
	$Q markdown '$*.md' > '$*.html'

md-to-html::		${md.html}
dox::			${md.html}
undox::		; $C $R ${md.html}

.PHONY:         dox undox md-to-html
