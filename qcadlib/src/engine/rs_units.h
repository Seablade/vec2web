/****************************************************************************
** $Id: rs_units.h,v 1.6 2004/05/15 09:09:20 andrew Exp $
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


#ifndef RS_UNITS_H
#define RS_UNITS_H

#include "rs.h"
#include "rs_string.h"
#include "rs_vector.h"

/**
 * Conversion methods for units
 *
 * @author Andrew Mustun
 */
class RS_Units {
public:

    //static char* unit2sign(RS2::Unit unit);

    //static RS2::Unit string2unit(const char* str, bool* ok=0);
    //static char* unit2string(RS2::Unit unit);

    static RS2::Unit dxfint2unit(int dxfint);

    static RS_String unitToString(RS2::Unit u, bool t = true);
    static RS2::Unit stringToUnit(const RS_String& u);

	static bool isMetric(RS2::Unit u);
	static double getFactorToMM(RS2::Unit u);
	static double convert(double val, RS2::Unit src, RS2::Unit dest);
	static RS_Vector convert(const RS_Vector val, RS2::Unit src, RS2::Unit dest);
	
    static RS_String unitToSign(RS2::Unit u);

    static RS_String formatLinear(double length, RS2::Unit unit,
                                  RS2::LinearFormat format,
                                  int prec, bool showUnit=false);
    static RS_String formatScientific(double length, RS2::Unit unit,
                                  int prec, bool showUnit=false);
    static RS_String formatDecimal(double length, RS2::Unit unit,
                                  int prec, bool showUnit=false);
    static RS_String formatEngineering(double length, RS2::Unit unit,
                                  int prec, bool showUnit=false);
    static RS_String formatArchitectural(double length, RS2::Unit unit,
                                  int prec, bool showUnit=false);
    static RS_String formatFractional(double length, RS2::Unit unit,
                                  int prec, bool showUnit=false);

    static RS_String formatAngle(double angle, RS2::AngleFormat format,
                                 int prec);

	static RS_Vector paperFormatToSize(RS2::PaperFormat p);
	static RS2::PaperFormat paperSizeToFormat(const RS_Vector s);
	
	static RS_String paperFormatToString(RS2::PaperFormat p);
	static RS2::PaperFormat stringToPaperFormat(const RS_String& p);

	static void test();
};


#endif
