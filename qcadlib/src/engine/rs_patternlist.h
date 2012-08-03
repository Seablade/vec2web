/****************************************************************************
** $Id: rs_patternlist.h,v 1.4 2004/09/20 12:08:35 andrew Exp $
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


#ifndef RS_PATTERNLIST_H
#define RS_PATTERNLIST_H


#include "rs_pattern.h"
#include "rs_entity.h"
#include "rs_ptrlist.h"

#define RS_PATTERNLIST RS_PatternList::instance()

/**
 * The global list of patterns. This is implemented as a singleton.
 * Use RS_PatternList::instance() to get a pointer to the object.
 *
 * @author Andrew Mustun
 */
class RS_PatternList {
protected:
    RS_PatternList();

public:
    /**
     * @return Instance to the unique pattern list.
     */
    static RS_PatternList* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_PatternList();
        }
        return uniqueInstance;
    }

    virtual ~RS_PatternList() {}

    void init();

    void clearPatterns();
    int countPatterns() {
        return patterns.count();
    }
    virtual void removePattern(RS_Pattern* pattern);
    RS_Pattern* requestPattern(const RS_String& name);
    //! @return First pattern of the list.
    RS_Pattern* firstPattern() {
        return patterns.first();
    }
    /** 
	 * @return Next pattern from the list after
     * calling firstPattern() or nextPattern().
     */
    RS_Pattern* nextPattern() {
        return patterns.next();
    }

	bool contains(const RS_String& name);

    //void addPatternListListener(RS_PatternListListener* listener);

    friend std::ostream& operator << (std::ostream& os, RS_PatternList& l);

    //static bool test();

protected:
    static RS_PatternList* uniqueInstance;

private:
    //! patterns in the graphic
    RS_PtrList<RS_Pattern> patterns;
    //! List of registered PatternListListeners
    //RS_PtrList<RS_PatternListListener> patternListListeners;
}
;

#endif
