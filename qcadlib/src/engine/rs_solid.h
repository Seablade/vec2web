/****************************************************************************
** $Id: rs_solid.h,v 1.5 2004/09/04 19:56:41 andrew Exp $
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


#ifndef RS_SOLID_H
#define RS_SOLID_H

#include "rs_atomicentity.h"
#include "rs_vector.h"


/**
 * Holds the data that defines a solid.
 */
class RS_SolidData {
public:
    /**
     * Default constructor. Leaves the data object uninitialized.
     */
    RS_SolidData() {
        for (int i=0; i<4; ++i) {
            corner[i] = RS_Vector(false);
        }
    }

    /**
     * Constructor for a solid with 3 corners.
     */
    RS_SolidData(const RS_Vector& corner1,
                 const RS_Vector& corner2,
                 const RS_Vector& corner3) {

        corner[0] = corner1;
        corner[1] = corner2;
        corner[2] = corner3;
        corner[3] = RS_Vector(false);
    }

    /**
     * Constructor for a solid with 4 corners.
     */
    RS_SolidData(const RS_Vector& corner1,
                 const RS_Vector& corner2,
                 const RS_Vector& corner3,
                 const RS_Vector& corner4) {

        corner[0] = corner1;
        corner[1] = corner2;
        corner[2] = corner3;
        corner[3] = corner4;
    }

    friend class RS_Solid;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_SolidData& pd) {
        os << "(";
        for (int i=0; i<4; i++) {
            os << pd.corner[i];
        }
        os << ")";
        return os;
    }

private:
    RS_Vector corner[4];
};



/**
 * Class for a point entity.
 *
 * @author Andrew Mustun
 */
class RS_Solid : public RS_AtomicEntity {
public:
    RS_Solid(RS_EntityContainer* parent,
             const RS_SolidData& d);

    virtual RS_Entity* clone() {
        RS_Solid* s = new RS_Solid(*this);
        s->initId();
        return s;
    }

    /**	@return RS_ENTITY_POINT */
    virtual RS2::EntityType rtti() const {
        return RS2::EntitySolid;
    }
	
    /** 
	 * @return Start point of the entity. 
	 */
    virtual RS_Vector getStartpoint() const {
        return RS_Vector(false);
    }
    /** 
	 * @return End point of the entity. 
	 */
    virtual RS_Vector getEndpoint() const {
        return RS_Vector(false);
    }


    /** @return Copy of data that defines the point. */
    RS_SolidData getData() const {
        return data;
    }

    /** @return true if this is a triangle. */
    bool isTriangle() {
        return !data.corner[3].valid;
    }

    RS_Vector getCorner(int num);

    void shapeArrow(const RS_Vector& point,
                    double angle,
                    double arrowSize);

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

    friend std::ostream& operator << (std::ostream& os, const RS_Solid& p);

    /** Recalculates the borders of this entity. */
    virtual void calculateBorders ();

protected:
    RS_SolidData data;
    //RS_Vector point;
}
;

#endif
