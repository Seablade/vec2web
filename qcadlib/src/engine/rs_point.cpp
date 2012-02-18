/****************************************************************************
** $Id: rs_point.cpp,v 1.7 2004/09/04 19:56:41 andrew Exp $
**
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
** This file is part of the qcadlib Library project.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid qcadlib Professional Edition licenses may use 
** this file in accordance with the qcadlib Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.ribbonsoft.com for further details.
**
** Contact info@ribbonsoft.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/


#include "rs_point.h"

#include "rs_graphicview.h"
#include "rs_painter.h"


/**
 * Default constructor.
 */
RS_Point::RS_Point(RS_EntityContainer* parent,
                   const RS_PointData& d)
        :RS_AtomicEntity(parent), data(d) {
    calculateBorders ();
}



void RS_Point::calculateBorders () {
    minV = maxV = data.pos;
}



RS_VectorSolutions RS_Point::getRefPoints() {
	RS_VectorSolutions ret(data.pos);
	return ret;
}



RS_Vector RS_Point::getNearestEndpoint(const RS_Vector& coord, double* dist) {

    if (dist!=NULL) {
        *dist = data.pos.distanceTo(coord);
    }

    return data.pos;
}



RS_Vector RS_Point::getNearestPointOnEntity(const RS_Vector& coord,
        bool /*onEntity*/, double* dist, RS_Entity** entity) {
    if (dist!=NULL) {
        *dist = data.pos.distanceTo(coord);
    }
    if (entity!=NULL) {
        *entity = this;
    }
    return data.pos;
}



RS_Vector RS_Point::getNearestCenter(const RS_Vector& coord, double* dist) {

    if (dist!=NULL) {
        *dist = data.pos.distanceTo(coord);
    }

    return data.pos;
}



RS_Vector RS_Point::getNearestMiddle(const RS_Vector& coord,
                                     double* dist) {
    if (dist!=NULL) {
        *dist = data.pos.distanceTo(coord);
    }

    return data.pos;
}



RS_Vector RS_Point::getNearestDist(double /*distance*/,
                                   const RS_Vector& /*coord*/,
                                   double* dist) {
    if (dist!=NULL) {
        *dist = RS_MAXDOUBLE;
    }
    return RS_Vector(false);
}



double RS_Point::getDistanceToPoint(const RS_Vector& coord,
                                    RS_Entity** entity,
                                    RS2::ResolveLevel /*level*/,
									double /*solidDist*/) {
    if (entity!=NULL) {
        *entity = this;
    }
    return data.pos.distanceTo(coord);
}



void RS_Point::moveStartpoint(const RS_Vector& pos) {
	data.pos = pos;
	calculateBorders();
}



void RS_Point::move(RS_Vector offset) {
    data.pos.move(offset);
    calculateBorders();
}



void RS_Point::rotate(RS_Vector center, double angle) {
    data.pos.rotate(center, angle);
    calculateBorders();
}



void RS_Point::scale(RS_Vector center, RS_Vector factor) {
    data.pos.scale(center, factor);
    calculateBorders();
}



void RS_Point::mirror(RS_Vector axisPoint1, RS_Vector axisPoint2) {
    data.pos.mirror(axisPoint1, axisPoint2);
    calculateBorders();
}


void RS_Point::draw(RS_Painter* painter, RS_GraphicView* view, double /*patternOffset*/) {
    if (painter==NULL || view==NULL) {
        return;
    }

    painter->drawPoint(view->toGui(getPos()));
}



/**
 * Dumps the point's data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_Point& p) {
    os << " Point: " << p.getData() << "\n";
    return os;
}


// EOF
