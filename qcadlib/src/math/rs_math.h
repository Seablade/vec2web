/****************************************************************************
** $Id: rs_math.h,v 1.19 2004/11/30 02:11:32 andrew Exp $
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

#ifndef RS_MATH_H
#define RS_MATH_H

// no idea why, but doesn't link without that under win32 / bcc55:
#ifndef _MT
#define _MT
#endif

#include <math.h>
#include <errno.h>

#ifndef RS_NO_FPARSER
#include "fparser.h"
#endif

#include "rs.h"
#include "rs_string.h"
#include "rs_regexp.h"
#include "rs_vector.h"

//#ifdef __GNUC__
//#define min(x,y) (x<y ? x : y)
//#define max(x,y) (x>y ? x : y)
//#endif

#define ARAD 57.29577951308232
#define RS_TOLERANCE 1.0e-10
#define RS_TOLERANCE_ANGLE 1.0e-8

typedef unsigned int uint;

/**
 * Math functions.
 */
class RS_Math {
public:
    static int round(double v);
	static double pow(double x, double y);

    //static double abs(double v);
    //static int abs(int v);
    static double rad2deg(double a);
    static double deg2rad(double a);
    static double rad2gra(double a);
    static int findGCD(int a, int b);
    static bool isAngleBetween(double a,
                               double a1, double a2,
                               bool reversed);
    static double correctAngle(double a);
    static double getAngleDifference(double a1, double a2);
    static double makeAngleReadable(double angle, bool readable=true,
                                    bool* corrected=NULL);
    static bool isAngleReadable(double angle);
    static bool isSameDirection(double dir1, double dir2, double tol);
    static double eval(const RS_String& expr, double def=0.0);

    static bool cmpDouble(double v1, double v2, double tol=0.001);
  	
    /**
     * Evaluates a mathematical expression and returns the result.
     * If an error occured, ok will be set to false (if ok isn't NULL).
     */
	// Keep that in the header file for dynamic inclusion/exclusion.
    static double eval(const RS_String& expr, bool* ok) {
#ifndef RS_NO_FPARSER
        FunctionParser fp;
        fp.AddConstant("pi", M_PI);

		// replace '14 3/4' with '14+3/4'
		RS_String s = expr;
		bool done;
		do {
			done = true;
			int i = s.find(RS_RegExp("[0-9]* [0-9]*/[0-9]*"));
			if (i!=-1) {
				int i2 = s.find(' ', i);
				if (i2!=-1) {
					s.replace(i2, 1, "+");
					done = false;
				}
			}
		} while (!done);

        int ret = fp.Parse(s.latin1(), "", true);

        if (ret>=0) {
            if (ok!=NULL) {
                *ok = false;
            }
            return 0.0;
        }

        if (ok!=NULL) {
            *ok = true;
        }

        return fp.Eval(NULL);
#else
        //std::cerr << "RS_Math::eval: No FParser support compiled in.\n";
        return expr.toDouble();
#endif
    }

    static RS_String doubleToString(double value, double prec);
    static RS_String doubleToString(double value, int prec);

    static void test();
};

#endif
