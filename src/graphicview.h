/*****************************************************************************
**  $Id: graphicview.h,v 1.9 2003/04/22 12:08:55 andrew23 Exp $
**
**  This is part of the QCad Qt GUI
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License (version 2) as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <qwidget.h>
#include <qscrollbar.h>
#include <qpixmap.h>
#include <qlayout.h>

#include "rs_graphicview.h"
#include "rs_layerlistlistener.h"

#include "qg_coordinatewidget.h"
#include "qg_mousewidget.h"
#include "qg_painter.h"
#include "qg_scrollbar.h"

#define QG_SCROLLMARGIN 150

/**
 * This is the vec2web pseudo implementation of a graphic viewer.
 * It only operates in the memory.
 */
class GraphicView: public RS_GraphicView {
public:
    GraphicView(int w, int h, RS_Painter* p);
    virtual ~GraphicView();

    virtual int getWidth();
    virtual int getHeight();
    virtual void redraw() {}
    virtual void adjustOffsetControls() {}
    virtual void adjustZoomControls() {}
    virtual RS_Painter* createPainter();
    virtual RS_Painter* createDirectPainter();
    virtual void destroyPainter();
    virtual void setMouseCursor(RS::CursorType ) {}

    virtual void emulateMouseMoveEvent() {}

    virtual void requestWarningDialog(const RS_String& ) {}
    virtual void requestPreviousMenu() {}
    virtual RS_Layer* requestNewLayerDialog() {
        return NULL;
    }
    virtual RS_Layer* requestLayerRemovalDialog(RS_LayerList* = NULL) {
        return NULL;
    }
    virtual RS_Layer* requestEditLayerDialog(RS_LayerList* ) {
        return NULL;
    }
    virtual RS_String requestFileSaveAsDialog() {
        return "";
    }
    virtual RS_String requestFileOpenDialog() {
        return "";
    }
    virtual void requestDimensionOptions(RS_DimensionData& , bool ) {}
    virtual void requestDimLinearOptions(RS_DimLinearData& , bool ) {}
    virtual void requestArcOptions(RS_ArcData& , bool) {}
    virtual void requestCircleOptions(RS_CircleData&, bool) {}
    virtual void requestSnapDistOptions(double&, bool) {}
    virtual void requestLineParallelOptions(double& , bool ) {}
    virtual void requestLineAngleOptions(double& , bool ) {}
    virtual void requestLineBisectorOptions(double& , bool ) {}
    virtual void requestToolBar(RS::ToolBarId) {}
    virtual void requestToolBarSelect(RS::ActionType ) {}
    virtual RS_Block* requestNewBlockDialog() {
        return NULL;
    }
    virtual RS_Block* requestBlockRemovalDialog(
        RS_BlockList* = NULL) {
        return NULL;
    }
    virtual void requestEditBlockWindow(RS_BlockList* = NULL) {}
    virtual bool requestMoveDialog(RS_MoveData& ) {
        return false;
    }
    virtual bool requestRotateDialog(RS_RotateData& ) {
        return false;
    }
    virtual bool requestScaleDialog(RS_ScaleData& ) {
        return false;
    }
    virtual void requestModifyEntityDialog(RS_Entity* ) {}
    virtual bool requestTextDialog(RS_Text*) {
        return false;
    }

    virtual void updateCoordinateWidget(const RS_Vector& ,
                                        const RS_Vector& ) {}
    virtual void updateMouseWidget(const RS_String& ,
                                   const RS_String& ) {}


    void paint();

private:
    //! Width
    int width;

    //! Height
    int height;
};

#endif
