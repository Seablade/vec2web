/*****************************************************************************
**  $Id: swfpainter.cpp,v 1.5 2003/02/13 23:03:57 xiru Exp $
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

#include <stdio.h>
#include "swfpainter.h"
#include "rs_math.h"
#include "rs_color.h"


/**
 * Constructor.
 */
SWFPainter::SWFPainter(SWFMovie* mov) : RS_Painter() {
    this->movie = mov;
    width=1;
    colr=colg=colb=0;
}


/**
 * Destructor
 */
SWFPainter::~SWFPainter() {}


/**
 * Draws a point at (x,y).
 */
void SWFPainter::drawPoint(double x, double y) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width, colr, colg, colb);
    shape->movePenTo((float)x-1, (float)y);
    shape->drawLineTo((float)x+1, (float)y);
    shape->movePenTo((float)x, (float)y-1);
    shape->drawLineTo((float)x, (float)y+1);
    movie->add(shape);
}


/**
 * Draws a line from (x1, y1) to (x2, y2).
 */
void SWFPainter::drawLine(double x1, double y1, double x2, double y2) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);
    shape->movePenTo((float)x1, (float)y1);
    shape->drawLineTo((float)x2, (float)y2);
    movie->add(shape);
}


/**
 * Draws an arc.
 * @param cx center in x
 * @param cy center in y
 * @param radius Radius
 * @param a1 Angle 1 in rad
 * @param a2 Angle 2 in rad
 * @param x1 startpoint x
 * @param y1 startpoint y
 * @param x2 endpoint x
 * @param y2 endpoint y
 * @param reversed true: clockwise, false: counterclockwise
 */
void SWFPainter::drawArc(double cx, double cy, double radius,
                         double a1, double a2,
                         double x1, double y1, double x2, double y2,
                         bool reversed) {
    drawArc(cx, cy, radius, a1, a2, reversed);
}

/**
 * Draws an arc.
 * @param cx center in x
 * @param cy center in y
 * @param radius Radius
 * @param a1 Angle 1 in rad
 * @param a2 Angle 2 in rad
 * @param reversed true: clockwise, false: counterclockwise
 */
void SWFPainter::drawArc(double cx, double cy, double radius,
                         double a1, double a2,
                         bool reversed) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);
    shape->movePenTo((float)cx, (float)cy);
    float ang1, ang2;
    ang1 = (float)( (M_PI * 2 - a1) * ARAD + 90 );
    ang2 = (float)( (M_PI * 2 - a2) * ARAD + 90 );
    if (reversed) {
        if (ang1 > ang2) {
            ang2 += 360;
        }
        shape->drawArc((float)radius, ang1, ang2);
    } else {
        if (ang2 > ang1) {
            ang1 += 360;
        }
        shape->drawArc((float)radius, ang2, ang1);
    }
    movie->add(shape);
}


/**
 * Draws a circle.
 * @param cx center in x
 * @param cy center in y
 * @param radius Radius
 */
void SWFPainter::drawCircle(double cx, double cy, double radius) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);
    shape->movePenTo((float)cx, (float)cy);
    shape->drawCircle((float)radius);
    movie->add(shape);
}


RS_Pen SWFPainter::getPen() {
    return RS_Pen(RS_Color(colr,colg,colb), RS::Width01, RS::SolidLine);
}


void SWFPainter::setPen(const RS_Pen& pen) {
    width = RS::qw(pen.getWidth());
    colr = pen.getColor().red();
    colg = pen.getColor().green();
    colb = pen.getColor().blue();
}


void SWFPainter::setPen(const RS_Color& color) {
    colr = color.red();
    colg = color.green();
    colb = color.blue();
}


void SWFPainter::setPen(int r, int g, int b) {
    colr = r;
    colg = g;
    colb = b;
}
