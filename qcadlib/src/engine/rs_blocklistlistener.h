/****************************************************************************
** $Id: rs_blocklistlistener.h,v 1.2 2003/06/11 06:55:57 andrew Exp $
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


#ifndef RS_BLOCKLISTLISTENER_H
#define RS_BLOCKLISTLISTENER_H

#include "rs_block.h"

/**
 * This class is an interface for classes that are interested in
 * knowing about changes in the block list. 
 */
class RS_BlockListListener {
public:
    RS_BlockListListener() {}
    virtual ~RS_BlockListListener() {}

    /**
     * Called when the active block changes.
     */
    virtual void blockActivated(RS_Block*) {}

    /**
     * Called when a new block is added to the list.
     */
    virtual void blockAdded(RS_Block*) {}

    /**
     * Called when a block is removed from the list.
     */
    virtual void blockRemoved(RS_Block*) {}

    /**
     * Called when a block's attributes are modified.
     */
    virtual void blockEdited(RS_Block*) {}

    /**
     * Called when a block's visibility is toggled. 
     */
    virtual void blockToggled(RS_Block*) {}
}
;

#endif
