/****************************************************************************
** $Id: rs_atomicentity.h,v 1.8 2004/12/09 01:11:15 andrew Exp $
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


#ifndef RS_ATOMICENTITY_H
#define RS_ATOMICENTITY_H

#include "rs_entity.h"


/**
 * Class representing a tree of entities.
 * Typical entity containers are graphics, polylines, groups, texts, ...)
 *
 * @author Andrew Mustun
 */
class RS_AtomicEntity : public RS_Entity {

public:
    /**
     * Construtor.
     */
    RS_AtomicEntity(RS_EntityContainer* parent=NULL) : RS_Entity(parent) {}
    /**
     * Destrutor.
     */
    virtual ~RS_AtomicEntity() {}

    /**
     * @return false because entities made from subclasses are 
     *  atomic entities.
     */
    virtual bool isContainer() const {
        return false;
    }

    /**
     * @return true because entities made from subclasses are 
     *  atomic entities.
     */
    virtual bool isAtomic() const {
        return true;
    }

    /**
     * @return Always 1 for atomic entities.
     */
    virtual unsigned long int count() {
        return 1;
    }
	
    /**
     * @return Always 1 for atomic entities.
     */
    virtual unsigned long int countDeep() {
        return 1;
    }

    /**
     * Implementation must return the endpoint of the entity or
     * an invalid vector if the entity has no endpoint.
     */
    virtual RS_Vector getEndpoint() const {
        return RS_Vector(false);
    }

    /**
     * Implementation must return the startpoint of the entity or
     * an invalid vector if the entity has no startpoint.
     */
    virtual RS_Vector getStartpoint() const {
        return RS_Vector(false);
    }
	
	/**
	 * Implementation must return the angle in which direction the entity starts.
	 */
	virtual double getDirection1() const {
		return 0.0;
	}
	
	/**
	 * Implementation must return the angle in which direction the entity starts the opposite way.
	 */
	virtual double getDirection2() const {
		return 0.0;
	}

    /**
     * (De-)selects startpoint.
     */
    virtual void setStartpointSelected(bool select) {
        if (select) {
            setFlag(RS2::FlagSelected1);
        } else {
            delFlag(RS2::FlagSelected1);
        }
    }

    /**
     * (De-)selects endpoint.
     */
    virtual void setEndpointSelected(bool select) {
        if (select) {
            setFlag(RS2::FlagSelected2);
        } else {
            delFlag(RS2::FlagSelected2);
        }
    }

    /**
     * @return True if the entities startpoint is selected. 
     */
    bool isStartpointSelected() const {
        return getFlag(RS2::FlagSelected1);
    }

    /**
     * @return True if the entities endpoint is selected. 
     */
    bool isEndpointSelected() const {
        return getFlag(RS2::FlagSelected2);
    }

    /**
     * Implementation must move the startpoint of the entity to
     * the given position.
     */
    virtual void moveStartpoint(const RS_Vector& /*pos*/) {}

    /**
     * Implementation must move the endpoint of the entity to
     * the given position.
     */
    virtual void moveEndpoint(const RS_Vector& /*pos*/) {}
    
	/**
     * Implementation must trim the startpoint of the entity to
     * the given position.
     */
    virtual void trimStartpoint(const RS_Vector& pos) {
		moveStartpoint(pos);
	}

    /**
     * Implementation must trim the endpoint of the entity to
     * the given position.
     */
    virtual void trimEndpoint(const RS_Vector& pos) {
		moveEndpoint(pos);
	}
	
    /**
     * Implementation must return which ending of the entity will
     * be trimmed if 'coord' is the coordinate chosen to indicate the
     * trim entity and 'trimPoint' is the point to which the entity will
     * be trimmed.
     */
    virtual RS2::Ending getTrimPoint(const RS_Vector& /*coord*/,
                                     const RS_Vector& /*trimPoint*/) {
        return RS2::EndingNone;
    }

    virtual void reverse() { }

	virtual void moveSelectedRef(const RS_Vector& ref, const RS_Vector& offset) {
	    if (isSelected()) {
			moveRef(ref, offset);
	    }
	}
}
;


#endif
