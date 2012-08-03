/****************************************************************************
** $Id: rs_string.cpp,v 1.1 2003/10/22 19:46:31 andrew Exp $
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


#include "rs_string.h"

#include <iostream>


RS_String RS_StringCompat::replace(const RS_String& str,
                                   RS_Char c1, RS_Char c2) {

    RS_String ret = str;

    for (uint i=0; i<ret.length(); ++i) {
        if (ret.at(i)==c1) {
            ret.ref(i) = c2;
        }
    }

    return ret;
}

RS_String RS_StringCompat::replace(const RS_String& str,
                                   const RS_String& s1, const RS_String& s2) {

    if (s1.isEmpty()) {
        return str;
    }

    RS_String ret = "";

    for (uint i=0; i<str.length(); ++i) {
        if (str.mid(i, s1.length())==s1) {
            ret += s2;
			i += s1.length()-1;
        } else {
            ret += str.at(i);
        }
    }

    return ret;
}

void RS_StringCompat::test() {
    RS_String res;
    RS_String s1 = "abcdefg";
    res = RS_StringCompat::replace(s1, 'a', 'A');
    assert(res=="Abcdefg");
    res = RS_StringCompat::replace(s1, 'b', 'B');
    assert(res=="aBcdefg");
    res = RS_StringCompat::replace(s1, 'g', 'G');
    assert(res=="abcdefG");

    res = RS_StringCompat::replace(s1, "", "blah");
    assert(res=="abcdefg");
    res = RS_StringCompat::replace(s1, "ab", "AB");
    assert(res=="ABcdefg");
    res = RS_StringCompat::replace(s1, "def", "DEF");
    assert(res=="abcDEFg");
    res = RS_StringCompat::replace(s1, "g", "G");
    assert(res=="abcdefG");
    res = RS_StringCompat::replace(s1, "fg", "FG");
    assert(res=="abcdeFG");

    s1 = "a";
    res = RS_StringCompat::replace(s1, "a", "ABC");
    assert(res=="ABC");
    s1 = "ab";
    res = RS_StringCompat::replace(s1, "ab", "");
    assert(res=="");
}
