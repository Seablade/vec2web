/****************************************************************************
** $Id: rs_clipboard.cpp,v 1.3 2004/12/09 23:09:50 andrew Exp $
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


#include "rs_clipboard.h"
#include "rs_block.h"
#include "rs_layer.h"
#include "rs_entity.h"

RS_Clipboard* RS_Clipboard::uniqueInstance = NULL;



void RS_Clipboard::clear() {
	graphic.clear();
	graphic.clearBlocks();
	graphic.clearLayers();
	graphic.clearVariables();
}





void RS_Clipboard::addBlock(RS_Block* b) {
	if (b!=NULL) {
		graphic.addBlock(b, false);
	}
}


bool RS_Clipboard::hasBlock(const RS_String& name) {
	return (graphic.findBlock(name)!=NULL);
}


void RS_Clipboard::addLayer(RS_Layer* l) {
	if (l!=NULL) {
		//graphic.addLayer(l->clone());
		graphic.addLayer(l);
	}
}



bool RS_Clipboard::hasLayer(const RS_String& name) {
	return (graphic.findLayer(name)!=NULL);
}



void RS_Clipboard::addEntity(RS_Entity* e) {
	if (e!=NULL) {
		//graphic.addEntity(e->clone());
		graphic.addEntity(e);
		e->reparent(&graphic);
	}
}

/**
 * Dumps the clipboard contents to stdout.
 */
std::ostream& operator << (std::ostream& os, RS_Clipboard& cb) {
	os << "Clipboard: " << cb.graphic << "\n";

	return os;
}

