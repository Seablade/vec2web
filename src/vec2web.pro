TEMPLATE	= app
CONFIG		+= qt warn_on debug
unix {
	LIBS        += -L../../qcadguiqt/lib -lqcadguiqt -L../../qcadlib/lib -lqcad -L../../dxflib/lib -ldxf -lgd -lg2
}
win32 {
	LIBS        += ../../qcadguiqt/lib/qcadguiqt.lib ../../qcadlib/lib/qcad.lib ../../dxflib/lib/dxflib.lib
}
INCLUDEPATH += ../../dxflib/include ../../qcadlib/include ../../qcadguiqt/include
HEADERS		= vec2web.h \
              graphicview.h
SOURCES		= vec2web.cpp \
              graphicview.cpp \
              main.cpp 
DESTDIR     = ..
TARGET		= vec2web
OBJECTS_DIR = obj
MOC_DIR     = moc
