/****************************************************************************
** $Id: rs_block.h,v 1.9 2004/04/09 19:56:41 andrew Exp $
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


#ifndef RS_BLOCK_H
#define RS_BLOCK_H

//#include "rs_blocklist.h"
#include "rs_document.h"

/**
 * Holds the data that defines a block.
 */
class RS_BlockData {
public:
    RS_BlockData() {}

    RS_BlockData(const RS_String& name,
	           const RS_Vector& basePoint,
			   bool frozen) {

		this->name = name;
		this->basePoint = basePoint;
		this->frozen = frozen;
    }

	bool isValid() {
		return (!name.isEmpty() && basePoint.valid);
	}

public:
    /**
     * Block name. Acts as an id.
     */
	RS_String name;
	/*
     * Base point of the Block. Usually 0/0 since blocks can be moved around 
     * using the insertion point of Insert entities.
	 */
    RS_Vector basePoint;

	//! Frozen flag
	bool frozen;
};



/**
 * A block is a group of entities. A block unlike an other entity
 * container has a base point which defines the offset of the
 * block. Note that although technically possible, a block should
 * never be part of the entity tree of a graphic. Blocks are 
 * stored in a seperate list inside the graphic document (a block list).
 * The graphic can contain RS_Insert entities that refer to such 
 * blocks.
 *
 * blocks are documents and can therefore be handled by graphic views.
 *
 * @author Andrew Mustun
 */
class RS_Block : public RS_Document {

	friend class RS_BlockList;

public:
    /**
     * @param parent The graphic this block belongs to.
     * @param blockData defining data of the block.
     */
    RS_Block(RS_EntityContainer* parent, const RS_BlockData& d);

    virtual ~RS_Block();
	
    virtual RS_Entity* clone();

    /** @return RS2::EntityBlock */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityBlock;
    }

    /**
     * @return Name of this block (the name is an Id for this block).
     */
    RS_String getName() const {
        return data.name;
    }

    /**
     * @return base point of this block.
     */
    RS_Vector getBasePoint() const {
        return data.basePoint;
    }

    virtual RS_LayerList* getLayerList();
    virtual RS_BlockList* getBlockList();

    /**
     * Reimplementation from RS_Document. Does nothing.
     */
    virtual void newDoc() {
        // do nothing
    }

    /**
     * Reimplementation from RS_Document. Saves the parent graphic document.
     */
    virtual bool save();

    /**
     * Reimplementation from RS_Document. Does nothing.
     */
    virtual bool saveAs(const RS_String& filename, RS2::FormatType type);

    /**
     * Reimplementation from RS_Document. Does nothing.
     */
    virtual bool open(const RS_String& , RS2::FormatType) {
        // do nothing
        return false;
    }

    friend std::ostream& operator << (std::ostream& os, const RS_Block& b) {
        os << " name: " << b.getName().latin1() << "\n";
        os << " entities: " << (RS_EntityContainer&)b << "\n";
        return os;
    }

    /** 
	 * sets a new name for the block. Only called by blocklist to
	 * assure that block names stay unique.
	 */
    void setName(const RS_String& n) {
        data.name = n;
    }
    
	/**
     * @retval true if this block is frozen (invisible)
     * @retval false if this block isn't frozen (visible)
     */
    bool isFrozen() const {
        return data.frozen;
    }

    /**
     * Toggles the visibility of this block.
     * Freezes the block if it's not frozen, thaws the block otherwise
     */
    void toggle() {
		data.frozen = !data.frozen;
    }

    /**
     * (De-)freezes this block.
     *
     * @param freeze true: freeze, false: defreeze
     */
    void freeze(bool freeze) {
		data.frozen = freeze;
    }
	
	virtual void setModified(bool m);


protected:
    /**
     * Base point of the Block. Usually 0/0 since blocks can be moved around 
     * using the insertion point of Insert entities.
     */
    //RS_Vector basePoint;
    /**
     * Block name. Acts as an id.
     */
    //RS_String name;
	//! Block data
	RS_BlockData data;
};


#endif
