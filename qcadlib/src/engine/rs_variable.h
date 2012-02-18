/****************************************************************************
** $Id: rs_variable.h,v 1.2 2003/06/11 06:55:59 andrew Exp $
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


#ifndef RS_VARIABLE_H
#define RS_VARIABLE_H


#include "rs.h"
#include "rs_string.h"
#include "rs_vector.h"
#include "rs_debug.h"

/**
 * A variable of type int, double, string or vector.
 * The variable also contains its type and an int code
 * which can identify its contents in any way.
 *
 * @author Andrew Mustun
 */
class RS_Variable {
public:
	typedef struct {
		RS_String s;
		int i;
		double d;
		RS_Vector v;
	} RS_VariableContents;
	
    RS_Variable() {
		type = RS2::VariableVoid;
		code = 0;
	}
    RS_Variable(const RS_Vector& v, int c) {
		setVector(v);
		code = c;
	}
    RS_Variable(const RS_String& v, int c) {
		setString(v);
		code = c;
	}
    RS_Variable(int v, int c) {
		setInt(v);
		code = c;
	}
    RS_Variable(double v, int c) {
		setDouble(v);
		code = c;
	}
    virtual ~RS_Variable() {}

	void setString(const RS_String& str) {
		contents.s = str;
		type = RS2::VariableString;
	}
	void setInt(int i) {
		contents.i = i;
		type = RS2::VariableInt;
	}
	void setDouble(double d) {
		contents.d = d;
		type = RS2::VariableDouble;
	}
	void setVector(const RS_Vector& v) {
		contents.v = v;
		type = RS2::VariableVector;
	}

	RS_String getString() {
		return contents.s;
	}
	int getInt() {
		return contents.i;
	}
	double getDouble() {
		return contents.d;
	}
	RS_Vector getVector() {
		return contents.v;
	}

	RS2::VariableType getType() {
		return type;
	}
	int getCode() {
		return code;
	}

    //friend std::ostream& operator << (std::ostream& os, RS_Variable& v);

private:
	RS_VariableContents contents;
	RS2::VariableType type;
	int code;
};

#endif
