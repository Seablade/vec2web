/****************************************************************************
** $Id: rs_string.h,v 1.4 2003/10/22 19:46:31 andrew Exp $
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


#ifndef RS_STRING_H
#define RS_STRING_H

#include <assert.h>

#include <qstring.h>

#define RS_String QString
#define RS_Char QChar

class RS_StringCompat {
public:
    static RS_String replace(const RS_String& str, RS_Char c1, RS_Char c2);
    static RS_String replace(const RS_String& str, 
		const RS_String& s1, const RS_String& s2);
	static void test();
};

#endif
