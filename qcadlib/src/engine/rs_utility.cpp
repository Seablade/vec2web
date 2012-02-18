/****************************************************************************
** $Id: rs_utility.cpp,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#include "rs_utility.h"


/**
 * Converts a double to a string cutting away unnecessary 0's.
 * e.g. 2.70000  -> 2.7
 */
RS_String RS_Utility::doubleToString(double value, int precision) {
    RS_String ret;

    ret.setNum(value, 'f', precision);

    if(ret.contains('.')) {
        // remove trailing zeros:
        while(ret.at(ret.length()-1)=='0') {
            ret.truncate(ret.length()-1);
        }

        // remove trailing .
        if(ret.at(ret.length()-1)=='.') {
            ret.truncate(ret.length()-1);
        }
    }

    return ret;
}

// EOF

