/****************************************************************************
** $Id: rs_dimradial.h,v 1.4 2004/01/12 21:40:12 andrew Exp $
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


#ifndef RS_DIMRADIAL_H
#define RS_DIMRADIAL_H

#include "rs_dimension.h"

/**
 * Holds the data that defines a radial dimension entity.
 */
class RS_DimRadialData {
public:
    /**
     * Default constructor. Leaves the data object uninitialized.
     */
    RS_DimRadialData() {}

    /**
     * Constructor with initialisation.
     *
     * @param definitionPoint Definition point of the radial dimension. 
     * @param leader Leader length.
     */
    RS_DimRadialData(const RS_Vector& definitionPoint,
                     double leader) {
        this->definitionPoint = definitionPoint;
        this->leader = leader;
    }

    friend class RS_DimRadial;
    //friend class RS_ActionDimRadial;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_DimRadialData& dd) {
        os << "(" << dd.definitionPoint << "/" << dd.leader << ")";
        return os;
    }

public:
    /** Definition point. */
    RS_Vector definitionPoint;
    /** Leader length. */
    double leader;
};



/**
 * Class for radial dimension entities.
 *
 * @author Andrew Mustun
 */
class RS_DimRadial : public RS_Dimension {
public:
    RS_DimRadial(RS_EntityContainer* parent,
                 const RS_DimensionData& d,
                 const RS_DimRadialData& ed);
    virtual ~RS_DimRadial() {}

    virtual RS_Entity* clone() {
        RS_DimRadial* d = new RS_DimRadial(*this);
        d->initId();
        d->detach();
        return d;
    }

    /**	@return RS2::EntityDimRadial */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityDimRadial;
    }

    /**
     * @return Copy of data that defines the radial dimension. 
     * @see getData()
     */
    RS_DimRadialData getEData() const {
        return edata;
    }
	
    virtual RS_VectorSolutions getRefPoints();

    virtual RS_String getMeasuredLabel();

    virtual void update(bool autoText=false);

    RS_Vector getDefinitionPoint() {
        return edata.definitionPoint;
    }
    double getLeader() {
        return edata.leader;
    }

    virtual void move(RS_Vector offset);
    virtual void rotate(RS_Vector center, double angle);
    virtual void scale(RS_Vector center, RS_Vector factor);
    virtual void mirror(RS_Vector axisPoint1, RS_Vector axisPoint2);
	virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_DimRadial& d);

protected:
    /** Extended data. */
    RS_DimRadialData edata;
};

#endif
