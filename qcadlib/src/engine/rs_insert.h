/****************************************************************************
** $Id: rs_insert.h,v 1.10 2004/07/21 22:44:22 andrew Exp $
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


#ifndef RS_INSERT_H
#define RS_INSERT_H

#include "rs_entitycontainer.h"

#include "rs_block.h"
#include "rs_graphic.h"

/**
 * Holds the data that defines an insert.
 */
class RS_InsertData {
public:
	/**
	 * Default constructor.
	 */
    RS_InsertData() {}

    /**
     * @param name The name of the block used as an identifier.
     * @param insertionPoint Insertion point of the block.
     * @param scaleFactor Scale factor in x / y.
     * @param angle Rotation angle.
     * @param cols Number of cols if we insert a whole array.
     * @param rows Number of rows if we insert a whole array.
     * @param spacing Spacing between rows and cols.
     * @param blockSource Source for the block to insert if other than parent.
     *    Normally blocks are requested from the entity's parent but the
     *    block can also come from another resource. RS_Text uses that
     *    to share the blocks (letters) from a font.
     * @param updateMode RS2::Update will update the insert entity instantly
     *    RS2::NoUpdate will not update the insert. You can update
     *	  it later manually using the update() method. This is 
     *    often the case since you might want to adjust attributes
     *    after creating an insert entity.
     */
    RS_InsertData(const RS_String& name,
                  RS_Vector insertionPoint,
                  RS_Vector scaleFactor,
                  double angle,
                  int cols, int rows, RS_Vector spacing,
                  RS_BlockList* blockSource = NULL,
                  RS2::UpdateMode updateMode = RS2::Update) {
        this->name = name;
        this->insertionPoint = insertionPoint;
        this->scaleFactor = scaleFactor;
        this->angle = angle;
        this->cols = cols;
        this->rows = rows;
        this->spacing = spacing;
        this->blockSource = blockSource;
        this->updateMode = updateMode;

    }

    friend class RS_Insert;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_InsertData& d) {
        os << "(" << d.name.latin1() << ")";
        return os;
    }

    RS_String name;
    RS_Vector insertionPoint;
    RS_Vector scaleFactor;
    double angle;
    int cols, rows;
    RS_Vector spacing;
    RS_BlockList* blockSource;
    RS2::UpdateMode updateMode;
};



/**
 * An insert inserts a block into the drawing at a certain location
 * with certain attributes (angle, scale, ...). 
 * Inserts don't really contain other entities internally. They just
 * refer to a block. However, to the outside world they act exactly 
 * like EntityContainer.
 *
 * @author Andrew Mustun
 */
class RS_Insert : public RS_EntityContainer {
public:
    RS_Insert(RS_EntityContainer* parent,
              const RS_InsertData& d);
    virtual ~RS_Insert();

    virtual RS_Entity* clone() {
        RS_Insert* i = new RS_Insert(*this);
        i->initId();
        i->detach();
        return i;
    }

    /** @return RS2::EntityInsert */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityInsert;
    }

    /** @return Copy of data that defines the insert. **/
    RS_InsertData getData() const {
        return data;
    }

	/**
	 * Reimplementation of reparent. Invalidates block cache pointer.
	 */
    virtual void reparent(RS_EntityContainer* parent) {
		RS_Entity::reparent(parent);
		block = NULL;
    }

    RS_Block* getBlockForInsert();

    virtual void update();

    RS_String getName() const {
        return data.name;
    }

	void setName(const RS_String& newName) {
		data.name = newName;
		update();
	}

    RS_Vector getInsertionPoint() const {
        return data.insertionPoint;
    }
    void setInsertionPoint(const RS_Vector& i) {
        data.insertionPoint = i;
    }

    RS_Vector getScale() const {
        return data.scaleFactor;
    }

	void setScale(const RS_Vector& s) {
		data.scaleFactor = s;
	}

    double getAngle() const {
        return data.angle;
    }
    void setAngle(double a) {
        data.angle = a;
    }

    int getCols() const {
        return data.cols;
    }
	void setCols(int c) {
		data.cols = c;
	}

    int getRows() const {
        return data.rows;
    }
	void setRows(int r) {
		data.rows = r;
	}

    RS_Vector getSpacing() const {
        return data.spacing;
    }
	void setSpacing(const RS_Vector& s) {
		data.spacing = s;
	}
	
    virtual bool isVisible();

    virtual RS_VectorSolutions getRefPoints();
    virtual RS_Vector getNearestRef(const RS_Vector& coord,
                                     double* dist = NULL);

    virtual void move(RS_Vector offset);
    virtual void rotate(RS_Vector center, double angle);
    virtual void scale(RS_Vector center, RS_Vector factor);
    virtual void mirror(RS_Vector axisPoint1, RS_Vector axisPoint2);

    friend std::ostream& operator << (std::ostream& os, const RS_Insert& i);

protected:
    RS_InsertData data;
	RS_Block* block;
};


#endif
