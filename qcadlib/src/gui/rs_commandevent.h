/****************************************************************************
** $Id: rs_commandevent.h,v 1.4 2004/02/18 16:03:00 andrew Exp $
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


#ifndef RS_COMMANDEVENT_H
#define RS_COMMANDEVENT_H

/**
 * Command Events.
 */
class RS_CommandEvent {
public:
    /**
	 * Creates a new command event that is not yet accepted.
	 *
	 * @param cmd the command that was triggered.
	 */
    RS_CommandEvent(const RS_String& cmd) {
        this->cmd = cmd;
		accepted = false;
    }
 
    /**
	 * @return the command that was triggered, usually by
	 * the user.
	 */
    RS_String getCommand() {
        return cmd;
    }

    /**
	 * Sets the event state to accepted.
	 */
	void accept() {
		accepted = true;
	}

    /**
	 * @return Whether the event was already accepted or not.
	 */
	bool isAccepted() {
		return accepted;
	}
 
protected:
    RS_String cmd;
	bool accepted;
};

#endif
