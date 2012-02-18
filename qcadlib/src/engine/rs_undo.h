/****************************************************************************
** $Id: rs_undo.h,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#ifndef RS_UNDO_H
#define RS_UNDO_H

#include "rs_undocycle.h"
#include "rs_ptrlist.h"

/**
 * Undo / redo functionality. The internal undo list consists of
 * RS_UndoCycle entries.
 *
 * @see RS_UndoCycle
 * @author Andrew Mustun
 */
class RS_Undo {
public:
    RS_Undo();
    virtual ~RS_Undo() {}

    void addUndoCycle(RS_UndoCycle* i);

    virtual void undo();
    virtual void redo();

    virtual RS_UndoCycle* getUndoCycle();
    virtual RS_UndoCycle* getRedoCycle();

    virtual int countUndoCycles();
    virtual int countRedoCycles();

    virtual void startUndoCycle();
    virtual void addUndoable(RS_Undoable* u);
    virtual void endUndoCycle();

    /**
     * Must be overwritten by the implementing class and delete
     * the given Undoable (unrecoverable). This method is called
     * for Undoables that are no longer in the undo buffer.
     */
    virtual void removeUndoable(RS_Undoable* u) = 0;

    friend std::ostream& operator << (std::ostream& os, RS_Undo& a);

    static bool test();

protected:
    //! List of undo list items. every item is something that can be undone.
    RS_PtrList<RS_UndoCycle> undoList;

    /**
     * Index that points to the current position in the undo list.
     * The item it points on will be undone the next time undo is called.
     * The item after will be redone (if there is an item) when redo 
     * is called.
     */
    int undoPointer;

    /**
     * Current undo cycle.
     */
    RS_UndoCycle* currentCycle;

};


/**
 * Stub for testing the RS_Undo class.
 */
#ifdef RS_TEST
class RS_UndoStub : public RS_Undo {
    virtual void removeUndoable(RS_Undoable* u) {
        delete u;
        u = NULL;
    }
};
#endif

#endif

