/*****************************************************************************
**  $Id: dxmlpainter.cpp,v 1.4 2003/02/26 12:55:33 xiru Exp $
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
#include "dxmlpainter.h"
#include "rs_math.h"
#include "rs_color.h"


/**
 * Constructor.
 */
DXMLPainter::DXMLPainter(char* dxml) : RS_Painter() {
    this->dxml = fopen(dxml, "w");
    StartDXML();
    width=1;
    colr=colg=colb=0;
}


/**
 * Destructor
 */
DXMLPainter::~DXMLPainter() {
    EndDXML();
    fclose(this->dxml);
}


/**
 * Draws a point at (x,y).
 */
void DXMLPainter::drawPoint(double x, double y) {
    fprintf(dxml, "  <point x=\"%f\" y=\"%f\" />\n", (float)x, (float)y);
}


/**
 * Draws a line from (x1, y1) to (x2, y2).
 */
void DXMLPainter::drawLine(double x1, double y1, double x2, double y2) {
    fprintf(dxml, "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />\n", (float)x1, (float)y1, (float)x2, (float)y2);
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
void DXMLPainter::drawArc(double cx, double cy, double radius,
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
void DXMLPainter::drawArc(double cx, double cy, double radius,
                         double a1, double a2,
                         bool reversed) {
    float ang1, ang2;
    ang1 = (float)( (M_PI * 2 - a1) * ARAD );
    ang2 = (float)( (M_PI * 2 - a2) * ARAD );
    if (reversed) {
        if (ang1 > ang2) {
            ang2 += 360;
        }
        fprintf(dxml, "  <arc x=\"%f\" y=\"%f\" radius=\"%f\" angle1=\"%f\" angle2=\"%f\" />\n",
        (float)cx, (float)cy, (float)radius, ang1, ang2);
    } else {
        if (ang2 > ang1) {
            ang1 += 360;
        }
        fprintf(dxml, "  <arc x=\"%f\" y=\"%f\" radius=\"%f\" angle1=\"%f\" angle2=\"%f\" />\n",
        (float)cx, (float)cy, (float)radius, ang2, ang1);
    }
}


/**
 * Draws a circle.
 * @param cx center in x
 * @param cy center in y
 * @param radius Radius
 */
void DXMLPainter::drawCircle(double cx, double cy, double radius) {
    fprintf(dxml, "  <circle x=\"%f\" y=\"%f\" radius=\"%f\" />\n", (float)cx, (float)cy, (float)radius);
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
void DXMLPainter::drawEllipse(double cx, double cy,
                             double radius1, double radius2,
                             double angle,
                             double a1, double a2,
                             bool reversed) {
    float ang1, ang2;
    ang1 = (float)( (M_PI * 2 - a1) * ARAD + 90 );
    ang2 = (float)( (M_PI * 2 - a2) * ARAD + 90 );
    if (reversed) {
        if (ang1 > ang2) {
            ang2 += 360;
        }
        fprintf(dxml, "  <ellipse x=\"%f\" y=\"%f\" radius1=\"%f\" radius2=\"%f\" angle1=\"%f\" angle2=\"%f\" angle3=\"%f\" />\n",
        (float)cx, (float)cy, (float)radius1, (float)radius2, (float)angle, ang1, ang2);
    } else {
        if (ang2 > ang1) {
            ang1 += 360;
        }
        fprintf(dxml, "  <ellipse x=\"%f\" y=\"%f\" radius1=\"%f\" radius2=\"%f\" angle1=\"%f\" angle2=\"%f\" angle3=\"%f\" />\n",
        (float)cx, (float)cy, (float)radius1, (float)radius2, (float)angle, ang2, ang1);
    }
}


RS_Pen DXMLPainter::getPen() {
    return RS_Pen(RS_Color(colr,colg,colb), RS::Width01, RS::SolidLine);
}


void DXMLPainter::setPen(const RS_Pen& pen) {
    width = RS::qw(pen.getWidth());
    colr = pen.getColor().red();
    colg = pen.getColor().green();
    colb = pen.getColor().blue();
}


void DXMLPainter::setPen(const RS_Color& color) {
    colr = color.red();
    colg = color.green();
    colb = color.blue();
}


void DXMLPainter::setPen(int r, int g, int b) {
    colr = r;
    colg = g;
    colb = b;
}


void DXMLPainter::StartDXML() {
    fprintf(dxml, "<draw>\n");
}


void DXMLPainter::EndDXML() {
    fprintf(dxml, "</draw>\n");
}
