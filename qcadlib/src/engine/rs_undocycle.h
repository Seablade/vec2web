/****************************************************************************
** $Id: rs_undocycle.h,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#ifndef RS_UNDOLISTITEM_H
#define RS_UNDOLISTITEM_H

#include <iostream>

#include "rs.h"
#include "rs_entity.h"
#include "rs_ptrlist.h"
#include "rs_undoable.h"

/**
 * An Undo Cycle represents an action that was triggered and can 
 * be undone. It stores all the pointers to the Undoables affected by 
 * the action. Undoables are entities in a container that can be
 * created and deleted.
 *
 * Undo Cycles are stored within classes derrived from RS_Undo.
 *
 * @see RS_Undoable
 * @see RS_Undo
 *
 * @author Andrew Mustun
 */
class RS_UndoCycle {
public:
    /**
     * @param type Type of undo item.
     */
    RS_UndoCycle(/*RS2::UndoType type*/) {
        //this->type = type;
        undoables.setAutoDelete(false);
    }

    /**
     * Adds an Undoable to this Undo Cycle. Every Cycle can contain one or
     * more Undoables.
     */
    void addUndoable(const RS_Undoable* u) {
        undoables.append(u);
    }

    /**
     * Removes an undoable from the list.
     */
    void removeUndoable(RS_Undoable* u) {
        undoables.remove(u);
    }

    /**
     * Iteration through undoable elements in this item.
     */
    RS_Undoable* getFirstUndoable() {
        return undoables.first();
    }

    /**
     * Iteration through undoable elements in this item.
     */
    RS_Undoable* getNextUndoable() {
        return undoables.next();
    }

    friend std::ostream& operator << (std::ostream& os,
                                      RS_UndoCycle& i) {
        os << " Undo item: " << "\n";
        //os << "   Type: ";
        /*switch (i.type) {
        case RS2::UndoAdd:
            os << "RS2::UndoAdd";
            break;
        case RS2::UndoDel:
            os << "RS2::UndoDel";
            break;
    }*/
        os << "   Undoable ids: ";
        for (RS_Undoable* u=i.getFirstUndoable();
                u!=NULL; u=i.getNextUndoable()) {

            if (u->undoRtti()==RS2::UndoableEntity) {
                RS_Entity* e = (RS_Entity*)u;
                os << e->getId() << (u->isUndone() ? "*" : "") << " ";
            } else {
                os << "|";
            }
        }

        return os;
    }

    friend class RS_Undo;

private:
    //! Undo type:
    //RS2::UndoType type;
    //! List of entity id's that were affected by this action
    RS_PtrList<RS_Undoable> undoables;
};

#endif
