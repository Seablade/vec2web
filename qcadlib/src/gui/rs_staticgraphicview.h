/*****************************************************************************
**  $Id: rs_staticgraphicview.h,v 1.1 2003/08/25 22:50:31 andrew Exp $
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

#ifndef RS_STATICGRAPHICVIEW_H
#define RS_STATICGRAPHICVIEW_H

#include "rs_graphicview.h"
#include "rs_layerlistlistener.h"

/**
 * This is an implementation of a graphic viewer with a fixed size
 * for drawing onto fixed devices (such as bitmaps).
 */
class RS_StaticGraphicView: public RS_GraphicView {
public:
    RS_StaticGraphicView(int w, int h, RS_Painter* p);
    virtual ~RS_StaticGraphicView();

    virtual int getWidth();
    virtual int getHeight();
    virtual void redraw() {}
    virtual void adjustOffsetControls() {}
    virtual void adjustZoomControls() {}
    virtual RS_Painter* createPainter();
    virtual RS_Painter* createDirectPainter();
    virtual void destroyPainter();
    virtual void setMouseCursor(RS2::CursorType ) {}

    virtual void emulateMouseMoveEvent() {}
	virtual void updateGridStatusWidget(const RS_String& ) {}

    void paint();

private:
    //! Width
    int width;

    //! Height
    int height;
};

#endif
