/****************************************************************************
** $Id: rs_script.h,v 1.3 2004/12/09 23:09:53 andrew Exp $
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

#ifndef RS_SCRIPT_H
#define RS_SCRIPT_H

#include <iostream>

#include "rs_string.h"


/**
 * Class for representing a script. This is implemented as a RS_String
 * containing the script name.
 *
 * @author Andrew Mustun
 */
class RS_Script {
public:
    RS_Script(const RS_String& name, const RS_String& path);
    //RS_Script(const char* name);

    /** @return the name of this script. */
    RS_String getName() const {
        return name;
    }

    /** @return the full path and file name of this script. */
    RS_String getPath() const {
        return path;
    }

private:
    //! Script name
    RS_String name;

    //! Full path to script
    RS_String path;
};

#endif

