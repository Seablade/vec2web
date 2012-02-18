/****************************************************************************
** $Id: rs_pattern.h,v 1.3 2004/02/18 16:03:00 andrew Exp $
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


#ifndef RS_PATTERN_H
#define RS_PATTERN_H

#include "rs_entitycontainer.h"

class RS_PatternList;

/**
 * Patterns are used for hatches. They are stored in a RS_PatternList.
 * Use RS_PatternList to access a pattern.
 *
 * @author Andrew Mustun
 */
class RS_Pattern : public RS_EntityContainer {
public:
    RS_Pattern(const RS_String& fileName);
    virtual ~RS_Pattern();

    virtual bool loadPattern();
	
    /** @return the fileName of this pattern. */
    RS_String getFileName() const {
        return fileName;
    }

protected:
    //! Pattern file name
    RS_String fileName;

    //! Is this pattern currently loaded into memory?
    bool loaded;

	
};


#endif
