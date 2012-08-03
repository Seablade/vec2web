/****************************************************************************
** $Id: rs_actioninterface.h,v 1.23 2004/02/19 23:20:32 andrew Exp $
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


#ifndef RS_ACTIONINTERFACE_H
#define RS_ACTIONINTERFACE_H

#include <qobject.h>
#include <qaction.h>

#include "rs_entitycontainer.h"
#include "rs_commandevent.h"
#include "rs_event.h"
#include "rs_graphic.h"
#include "rs_graphicview.h"
#include "rs_mouseevent.h"
#include "rs_snapper.h"
#include "rs_string.h"
#include "rs_preview.h"
#include "rs_dialogfactory.h"
#include "rs_stringlist.h"

#ifndef RS_NO_QCADCMD
#include "rs_commands.h"
#endif

//template<class T> T* instantiate(RS_EntityContainer& container, RS_GraphicView& graphicView) {
//	return new T(container, graphicView);
	//void (*function)() = T::instantiate;
	//return (*function)();
//}

/**
 * This is the interface that must be implemented for all 
 * action classes. Action classes handle actions such
 * as drawing lines, moving entities or zooming in.
 *
 * Inherited from QObject for Qt translation features.
 *
 * @author Andrew Mustun
 */
class RS_ActionInterface : public QObject, public RS_Snapper {
    Q_OBJECT
public:
    RS_ActionInterface(const char* name,
                       RS_EntityContainer& container,
                       RS_GraphicView& graphicView);
    virtual ~RS_ActionInterface();
	
    virtual RS2::ActionType rtti();

    RS_String getName();

    virtual void init(int status=0);
    virtual void mouseMoveEvent(RS_MouseEvent*);
    virtual void mousePressEvent(RS_MouseEvent*);

    virtual void mouseReleaseEvent(RS_MouseEvent*);
    virtual void keyPressEvent(RS_KeyEvent* e);
    virtual void keyReleaseEvent(RS_KeyEvent* e);
    virtual void coordinateEvent(RS_CoordinateEvent*);
    virtual void commandEvent(RS_CommandEvent*);
    virtual RS_StringList getAvailableCommands();
    virtual void setStatus(int status);
    virtual int getStatus();
    virtual void trigger();
    virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
    virtual void updateToolBar();
    virtual bool isFinished();
    virtual void setFinished();
    virtual void finish();
    virtual void setPredecessor(RS_ActionInterface* pre);
    virtual void suspend();
    virtual void resume();
    virtual void hideOptions();
    virtual void showOptions();
    bool checkCommand(const RS_String& cmd, const RS_String& str,
                             RS2::ActionType action=RS2::ActionNone);
	RS_String command(const RS_String& cmd);
	RS_String msgAvailableCommands();

private:
    /**
     * Current status of the action. After an action has
     * been created the action status is set to 0. Actions
     * that are terminated have a stats of -1. Other status
     * numbers can be used to describe the stage this action
     * is in. E.g. a window zoom consists of selecting the
     * first corner (status 0), and selecting the second
     * corner (status 1).
     */
    int status;

protected:
    /** Action name. Used internally for debugging */
    RS_String name;

    /**
     * This flag is set when the action has terminated and 
     * can be deleted.
     */
    bool finished;

    /**
     * Pointer to the graphic is this container is a graphic. 
     * NULL otherwise
     */
    RS_Graphic* graphic;

	/**
	 * Pointer to the document (graphic or block) or NULL.
	 */
	RS_Document* document;

    /**
     * Pointer to the default mouse cursor for this action or NULL.
     */
    //RS2::CursorType cursor;

    /**
     * Predecessor of this action or NULL.
     */
    RS_ActionInterface* predecessor;

    /**
     * String prepended to the help text for currently available commands.
     */
    //static RS_String msgAvailableCommands;

    /**
     * Command used for showing help for every action.
     */
    //static RS_String cmdHelp;
	
    /**
     * Command for answering yes to a question.
     */
    //static RS_String cmdYes;
    //static RS_String cmdYes2;
	
     /**
     * Command for answering no to a question.
     */
    //static RS_String cmdNo;
    //static RS_String cmdNo2;
};


#endif
