/****************************************************************************
** $Id: rs_document.h,v 1.11 2004/05/24 19:05:28 andrew Exp $
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


#ifndef RS_DOCUMENT_H
#define RS_DOCUMENT_H

#include "rs_layerlist.h"
#include "rs_entitycontainer.h"
#include "rs_undo.h"
#include "rs_string.h"

class RS_BlockList;

/**
 * Base class for documents. Documents can be either graphics or 
 * blocks and are typically shown in graphic views. Documents hold
 * an active pen for drawing in the Document, a file name and they
 * know whether they have been modified or not.
 *
 * @author Andrew Mustun
 */
class RS_Document : public RS_EntityContainer,
    public RS_Undo {
public:
    RS_Document(RS_EntityContainer* parent=NULL);
    virtual ~RS_Document();

    virtual RS_LayerList* getLayerList() = 0;
    virtual RS_BlockList* getBlockList() = 0;

    virtual void newDoc() = 0;
    virtual bool save() = 0;
    virtual bool saveAs(const RS_String &filename, RS2::FormatType type) = 0;
    virtual bool open(const RS_String &filename, RS2::FormatType type) = 0;
	

    /**
     * @return true for all document entities (e.g. Graphics or Blocks).
     */
    virtual bool isDocument() const {
        return true;
    }

    /**
     * Removes an entity from the entiy container. Implementation
     * from RS_Undo.
     */
    virtual void removeUndoable(RS_Undoable* u) {
        if (u!=NULL && u->undoRtti()==RS2::UndoableEntity) {
            removeEntity((RS_Entity*)u);
        }
    }

    /**
     * @return Currently active drawing pen.
     */
    RS_Pen getActivePen() const {
        return activePen;
    }

    /**
     * Sets the currently active drawing pen to p.
     */
    void setActivePen(RS_Pen p) {
        activePen = p;
    }

    /**
     * @return File name of the document currently loaded.
     * Note, that the default file name is empty.
     */
    RS_String getFilename() const {
        return filename;
    }
	
    /**
     * Sets file name for the document currently loaded.
     */
    void setFilename(const RS_String& fn) {
        filename = fn;
    }

	/**
	 * Sets the documents modified status to 'm'.
	 */
	virtual void setModified(bool m) {
		//std::cout << "RS_Document::setModified: %d" << (int)m << std::endl;
		modified = m;
	}
	
	/**
	 * @retval true The document has been modified since it was last saved.
	 * @retval false The document has not been modified since it was last saved.
	 */
    virtual bool isModified() const {
        return modified;
    }
	
	/**
	 * Overwritten to set modified flag before starting an undo cycle.
	 */
    virtual void startUndoCycle() {
		setModified(true);
		RS_Undo::startUndoCycle();
	}


protected:
    /** Flag set if the document was modified and not yet saved. */
    bool modified;
    /** Active pen. */
    RS_Pen activePen;
    /** File name of the document or empty for a new document. */
    RS_String filename;
	/** Format type */
	RS2::FormatType formatType;
};


#endif
