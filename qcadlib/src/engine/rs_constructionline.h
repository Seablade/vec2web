/****************************************************************************
** $Id: rs_constructionline.h,v 1.5 2004/09/04 19:56:40 andrew Exp $
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


#ifndef RS_CONSTRUCTIONLINE_H
#define RS_CONSTRUCTIONLINE_H

#include "rs_atomicentity.h"
#include "rs_vector.h"

/**
 * Holds the data that defines a construction line (a line
 * which is not limited to both directions).
 */
class RS_ConstructionLineData {
public:
    /**
     * Default constructor. Leaves the data object uninitialized.
     */
    RS_ConstructionLineData() {}

    RS_ConstructionLineData(const RS_Vector& point1,
                            const RS_Vector& point2) {

        this->point1 = point1;
        this->point2 = point2;
    }

    friend class RS_ConstructionLine;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_ConstructionLineData& ld) {

        os << "(" << ld.point1 <<
        "/" << ld.point2 <<
        ")";
        return os;
    }

private:
    RS_Vector point1;
    RS_Vector point2;
};


/**
 * Class for a construction line entity.
 *
 * @author Andrew Mustun
 */
class RS_ConstructionLine : public RS_AtomicEntity {
public:
    RS_ConstructionLine(RS_EntityContainer* parent,
                        const RS_ConstructionLineData& d);

    virtual RS_Entity* clone();

    virtual ~RS_ConstructionLine();

    /**	@return RS2::EntityConstructionLine */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityConstructionLine;
    }
    
	/** 
	 * @todo
	 * @return Start point of the entity. 
	 */
    virtual RS_Vector getStartpoint() const {
        return RS_Vector(false);
    }
    /** 
	 * @todo
	 * @return End point of the entity. 
	 */
    virtual RS_Vector getEndpoint() const {
        return RS_Vector(false);
    }

    /** @return Copy of data that defines the line. */
    RS_ConstructionLineData getData() const {
        return data;
    }

    /** @return First definition point. */
    RS_Vector getPoint1() const {
        return data.point1;
    }
    /** @return Second definition point. */
    RS_Vector getPoint2() const {
        return data.point2;
    }

    virtual RS_Vector getNearestEndpoint(const RS_Vector& coord,
                                         double* dist = NULL);
    virtual RS_Vector getNearestPointOnEntity(const RS_Vector& coord,
            bool onEntity = true, double* dist = NULL, RS_Entity** entity=NULL);
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

    virtual void draw(RS_Painter* /*painter*/, RS_GraphicView* /*view*/, 
		double /*patternOffset*/) {}

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_ConstructionLine& l);

    virtual void calculateBorders();

protected:
    RS_ConstructionLineData data;
};

#endif
