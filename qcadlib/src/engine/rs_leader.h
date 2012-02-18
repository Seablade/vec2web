/****************************************************************************
** $Id: rs_leader.h,v 1.7 2004/09/11 20:05:47 andrew Exp $
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


#ifndef RS_LEADER_H
#define RS_LEADER_H

#include "rs_entity.h"
#include "rs_entitycontainer.h"



/**
 * Holds the data that defines a leader.
 */
class RS_LeaderData {
public:
    RS_LeaderData() {}
    RS_LeaderData(bool arrowHeadFlag) {
        arrowHead = arrowHeadFlag;
    }

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_LeaderData& /*ld*/) {
        os << "(Leader)";
        return os;
    }

	/** true: leader has an arrow head. false: no arrow. */
	bool arrowHead;
};



/**
 * Class for a leader entity (kind of a polyline arrow).
 *
 * @author Andrew Mustun
 */
class RS_Leader : public RS_EntityContainer {
public:
    RS_Leader(RS_EntityContainer* parent=NULL);
    RS_Leader(RS_EntityContainer* parent,
                const RS_LeaderData& d);
    virtual ~RS_Leader();

    virtual RS_Entity* clone() {
        RS_Leader* p = new RS_Leader(*this);
        p->initId();
        p->detach();
        return p;
    }

    /**	@return RS2::EntityDimLeader */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityDimLeader;
    }

	virtual void update();

    /** @return Copy of data that defines the leader. */
    RS_LeaderData getData() const {
        return data;
    }

	/** @return true: if this leader has an arrow at the beginning. */
	bool hasArrowHead() {
		return data.arrowHead;
	}

    virtual RS_Entity* addVertex(const RS_Vector& v);
    virtual void addEntity(RS_Entity* entity);

	virtual double getLength() {
		return -1.0;
	}
	
    virtual void move(RS_Vector offset);
    virtual void rotate(RS_Vector center, double angle);
    virtual void scale(RS_Vector center, RS_Vector factor);
    virtual void mirror(RS_Vector axisPoint1, RS_Vector axisPoint2);
    virtual void stretch(RS_Vector firstCorner,
                         RS_Vector secondCorner,
                         RS_Vector offset);

    friend std::ostream& operator << (std::ostream& os, const RS_Leader& l);

protected:
    RS_LeaderData data;
	bool empty;
};

#endif
