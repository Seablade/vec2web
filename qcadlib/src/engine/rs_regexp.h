/****************************************************************************
** $Id: rs_regexp.h,v 1.3 2003/10/22 18:17:51 andrew Exp $
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


#ifndef RS_REGEXP_H
#define RS_REGEXP_H

#include <qregexp.h>

#if QT_VERSION>=0x030000

#define RS_RegExp QRegExp

#else

class RS_RegExp : public QRegExp {
public:
    RS_RegExp(const RS_String& pattern, bool caseSensitive = TRUE,
              bool wildcard = FALSE ) :
    QRegExp(pattern, caseSensitive, wildcard) {
		thecap = "";
	}

    int RS_RegExp::search(const RS_String& str, int offset = 0) {
		int len = 0;
		int pos = 0;
        pos = match(str, offset, &len, true);
		if (pos!=-1) {
			thecap = str.mid(pos, len);
		}
		else {
			thecap = "";
		}
        return pos;
    }

	RS_String RS_RegExp::cap() {
		return thecap;
	}

private:
	RS_String thecap;
};

#endif

#endif
