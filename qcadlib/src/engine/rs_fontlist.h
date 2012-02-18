/****************************************************************************
** $Id: rs_fontlist.h,v 1.4 2004/12/09 23:09:51 andrew Exp $
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


#ifndef RS_FONTLIST_H
#define RS_FONTLIST_H


#include "rs_font.h"
#include "rs_entity.h"
#include "rs_ptrlist.h"

#define RS_FONTLIST RS_FontList::instance()

/**
 * The global list of fonts. This is implemented as a singleton.
 * Use RS_FontList::instance() to get a pointer to the object.
 *
 * @author Andrew Mustun
 */
class RS_FontList {
protected:
    RS_FontList();

public:
    /**
     * @return Instance to the unique font list.
     */
    static RS_FontList* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_FontList();
        }
        return uniqueInstance;
    }

    virtual ~RS_FontList() {}

    void init();

    void clearFonts();
    int countFonts() {
        return fonts.count();
    }
    virtual void removeFont(RS_Font* font);
    RS_Font* requestFont(const RS_String& name);
    //! @return First font of the list.
    RS_Font* firstFont() {
        return fonts.first();
    }
    /** 
	 * @return Next font from the list after
     * calling firstFont() or nextFont().
     */
    RS_Font* nextFont() {
        return fonts.next();
    }

    friend std::ostream& operator << (std::ostream& os, RS_FontList& l);

protected:
    static RS_FontList* uniqueInstance;

private:
    //! fonts in the graphic
    RS_PtrList<RS_Font> fonts;
}
;

#endif
