# Generated automatically from Makefile.in by configure.

prefix =	/usr/local
exec_prefix =	${prefix}
bindir =	${exec_prefix}/bin

VERSION = 0.0.1

OBJF =    src/main.o \
          src/vec2web.o
EXTERN_LIBS = -L/usr/local/lib -lg2 -lgd -lpng -lz -lm -lfreetype -ljpeg -L$(HOME)/local/lib -lqcad -ldxf -L$(QTDIR)/lib -lqt -L/usr/X11R6/lib -lX11
INCLUDES = -I$(HOME)/local/include -I$(QTDIR)/include

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

docu:
	-(doxygen ./doxygen.cfg)
 
dist:   clean
	-rm -d ./doc/classref/html/en/*

