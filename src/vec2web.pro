TEMPLATE    = app
CONFIG      += qt warn_on debug
DEFINES     += NO_FPARSER

unix {
    LIBS    += -L../../qcadlib/lib -lqcad \
               -L../../dxflib/lib -ldxf
}

win32 {
    LIBS    += ../../qcadlib/lib/qcad.lib \
               ../../dxflib/lib/dxflib.lib
}

INCLUDEPATH += ../../dxflib/include \
               ../../qcadlib/include
               
# detect Qt:
exists( $$(QTDIR)/lib/libqt-mt.so ) {
    CONFIG  += thread
}

# detect ming
#unix {
#    exists(../../ming/libming.a) {
#        #LIBS        += -L../../ming -lming
#        LIBS        += ../../ming/libming.a
#        INCLUDEPATH += ../../ming
#        DEFINES     += SWF_SUPPORT
#    }
#}
#win32 {
#    exists(../../ming/win32/debug/libming.lib) {
#        LIBS += ../../ming/win32/debug/libming.lib
#        INCLUDEPATH += ../../ming
#        DEFINES     += SWF_SUPPORT
#    }
#}

HEADERS     = vec2web.h \
              graphicview.h \
              swfpainter.h \
              dxmlpainter.h
SOURCES     = main.cpp \
              vec2web.cpp \
              graphicview.cpp \
              swfpainter.cpp \
              dxmlpainter.cpp
DESTDIR     = ..
TARGET      = vec2web
OBJECTS_DIR = obj
MOC_DIR     = moc
