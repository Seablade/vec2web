/****************************************************************************
** $Id: rs_infoarea.h,v 1.2 2004/07/09 23:54:59 andrew Exp $
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

#ifndef RS_INFOAREA_H
#define RS_INFOAREA_H

#include "rs_vector.h"
#include "rs_valuevector.h"



/**
 * Class for getting information about an area. 
 *
 * @author Andrew Mustun
 */
class RS_InfoArea {
public: 
	RS_InfoArea();
	~RS_InfoArea();

	void reset();
	void addPoint(const RS_Vector& p);
	void calculate();
	void close();
	bool isValid();
	bool isClosed();
	double getArea() { 
		return area; 
	}
	double getCircumference() { 
		return circumference; 
	}
	int count() { 
		return thePoints.count(); 
	}

private:
	double calcSubArea(const RS_Vector& p1, const RS_Vector& p2);

	RS_ValueVector<RS_Vector> thePoints;
	double baseY;
	double area;
	double circumference;
};

#endif
