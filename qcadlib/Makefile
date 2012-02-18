# Makefile for qcadlib

VERSION = 1.9.5

# qcadlib installation directories
#

# default: /usr/local/...
#LIBDIR = /usr/local/lib
#INCDIR = /usr/local/include/qcadlib

# users home dir:
LIBDIR = $(HOME)/local/lib
INCDIR = $(HOME)/local/include/qcadlib

FIND = find

all:
	$(MAKE) prepare
	-rm -f ./lib/libqcad.a
	$(MAKE) ./lib/libqcad.a

prepare:
	test -d ./include || mkdir -p ./include
	-( cd ./include; rm -f *.h; \
	for hf in `find ../src -name '*.h'`; do \
		ln -s "$$hf" 2> /dev/null || cp "$$hf" .; \
	done )

./lib/libqcad.a: src/Makefile
	$(MAKE) src/Makefile
	cd src && $(MAKE)

src/Makefile:
	cd src && qmake qcadlib.pro

install: ./lib/libqcad.a
	test -d $(LIBDIR) || mkdir -p $(LIBDIR)
	test -d $(INCDIR) || mkdir -p $(INCDIR)
	cp ./lib/libqcad.a $(LIBDIR)
	cp ./include/*.h $(INCDIR)

clean:
	cd src && $(MAKE) clean
	cd test && $(MAKE) clean
	-rm -f ./lib/lib*
	-$(FIND) . -name "*~" -exec rm -f {} \;
  
testing: ./lib/libqcad.a
	-(cd ./test ; $(MAKE) clean; $(MAKE))

docu:
	-(doxygen ./doxygen.cfg)

statistics:
	@echo "Lines in source files:"
	-find -name *.cpp | xargs cat | wc
	@echo "Lines in header files:"
	-find -name *.h | xargs cat | wc

indent:
	-find . -name "*.cpp" | xargs astyle --style=kr
	-find . -name "*.h" | xargs astyle --style=kr
	-find . -name "*.h.orig" | xargs rm
	-find . -name "*.cpp.orig" | xargs rm

dist:	clean
	-rm -d ../doc/classref/html/en/*
	-(cd .. ; cp -r ./qcadlib ./qcadlib_dist)
	-(cd ../qcadlib_dist/qcadlib ; rm config.log config.cache reinstall*)
	-(cd ../qcadlib_dist ; tar fvcz qcadlib-$(VERSION).tar.gz qcadlib)

