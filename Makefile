# Generated automatically from Makefile.in by configure.

prefix =	/usr/local
exec_prefix =	${prefix}
bindir =	${exec_prefix}/bin

VERSION = 0.0.1

OBJF =    src/main.o \
          src/vec2web.o
EXTERN_LIBS = -L/usr/local/lib -lg2 -L$(HOME)/local/lib -ldxflib -lgd -lpng -lz -lm -L/usr/X11R6/lib -lX11
INCLUDES = -I$(HOME)/local/include

all: vec2web

clean:
	@echo "Cleaning project..."
	@find . -name '*.o' -exec rm "{}" \;
	@if [ -f vec2web ]; then rm -f vec2web; fi

distclean: clean
	rm -f config.log config.cache Makefile config.status

vec2web: $(OBJF)
	c++ -o vec2web $(OBJF) $(EXTERN_LIBS)

%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O3 -Wall $< -o $@

demo:   ./lib/libdxflib.a
	(cd ./demo ; make)
 
docu:
	-(doxygen ./doxygen.cfg)
	-(cd doc; tar fvcz classref.tar.gz classref; mv classref.tar.gz ../../homepage/htdocs/archives/ )
 
dist:   clean
	-rm -d ./doc/classref/html/en/*
	-(cd .. ; cp -r ./vec2web ./vec2web_dist)
	-(cd ../vec2web_dist/vec2web ; rm config.log config.cache reinstall*)
	-(cd ../vec2web_dist ; tar fvcz vec2web-$(VERSION).tar.gz vec2web)

