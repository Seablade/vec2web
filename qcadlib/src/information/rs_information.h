/****************************************************************************
** $Id: rs_information.h,v 1.9 2004/11/20 00:42:21 andrew Exp $
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

#ifndef RS_INFORMATION_H
#define RS_INFORMATION_H

#include "rs_entitycontainer.h"
#include "rs_line.h"
#include "rs_arc.h"



/**
 * Class for getting information about entities. This includes
 * also things like the end point of an element which is 
 * nearest to a given coordinate.
 * There's no interaction handled in this class.
 * This class is bound to an entity container.
 *
 * @author Andrew Mustun
 */
class RS_Information {
public:
    RS_Information(RS_EntityContainer& entityContainer);

	static bool isDimension(RS2::EntityType type);
	static bool isTrimmable(RS_Entity* e);
	static bool isTrimmable(RS_Entity* e1, RS_Entity* e2);

    RS_Vector getNearestEndpoint(const RS_Vector& point,
                                 double* dist = NULL) const;
    RS_Vector getNearestPointOnEntity(const RS_Vector& point,
	                                  bool onEntity=true, 
                                      double* dist = NULL,
                                      RS_Entity** entity=NULL) const;
    RS_Entity* getNearestEntity(const RS_Vector& point,
                                double* dist = NULL,
                                RS2::ResolveLevel level=RS2::ResolveAll) const;

    static RS_VectorSolutions getIntersection(RS_Entity* e1,
            RS_Entity* e2,
            bool onEntities = false);

    static RS_VectorSolutions getIntersectionLineLine(RS_Line* e1,
            RS_Line* e2);

    static RS_VectorSolutions getIntersectionLineArc(RS_Line* line,
            RS_Arc* arc);

    static RS_VectorSolutions getIntersectionArcArc(RS_Arc* e1,
            RS_Arc* e2);
    
	static RS_VectorSolutions getIntersectionLineEllipse(RS_Line* line,
            RS_Ellipse* ellipse);

    static bool isPointInsideContour(const RS_Vector& point,
                                     RS_EntityContainer* contour,
									 bool* onContour=NULL);
	
protected:
    RS_EntityContainer* container;
};



#endif
