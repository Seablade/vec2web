/*****************************************************************************
**  $Id: rs_staticgraphicview.cpp,v 1.1 2003/08/25 22:50:31 andrew Exp $
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

#include "rs_staticgraphicview.h"

#include "rs_graphic.h"


/**
 * Constructor.
 *
 * @param w Width
 * @param h Height
 */
RS_StaticGraphicView::RS_StaticGraphicView(int w, int h, RS_Painter* p) {
    setBackground(RS_Color(255,255,255));
    width = w;
    height = h;
    painter = p;
    setBorders(5, 5, 5, 5);
}


/**
 * Destructor
 */
RS_StaticGraphicView::~RS_StaticGraphicView() {}


/**
 * @return width of widget.
 */
int RS_StaticGraphicView::getWidth() {
    return width;
}


/**
 * @return height of widget.
 */
int RS_StaticGraphicView::getHeight() {
    return height;
}


/**
 * Creates a new painter for the buffer of this widget and returns a 
 * pointer to it. The class variable 'painter' also
 * points to that object.
 */
RS_Painter* RS_StaticGraphicView::createPainter() {
    return painter;
}


/**
 * Creates a new painter for this widget and returns a 
 * pointer to it. The class variable 'painter' also
 * points to that object.
 */
RS_Painter* RS_StaticGraphicView::createDirectPainter() {
    return createPainter();
}


/**
 * Deletes the painter.
 */
void RS_StaticGraphicView::destroyPainter() {}



/**
 * Handles paint events by redrawing the graphic in this view.
 */
void RS_StaticGraphicView::paint() {
    RS_DEBUG->print("RS_StaticGraphicView::paint begin");
    drawIt();
    RS_DEBUG->print("RS_StaticGraphicView::paint end");
}

