/****************************************************************************
** $Id: rs_scriptlist.h,v 1.4 2004/12/09 23:09:53 andrew Exp $
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

#ifndef RS_SCRIPTLIST_H
#define RS_SCRIPTLIST_H


#include "rs_script.h"
#include "rs_ptrlist.h"

#define RS_SCRIPTLIST RS_ScriptList::instance()

/**
 * The global list of scripts. This is implemented as a singleton.
 * Use RS_ScriptList::instance() to get a pointer to the object.
 *
 * @author Andrew Mustun
 */
class RS_ScriptList {
protected:
    RS_ScriptList();

public:
    /**
     * @return Instance to the unique script list.
     */
    static RS_ScriptList* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_ScriptList();
        }
        return uniqueInstance;
    }

    virtual ~RS_ScriptList() {}

    void init();

    void clearScripts();
    int countScripts() {
        return scripts.count();
    }
    //void activateScript(const RS_String& name);
    //void activateScript(RS_Script* script);
    ////! @return The active script of NULL if no script is activated.
    //RS_Script* getActiveScript() { return activeScript; }
    //virtual void addScript(RS_Script* script);
    virtual void removeScript(RS_Script* script);
    //virtual void editScript(RS_Script* script, const RS_Script& source);
    RS_Script* requestScript(const RS_String& name);
    //RS_Script* loadScript(const RS_String& name);
    //void toggleScript(const RS_String& name);
    //! @return First script of the list.
    RS_Script* firstScript() {
        return scripts.first();
    }
    /** @return Next script from the list after
     * calling firstScript() or nextScript().
     */
    RS_Script* nextScript() {
        return scripts.next();
    }

    //void addScriptListListener(RS_ScriptListListener* listener);

    static bool test();

protected:
    static RS_ScriptList* uniqueInstance;

private:
    //! all scripts available
    RS_PtrList<RS_Script> scripts;
    //! List of registered ScriptListListeners
    //RS_PtrList<RS_ScriptListListener> scriptListListeners;
    //! Currently active script
    //RS_Script* activeScript;
}
;

#endif
