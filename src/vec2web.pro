TEMPLATE	= app
CONFIG		+= qt warn_on debug ming

unix {
	LIBS        += -L../../qcadactions/lib -lqcadactions \
	               -L../../qcadlib/lib -lqcad \
				   -L../../dxflib/lib -ldxf
}
win32 {
	LIBS        += ../../qcadactions/lib/qcadactions.lib \
	               ../../qcadlib/lib/qcad.lib \
				   ../../dxflib/lib/dxflib.lib
}
INCLUDEPATH += ../../dxflib/include \
               ../../qcadlib/include \
               ../../qcadactions/include

unix {
	exists(../../ming/libming.a) {
		#LIBS        += -L../../ming -lming
		LIBS        += ../../ming/libming.a
		INCLUDEPATH += ../../ming
		DEFINES     += SWF_SUPPORT
	}
}
win32 {
	exists(../../ming/win32/debug/libming.lib)
		LIBS += ../../ming/win32/debug/libming.lib
		INCLUDEPATH += ../../ming
		DEFINES     += SWF_SUPPORT
	}
}

# detect Qt:
exists( $$(QTDIR)/lib/libqt-mt.so ) {
	CONFIG += thread
}


HEADERS		= vec2web.h \
              graphicview.h \
			  swfpainter.h \
			  dxmlpainter.h
SOURCES		= vec2web.cpp \
              graphicview.cpp \
			  swfpainter.cpp \
			  dxmlpainter.cpp \
              main.cpp 
DESTDIR     = ..
TARGET		= vec2web
OBJECTS_DIR = obj
MOC_DIR     = moc
