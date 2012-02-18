/****************************************************************************
** $Id: rs_block.cpp,v 1.7 2004/04/09 19:56:41 andrew Exp $
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


#include "rs_block.h"

#include "rs_graphic.h"

/**
 * @param parent The graphic this block belongs to.
 * @param name The name of the block used as an identifier.
 * @param basePoint Base point (offset) of the block.
 */
RS_Block::RS_Block(RS_EntityContainer* parent,
                   const RS_BlockData& d)
        : RS_Document(parent), data(d) {

    pen = RS_Pen(RS_Color(128,128,128), RS2::Width01, RS2::SolidLine);
}



RS_Block::~RS_Block() {}



RS_Entity* RS_Block::clone() {
    RS_Block* blk = new RS_Block(*this);
    blk->detach();
    blk->initId();
    return blk;
}



RS_LayerList* RS_Block::getLayerList() {
    RS_Graphic* g = getGraphic();
    if (g!=NULL) {
        return g->getLayerList();
    } else {
        return NULL;
    }
}



RS_BlockList* RS_Block::getBlockList() {
    RS_Graphic* g = getGraphic();
    if (g!=NULL) {
        return g->getBlockList();
    } else {
        return NULL;
    }
}


bool RS_Block::save() {
    RS_Graphic* g = getGraphic();
    if (g!=NULL) {
        return g->save();
    } else {
        return false;
    }
}


bool RS_Block::saveAs(const RS_String& filename, RS2::FormatType type) {
    RS_Graphic* g = getGraphic();
    if (g!=NULL) {
        return g->saveAs(filename, type);
    } else {
        return false;
    }
}



/**
 * Sets the parent documents modified status to 'm'.
 */
void RS_Block::setModified(bool m) {
    RS_Graphic* p = getGraphic();
    if (p) {
        p->setModified(m);
    }
    modified = m;
}
