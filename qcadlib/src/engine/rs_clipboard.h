/****************************************************************************
** $Id: rs_clipboard.h,v 1.5 2003/09/27 20:34:54 andrew Exp $
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


#ifndef RS_CLIPBOARD_H
#define RS_CLIPBOARD_H

#include <iostream>
#include "rs_graphic.h"

#define RS_CLIPBOARD RS_Clipboard::instance()

class RS_Block;
class RS_Layer;
class RS_Entity;

/**
 * QCad internal clipboard. We don't use the system clipboard for
 * better portaility.
 * Implemented as singleton.
 *
 * @author Andrew Mustun
 */
class RS_Clipboard {
protected:
    RS_Clipboard() {
    }

public:
    /**
     * @return Instance to the unique clipboard object.
     */
    static RS_Clipboard* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_Clipboard();
        }
        return uniqueInstance;
    }

	void clear();

	void addBlock(RS_Block* b);
	bool hasBlock(const RS_String& name);
	int  countBlocks() {
		return graphic.countBlocks();
	}
	RS_Block* blockAt(int i) {
		return graphic.blockAt(i);
	}
	
	void addLayer(RS_Layer* l);
	bool hasLayer(const RS_String& name);
	int  countLayers() {
		return graphic.countLayers();
	}
	RS_Layer* layerAt(int i) {
		return graphic.layerAt(i);
	}

	void addEntity(RS_Entity* e);

	uint count() {
		return graphic.count();
	}
	RS_Entity* entityAt(uint i) {
		return graphic.entityAt(i);
	}
	RS_Entity* firstEntity() {
		return graphic.firstEntity();
	}
	
	RS_Entity* nextEntity() {
		return graphic.nextEntity();
	}

	RS_Graphic* getGraphic() {
		return &graphic;
	}

    friend std::ostream& operator << (std::ostream& os, RS_Clipboard& cb);

protected:
    static RS_Clipboard* uniqueInstance;

	RS_Graphic graphic;
};

#endif

