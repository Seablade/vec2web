/*****************************************************************************
**  $Id: swfpainter.cpp,v 1.2 2003/02/13 20:54:32 xiru Exp $
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
SWFPainter::SWFPainter(SWFMovie* mov)
        : RS_Painter() {
	
	this->movie = mov;
	width=1;
	colr=colg=colb=0;
}


/**
 * Destructor
 */
SWFPainter::~SWFPainter() {}

/**
 * Draws a grid point at (x1, y1).
 */
//void SWFPainter::drawGridPoint(int x1, int y1) {
//}

/**
 * Draws a point at (x1, y1).
 */
void SWFPainter::drawPoint(double x, double y) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width, colr,colg,colb);
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
    shape->setLine(width, colr,colg,colb);
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
	shape->setLine(width, colr,colg,colb);
	shape->movePenTo((float)cx, (float)cy);
	float ang1, ang2;
	ang1 = (float)( (M_PI * 2 - a1) * ARAD + 90 );
	ang2 = (float)( (M_PI * 2 - a2) * ARAD + 90 );
	if (reversed) {
		if (ang1 > ang2) {
			ang2 += 360;
		}
		shape->drawArc((float)radius, ang1, ang2);
	}
	else {
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
    shape->setLine(width, colr,colg,colb);
    shape->movePenTo(cx, cy);
    shape->drawCircle(radius);
    movie->add(shape);
}


/**
 * Draws a rotated ellipse arc.
 */
/*
void SWFPainter::drawEllipse(double cx, double cy,
                             double radius1, double radius2,
                             double angle,
                             double a1, double a2,
                             bool reversed) {

    //if(radius1<=0.5 && radius2<=0.5) {
    //    drawGridPoint((int)cx, (int)cy);
    //} else {
        int   cix;            // Next point on arc
        int   ciy;            //
        double aStep;         // Angle Step (rad)
        double a;             // Current Angle (rad)

        // Angle step in rad
        if (radius1<radius2) {
            if (radius1<1.0e-4) {
                aStep=1.0;
            } else {
                aStep=asin(2.0/radius1);
            }
        } else {
            if (radius2<1.0e-4) {
                aStep=1.0;
            } else {
                aStep=asin(2.0/radius2);
            }
        }

        if(aStep<0.05) {
            aStep = 0.05;
        }

		aStep=0.01;

        RS_Vector vp;
        RS_Vector vc(cx, cy);
        vp.set(cx+cos(a1)*radius1,
               cy-sin(a1)*radius2);
        vp.rotate(vc, -angle);
        moveTo(RS_Math::round(vp.x),
               RS_Math::round(vp.y));
        if(!reversed) {
            // Arc Counterclockwise:
            if(a1>a2-1.0e-6) {
                a2+=2*M_PI;
            }
            for(a=a1+aStep; a<=a2; a+=aStep) {
                vp.set(cx+cos(a)*radius1,
                       cy-sin(a)*radius2);
                vp.rotate(vc, -angle);
                lineTo(RS_Math::round(vp.x),
                       RS_Math::round(vp.y));
            }
        } else {
            // Arc Clockwise:
            if(a1<a2+1.0e-6) {
                a-=2*M_PI;
            }
            for(a=a1-aStep; a>=a2; a-=aStep) {
                vp.set(cx+cos(a)*radius1,
                       cy-sin(a)*radius2);
                vp.rotate(vc, -angle);
                lineTo(RS_Math::round(vp.x),
                       RS_Math::round(vp.y));
            }
        }
        vp.set(cx+cos(a2)*radius1,
               cy-sin(a2)*radius2);
        vp.rotate(vc, -angle);
        lineTo(RS_Math::round(vp.x),
               RS_Math::round(vp.y));
   //}
}
*/



/*
void SWFPainter::drawTextH(int x1, int y1,
                           int x2, int y2,
                           const QString& text) {
    drawText(x1, y1, x2, y2,
             Qt::AlignLeft|Qt::AlignVCenter,
             text);
}



void SWFPainter::drawTextV(int x1, int y1,
                           int x2, int y2,
                           const QString& text) {
    save();
    QWMatrix wm = worldMatrix();
    wm.rotate(-90.0);
    setWorldMatrix(wm);
    //rotate(-90.0);

    drawText(x1, y1, x2, y2,
             Qt::AlignRight|Qt::AlignVCenter,
             text);

    restore();
}

void SWFPainter::fillRect(int x1, int y1, int w, int h,
                          const RS_Color& col) {
    QPainter::fillRect(x1, y1, w, h, col);
}


void SWFPainter::fillTriangle(int x1, int y1,
                              int x2, int y2,
                              int x3, int y3) {

	QPointArray arr(3);
	arr.putPoints(0, 3, x1,y1, x2,y2, x3,y3);
	setBrush(pen().color());
	drawPolygon(arr);
}
*/

/*
void SWFPainter::setBackgroundPen() {
    setPen(QColor(255,255,255));
}
*/
/*
void SWFPainter::setDefaultPen() {
    setPen(QColor(0,0,0));
}
*/

/*
void SWFPainter::setPreviewPen() {
    setPen(QColor(0,255,255));
}
*/

/*
RS_Pen SWFPainter::getPen() {
    RS_Pen p(pen().color(),
             RS::qw(pen().width()),
             RS::qw(pen().style()));
    //return QPainter::pen();
    return p;
}
*/
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
/*
//void SWFPainter::setColor(const QColor& color) {
//	setPen(color);
//}

void SWFPainter::setXORMode() {
    setRasterOp(XorROP);
}

void SWFPainter::setNormalMode() {
    setRasterOp(CopyROP);
}

void SWFPainter::setClipRect(int x, int y, int w, int h) {
    QPainter::setClipRect(x, y, w, h);
    setClipping(true);
}

void SWFPainter::resetClipping() {
    setClipping(false);
}
*/


