/****************************************************************************
** $Id: rs_linetypepattern.h,v 1.3 2003/08/08 14:05:26 andrew Exp $
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


#ifndef RS_LINETYPEPATTERN_H
#define RS_LINETYPEPATTERN_H

#include <stdarg.h>

/**
 * Stores a line type pattern.
 */
class RS_LineTypePattern {
public:
    RS_LineTypePattern(int count ...) {
        va_list ap;
        int i=0;
        num = count;

        va_start(ap, count);
        pattern = new double[num];
        for (i=0; i<count; i++) {
            pattern[i] = va_arg(ap, double);
        }
        va_end(ap);
    }

    ~RS_LineTypePattern() {
        delete[] pattern;
    }

public:
    double* pattern;
    int num;
};

// Create line patterns
static RS_LineTypePattern patternSolidLine(1, 10.0);

static RS_LineTypePattern patternDotLine(2, 0.1, -6.2);
static RS_LineTypePattern patternDotLine2(2, 0.1, -3.1);
static RS_LineTypePattern patternDotLineX2(2, 0.1, -12.4);

static RS_LineTypePattern patternDashLine(2, 12.0, -6.0);
static RS_LineTypePattern patternDashLine2(2, 6.0, -3.0);
static RS_LineTypePattern patternDashLineX2(2, 24.0, -12.0);

static RS_LineTypePattern patternDashDotLine(4, 12.0, -5.95, 0.1, -5.95);
static RS_LineTypePattern patternDashDotLine2(4, 6.0, -2.95, 0.1, -2.95);
static RS_LineTypePattern patternDashDotLineX2(4, 24.0, -11.95, 0.1, -11.95);

static RS_LineTypePattern patternDivideLine(
    6, 12.0, -5.9, 0.15, -5.9, 0.15, -5.9);
static RS_LineTypePattern patternDivideLine2(
    6, 6.0, -2.9, 0.15, -2.9, 0.15, -2.9);
static RS_LineTypePattern patternDivideLineX2(
    6, 24.0, -11.9, 0.15, -11.9, 0.15, -11.9);
	
static RS_LineTypePattern patternCenterLine(4, 32.0, -6.0, 6.0, -6.0);
static RS_LineTypePattern patternCenterLine2(4, 16.0, -3.0, 3.0, -3.0);
static RS_LineTypePattern patternCenterLineX2(4, 64.0, -12.0, 12.0, -12.0);

static RS_LineTypePattern patternBorderLine(
	6, 12.0, -6.0, 12.0, -5.95, 0.1, -5.95);
static RS_LineTypePattern patternBorderLine2(
	6, 6.0, -3.0, 6.0, -2.95, 0.1, -2.95);
static RS_LineTypePattern patternBorderLineX2(
	6, 24.0, -12.0, 24.0, -11.95, 0.1, -11.95);

static RS_LineTypePattern patternBlockLine(2, 0.5, -0.5);
static RS_LineTypePattern patternSelected(2, 1.0, -3.0);

#endif
