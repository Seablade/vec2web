# Makefile for QCad

VERSION = 0.0.2

# vec2web installation directories

# default: /usr/local/...
#LIBDIR = /usr/local/lib
#INCDIR = /usr/local/include/

# users home dir:
INSTALLDIR = $(HOME)/local

FIND = find

all: vec2web

#prepare:

vec2web: src/Makefile src/*.h src/*.cpp ../dxflib/lib/libdxf.a ../qcadlib/lib/libqcad.a
	- rm vec2web
	cd src && $(MAKE)

src/Makefile: src/vec2web.pro
	cd src && qmake vec2web.pro

clean:
	cd src && $(MAKE) clean
	- rm vec2web
	-$(FIND) . -name "*~" -exec rm -f {} \;
  
docu:
	-(doxygen ./doxygen.cfg)

statistics:
	@echo "Lines in source files:"
	-find -name *.cpp | xargs cat | wc
	@echo "Lines in header files:"
	-find -name *.h | xargs cat | wc

dist:	clean

