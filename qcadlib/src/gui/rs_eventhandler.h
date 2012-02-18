/****************************************************************************
** $Id: rs_eventhandler.h,v 1.8 2003/09/06 00:13:02 andrew Exp $
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


#ifndef RS_EVENTHANDLER_H
#define RS_EVENTHANDLER_H

#include "rs_actioninterface.h"
//#include "rs_actiondrawpoint.h"

#include "rs_event.h"
#include "rs_keyevent.h"
#include "rs_mouseevent.h"

#define RS_MAXACTIONS 16

class RS_ActionInterface;

/**
 * The event handler owns and manages all actions that are currently 
 * active. All events going from the view to the actions come over
 * this class.
 */
class RS_EventHandler {
public:
    RS_EventHandler(RS_GraphicView* graphicView);
    ~RS_EventHandler();

    void back();
    void enter();

    void mousePressEvent(RS_MouseEvent *e);
    void mouseReleaseEvent(RS_MouseEvent *e);
    void mouseMoveEvent(RS_MouseEvent *e);
    void mouseLeaveEvent();
    void mouseEnterEvent();

    void keyPressEvent(RS_KeyEvent* e);
    void keyReleaseEvent(RS_KeyEvent* e);

	void commandEvent(RS_CommandEvent* e);
	void enableCoordinateInput();
	void disableCoordinateInput();

    void setDefaultAction(RS_ActionInterface* action);
    RS_ActionInterface* getDefaultAction();
	
    void setCurrentAction(RS_ActionInterface* action);
    RS_ActionInterface* getCurrentAction();
	
    void killSelectActions();
    void killAllActions();
	
    bool hasAction();
    void cleanUp();
    void debugActions();
    void setSnapMode(RS2::SnapMode sm);
    void setSnapRestriction(RS2::SnapRestriction sr);

protected:
	RS_GraphicView* graphicView;
	RS_ActionInterface* defaultAction;
    RS_ActionInterface* currentActions[RS_MAXACTIONS];
    int actionIndex;
	bool coordinateInputEnabled;
};

#endif
