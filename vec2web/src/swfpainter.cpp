/*****************************************************************************
**  $Id: swfpainter.cpp,v 1.2 2003/10/03 18:55:41 andrew Exp $
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


#ifdef SWF_SUPPORT

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
void SWFPainter::drawPoint(const RS_Vector& p) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width, colr, colg, colb);
    shape->movePenTo((float)p.x-1, (float)p.y);
    shape->drawLineTo((float)p.x+1, (float)p.y);
    shape->movePenTo((float)p.x, (float)p.y-1);
    shape->drawLineTo((float)p.x, (float)p.y+1);
    movie->add(shape);
}


/**
 * Draws a line from (x1, y1) to (x2, y2).
 */
void SWFPainter::drawLine(const RS_Vector& p1, const RS_Vector& p2) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);
    shape->movePenTo((float)p1.x, (float)p1.y);
    shape->drawLineTo((float)p2.x, (float)p2.y);
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
void SWFPainter::drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         const RS_Vector& /*p1*/,
                         const RS_Vector& /*p2*/,
                         bool reversed) {
    drawArc(cp, radius, a1, a2, reversed);
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
void SWFPainter::drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         bool reversed) {
    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);
    shape->movePenTo((float)cp.x, (float)cp.y);
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
 * Draws an ellipse.
 * @param cx center in x
 * @param cy center in y
 * @param radius1 Radius 1
 * @param radius2 Radius 2
 * @param angle Angle in rad
 * @param a1 Angle 1 in rad
 * @param a2 Angle 2 in rad
 * @param reversed true: clockwise, false: counterclockwise
 */
void SWFPainter::drawEllipse(const RS_Vector& cp,
                             double radius1, double radius2,
                             double angle,
                             double a1, double a2,
                             bool reversed) {

    SWFShape *shape = new SWFShape();
    shape->setLine(width,colr,colg,colb);

    double aStep;            // Angle Step (rad)
    double a;                // Current Angle (rad)

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
    //RS_Vector vc(cx, cy);
    RS_Vector vc = cp;
    vp.set(cp.x+cos(a1)*radius1,
           cp.y-sin(a1)*radius2);
    vp.rotate(vc, -angle);
    shape->movePenTo((float)RS_Math::round(vp.x),
                     (float)RS_Math::round(vp.y));
    if(!reversed) {
        // Arc Counterclockwise:
        if(a1>a2-1.0e-6) {
            a2+=2*M_PI;
        }
        for(a=a1+aStep; a<=a2; a+=aStep) {
            vp.set(cp.x+cos(a)*radius1,
                   cp.y-sin(a)*radius2);
            vp.rotate(vc, -angle);
            shape->drawLineTo((float)RS_Math::round(vp.x),
                              (float)RS_Math::round(vp.y));
        }
    } else {
        // Arc Clockwise:
        if(a1<a2+1.0e-6) {
            a-=2*M_PI;
        }
        for(a=a1-aStep; a>=a2; a-=aStep) {
            vp.set(cp.x+cos(a)*radius1,
                   cp.y-sin(a)*radius2);
            vp.rotate(vc, -angle);
            shape->drawLineTo((float)RS_Math::round(vp.x),
                              (float)RS_Math::round(vp.y));
        }
    }
    vp.set(cp.x+cos(a2)*radius1,
           cp.y-sin(a2)*radius2);
    vp.rotate(vc, -angle);
    shape->drawLineTo((float)RS_Math::round(vp.x),
                      (float)RS_Math::round(vp.y));

    movie->add(shape);

}


RS_Pen SWFPainter::getPen() {
    return RS_Pen(RS_Color(colr,colg,colb), RS2::Width01, RS2::SolidLine);
}


void SWFPainter::setPen(const RS_Pen& pen) {
    float w;
    w = RS2::qw(pen.getWidth());
    w = w / 21.1;
    if ( w < 1 ) {
        w = 1;
    }
    if ( w > 10 ) {
        w = 10;
    }
    width = (int)w;
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

#endif
