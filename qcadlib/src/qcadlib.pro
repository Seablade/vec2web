# $Id: qcadlib.pro,v 1.38 2005/02/08 23:31:37 andrew Exp $
TEMPLATE    = lib
DESTDIR     = ../lib
CONFIG      += qt staticlib warn_on release
DEFINES     += RS_NO_COMPLEX_ENTITIES
INCLUDEPATH += ../include
INCLUDEPATH += ../../dxflib/include ../../fparser/include ../../qcadcmd/include

HEADERS     = \
              actions/rs_actioninterface.h \
              actions/rs_preview.h \
              actions/rs_previewactioninterface.h \
              actions/rs_snapper.h \
              creation/rs_creation.h \
              debug/rs_debug.h \
              engine/rs.h \
              engine/rs_application.h \
              engine/rs_arc.h \
              engine/rs_atomicentity.h \
              engine/rs_block.h \
              engine/rs_blocklist.h \
              engine/rs_blocklistlistener.h \
              engine/rs_clipboard.h \
              engine/rs_circle.h \
              engine/rs_color.h \
              engine/rs_constructionline.h \
              engine/rs_datetime.h \
              engine/rs_dimaligned.h \
              engine/rs_dimangular.h \
              engine/rs_dimdiametric.h \
              engine/rs_dimension.h \
              engine/rs_dimlinear.h \
              engine/rs_dimradial.h \
              engine/rs_dir.h \
              engine/rs_document.h \
              engine/rs_ellipse.h \
              engine/rs_entity.h \
              engine/rs_entitycontainer.h \
              engine/rs_file.h \
              engine/rs_fileinfo.h \
              engine/rs_flags.h \
              engine/rs_font.h \
              engine/rs_fontchar.h \
              engine/rs_fontlist.h \
              engine/rs_graphic.h \
              engine/rs_hatch.h \
              engine/rs_insert.h \
              engine/rs_img.h \
              engine/rs_image.h \
              engine/rs_layer.h \
              engine/rs_layerlist.h \
              engine/rs_layerlistlistener.h \
              engine/rs_leader.h \
              engine/rs_line.h \
              engine/rs_pattern.h \
              engine/rs_patternlist.h \
              engine/rs_pen.h \
              engine/rs_point.h \
              engine/rs_polyline.h \
              engine/rs_ptrlist.h \
              engine/rs_regexp.h \
              engine/rs_settings.h \
              engine/rs_solid.h \
              engine/rs_spline.h \
              engine/rs_string.h \
              engine/rs_stringlist.h \
              engine/rs_system.h \
              engine/rs_text.h \
              engine/rs_textstream.h \
              engine/rs_undo.h \
              engine/rs_undoable.h \
              engine/rs_undocycle.h \
              engine/rs_units.h \
              engine/rs_utility.h \
              engine/rs_valuelist.h \
              engine/rs_variabledict.h \
              engine/rs_vector.h \
              fileio/rs_fileio.h \
              filters/rs_filtercxf.h \
              filters/rs_filterdxf.h \
              filters/rs_filterdxf1.h \
              filters/rs_filterinterface.h \
              gui/rs_commandevent.h \
              gui/rs_coordinateevent.h \
              gui/rs_dialogfactory.h \
              gui/rs_dialogfactoryinterface.h \
              gui/rs_dialogfactoryadapter.h \
              gui/rs_event.h \
              gui/rs_eventhandler.h \
              gui/rs_graphicview.h \
              gui/rs_grid.h \
              gui/rs_keyevent.h \
              gui/rs_linetypepattern.h \
              gui/rs_mainwindowinterface.h \
              gui/rs_mouseevent.h \
              gui/rs_painter.h \
              gui/rs_painteradapter.h \
              gui/rs_painterqt.h \
              gui/rs_staticgraphicview.h \
              information/rs_information.h \
              information/rs_infoarea.h \
              modification/rs_modification.h \
              modification/rs_selection.h \
              math/rs_math.h \
              scripting/rs_python.h \
              scripting/rs_simplepython.h \
              scripting/rs_python_wrappers.h \
              scripting/rs_script.h \
              scripting/rs_scriptlist.h
SOURCES     = \ 
              actions/rs_actioninterface.cpp \
              actions/rs_preview.cpp \
              actions/rs_previewactioninterface.cpp \
              actions/rs_snapper.cpp \
              creation/rs_creation.cpp \
              debug/rs_debug.cpp \
              engine/rs_arc.cpp \
              engine/rs_block.cpp \
              engine/rs_blocklist.cpp \
              engine/rs_clipboard.cpp \
              engine/rs_circle.cpp \
              engine/rs_constructionline.cpp \
              engine/rs_dimaligned.cpp \
              engine/rs_dimangular.cpp \
              engine/rs_dimdiametric.cpp \
              engine/rs_dimension.cpp \
              engine/rs_dimlinear.cpp \
              engine/rs_dimradial.cpp \
              engine/rs_document.cpp \
              engine/rs_ellipse.cpp \
              engine/rs_entity.cpp \
              engine/rs_entitycontainer.cpp \
              engine/rs_font.cpp \
              engine/rs_fontlist.cpp \
              engine/rs_graphic.cpp \
              engine/rs_hatch.cpp \
              engine/rs_insert.cpp \
              engine/rs_image.cpp \
              engine/rs_layer.cpp \
              engine/rs_layerlist.cpp \
              engine/rs_leader.cpp \
              engine/rs_line.cpp \
              engine/rs_pattern.cpp \
              engine/rs_patternlist.cpp \
              engine/rs_point.cpp \
              engine/rs_polyline.cpp \
              engine/rs_settings.cpp \
              engine/rs_solid.cpp \
              engine/rs_spline.cpp \
              engine/rs_string.cpp \
              engine/rs_system.cpp \
              engine/rs_text.cpp \
              engine/rs_undo.cpp \
              engine/rs_undoable.cpp \
              engine/rs_units.cpp \
              engine/rs_utility.cpp \
              engine/rs_variabledict.cpp \
              engine/rs_vector.cpp \
              fileio/rs_fileio.cpp \
              filters/rs_filtercxf.cpp \
              filters/rs_filterdxf.cpp \
              filters/rs_filterdxf1.cpp \
              gui/rs_dialogfactory.cpp \
              gui/rs_eventhandler.cpp \
              gui/rs_graphicview.cpp \
              gui/rs_grid.cpp \
              gui/rs_linetypepattern.cpp \
              gui/rs_painter.cpp \
              gui/rs_painterqt.cpp \
              gui/rs_staticgraphicview.cpp \
              information/rs_information.cpp \
              information/rs_infoarea.cpp \
              math/rs_math.cpp \
              modification/rs_modification.cpp \
              modification/rs_selection.cpp \
              scripting/rs_python.cpp \
              scripting/rs_simplepython.cpp \
              scripting/rs_python_wrappers.cpp \
              scripting/rs_script.cpp \
              scripting/rs_scriptlist.cpp
TRANSLATIONS = ts/qcadlib_cs.ts \
               ts/qcadlib_et.ts \
               ts/qcadlib_en.ts \
               ts/qcadlib_da.ts \
               ts/qcadlib_de.ts \
               ts/qcadlib_el.ts \
               ts/qcadlib_fr.ts \
               ts/qcadlib_hu.ts \
               ts/qcadlib_it.ts \
               ts/qcadlib_nl.ts \
               ts/qcadlib_no.ts \
               ts/qcadlib_pl.ts \
               ts/qcadlib_ru.ts \
               ts/qcadlib_sk.ts \
               ts/qcadlib_tr.ts
TARGET      = qcad
OBJECTS_DIR = obj
MOC_DIR     = moc

exists( ../../mkspecs/defs.pro ) {
    include( ../../mkspecs/defs.pro )
}
