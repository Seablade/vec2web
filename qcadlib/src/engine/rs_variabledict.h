/****************************************************************************
** $Id: rs_variabledict.h,v 1.3 2003/06/14 07:24:34 andrew Exp $
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


#ifndef RS_VARIABLEDICT_H
#define RS_VARIABLEDICT_H


#include "rs_variabledict.h"
#include "rs_variable.h"
#include "rs_dict.h"
#include "rs_string.h"
#include "rs_debug.h"

/**
 * Dictionary of variables. The variables are stored as key / value
 * pairs (string / string).
 *
 * @author Andrew Mustun
 */
class RS_VariableDict {
public:
    RS_VariableDict();
    virtual ~RS_VariableDict() {}

    void clear();
    /**
     * @return Number of variables available.
     */
    int count() {
        return variables.count();
    }

    void add(const RS_String& key, const RS_Vector& value, int code);
    void add(const RS_String& key, const RS_String& value, int code);
    void add(const RS_String& key, int value, int code);
    void add(const RS_String& key, double value, int code);

    RS_Vector getVector(const RS_String& key, const RS_Vector& def);
    RS_String getString(const RS_String& key, const RS_String& def);
    int getInt(const RS_String& key, int def);
    double getDouble(const RS_String& key, double def);

    virtual void remove(const RS_String& key);

	RS_Dict<RS_Variable>& getVariableDict() {
		return variables;
	}

    //void addVariableDictListener(RS_VariableDictListener* listener);

    friend std::ostream& operator << (std::ostream& os, RS_VariableDict& v);

private:
    //! Variables for the graphic
    RS_Dict<RS_Variable> variables;
}
;

#endif
