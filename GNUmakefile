# -*- makefile-gmake -*-
wild.mak        := ${shell find . -name '*.mak' -print | env LC_COLLATE=C sort}
default::	build
include ${wild.mak}
