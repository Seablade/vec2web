/****************************************************************************
** $Id: rs_undoable.h,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#ifndef RS_UNDOABLE_H
#define RS_UNDOABLE_H

#include "rs_flags.h"

class RS_UndoCycle;



/**
 * Base class for something that can be added and deleted and every 
 * addition and deletion can be undone.
 *
 * @see RS_Undo
 * @author Andrew Mustun
 */
class RS_Undoable : public RS_Flags {
public:
    RS_Undoable();
    virtual ~RS_Undoable();

    /**
     * Runtime type identification for undoables.
     * Note that this is voluntarily. The default implementation 
     * returns RS2::UndoableUnknown.
     */
    virtual RS2::UndoableType undoRtti() {
        return RS2::UndoableUnknown;
    }

    virtual void setUndoCycle(RS_UndoCycle* cycle);
    virtual void changeUndoState();
    virtual void setUndoState(bool undone);
    virtual bool isUndone() const;

	/**
	 * Can be overwriten by the implementing class to be notified
	 * when the undo state changes (the undoable becomes visible / invisible).
	 */
	virtual void undoStateChanged(bool /*undone*/) {}

    //friend std::ostream& operator << (std::ostream& os, RS_Undoable& a);

private:
    RS_UndoCycle* cycle;
};

#endif
