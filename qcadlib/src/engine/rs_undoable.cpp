/****************************************************************************
** $Id: rs_undoable.cpp,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#include "rs_undoable.h"

#include "rs_undocycle.h"


/**
 * Default constructor.
 */
RS_Undoable::RS_Undoable() {
    cycle = NULL;
}



/**
 * Destructor. Makes sure that this undoable is removed from 
 * its undo cycle before it is deleted.
 */
RS_Undoable::~RS_Undoable() {
    if (cycle!=NULL) {
        cycle->removeUndoable(this);
    }
}



/**
 * Sets the undo cycle this entity is in. This is necessary to
 * make sure the entity can remove itself from the cycle before
 * being deleted.
 */
void RS_Undoable::setUndoCycle(RS_UndoCycle* cycle) {
    this->cycle = cycle;
}



/**
 * The undoable thing gets activated if it was undone and 
 * deactivated otherwise.
 */
void RS_Undoable::changeUndoState() {
    toggleFlag(RS2::FlagUndone);
	undoStateChanged(isUndone());
}



/**
 * Undoes or redoes an undoable.
 */
void RS_Undoable::setUndoState(bool undone) {
    if (undone) {
        setFlag(RS2::FlagUndone);
    } else {
        delFlag(RS2::FlagUndone);
    }
	undoStateChanged(isUndone());
}



/**
 * Is this entity in the Undo memory and not active?
 */
bool RS_Undoable::isUndone() const {
    return getFlag(RS2::FlagUndone);
}

