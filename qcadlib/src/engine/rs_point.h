/****************************************************************************
** $Id: rs_point.h,v 1.7 2004/12/09 23:09:52 andrew Exp $
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


#ifndef RS_POINT_H
#define RS_POINT_H

#include "rs_atomicentity.h"



/**
 * Holds the data that defines a point.
 */
class RS_PointData {
public:
    RS_PointData(const RS_Vector& pos) {
        this->pos = pos;
    }

    friend std::ostream& operator << (std::ostream& os, const RS_PointData& pd) {
        os << "(" << pd.pos << ")";
        return os;
    }

    RS_Vector pos;
};



/**
 * Class for a point entity.
 *
 * @author Andrew Mustun
 */
class RS_Point : public RS_AtomicEntity {
public:
    RS_Point(RS_EntityContainer* parent,
             const RS_PointData& d);

    virtual RS_Entity* clone() {
        RS_Point* p = new RS_Point(*this);
        p->initId();
        return p;
    }

    /**	@return RS_ENTITY_POINT */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityPoint;
    }
	
    /** 
	 * @return Start point of the entity. 
	 */
    virtual RS_Vector getStartpoint() const {
        return data.pos;
    }
    /** 
	 * @return End point of the entity. 
	 */
    virtual RS_Vector getEndpoint() const {
        return data.pos;
    }

	virtual void moveStartpoint(const RS_Vector& pos);

    /** @return Copy of data that defines the point. */
    RS_PointData getData() const {
        return data;
    }

    virtual RS_VectorSolutions getRefPoints();

    /** @return Position of the point */
    RS_Vector getPos() {
        return data.pos;
    }

    /** Sets a new position for this point. */
    void setPos(const RS_Vector& pos) {
        data.pos = pos;
    }

    virtual RS_Vector getNearestEndpoint(const RS_Vector& coord,
                                         double* dist = NULL);
    virtual RS_Vector getNearestPointOnEntity(const RS_Vector& coord,
            bool onEntity = true, double* dist = NULL, RS_Entity** entity = NULL);
    virtual RS_Vector getNearestCenter(const RS_Vector& coord,
                                       double* dist = NULL);
    virtual RS_Vector getNearestMiddle(const RS_Vector& coord,
                                       double* dist = NULL);
    virtual RS_Vector getNearestDist(double distance,
                                     const RS_Vector& coord,
                                     double* dist = NULL);
    virtual double getDistanceToPoint(const RS_Vector& coord,
                                      RS_Entity** entity=NULL,
                                      RS2::ResolveLevel level=RS2::ResolveNone,
									  double solidDist = RS_MAXDOUBLE);

    virtual void move(RS_Vector offset);
    virtual void rotate(RS_Vector center, double angle);
    virtual void scale(RS_Vector center, RS_Vector factor);
    virtual void mirror(RS_Vector axisPoint1, RS_Vector axisPoint2);

    virtual void draw(RS_Painter* painter, RS_GraphicView* view, double patternOffset=0.0);

    friend std::ostream& operator << (std::ostream& os, const RS_Point& p);

    /** Recalculates the borders of this entity. */
    virtual void calculateBorders ();

protected:
    RS_PointData data;
    //RS_Vector point;
}
;

#endif
