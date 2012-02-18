/****************************************************************************
** $Id: rs_creation.h,v 1.13 2003/09/16 00:01:54 andrew Exp $
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


#ifndef RS_CREATION_H
#define RS_CREATION_H

#include "rs_entitycontainer.h"
#include "rs_line.h"
#include "rs_polyline.h"
#include "rs_insert.h"
#include "rs_image.h"


/**
 * Data needed to insert library items.
 */
struct RS_LibraryInsertData {
	RS_String file;
	RS_Vector insertionPoint;
	double factor;
	double angle;
};


/**
 * Class for the creation of new entities.
 * This class is bound to an entity container in which the
 * entities are stored. 
 *
 * @author Andrew Mustun
 */
class RS_Creation {
public:
    RS_Creation(RS_EntityContainer* container,
                RS_GraphicView* graphicView=NULL,
                bool handleUndo=true);

    RS_Entity* createParallelThrough(const RS_Vector& coord,
                              int number,
                              RS_Entity* e);

    RS_Entity* createParallel(const RS_Vector& coord,
                              double distance,
                              int number,
                              RS_Entity* e);

    RS_Line* createParallelLine(const RS_Vector& coord,
                                double distance, int number,
                                RS_Line* e);

    RS_Arc* createParallelArc(const RS_Vector& coord,
                              double distance, int number,
                              RS_Arc* e);

    RS_Circle* createParallelCircle(const RS_Vector& coord,
                                    double distance, int number,
                                    RS_Circle* e);

    RS_Line* createBisector(const RS_Vector& coord1,
                            const RS_Vector& coord2,
                            double length,
                            int num,
                            RS_Line* l1,
                            RS_Line* l2);

    RS_Line* createTangent1(const RS_Vector& coord,
                            const RS_Vector& point,
                            RS_Entity* circle);

    RS_Line* createTangent2(const RS_Vector& coord,
                            RS_Entity* circle1,
                            RS_Entity* circle2);

    RS_Line* createLineRelAngle(const RS_Vector& coord,
                                RS_Entity* entity,
                                double angle,
                                double length);

    RS_Line* createPolygon(const RS_Vector& center,
                           const RS_Vector& corner,
                           int number);

    RS_Line* createPolygon2(const RS_Vector& corner1,
                            const RS_Vector& corner2,
                            int number);

    RS_Insert* createInsert(RS_InsertData& data);
	
    RS_Image* createImage(RS_ImageData& data);

    RS_Block* createBlock(const RS_BlockData& data,
                          const RS_Vector& referencePoint,
                          const bool remove);
						  
    RS_Insert* createLibraryInsert(RS_LibraryInsertData& data);

    //void createPoint(const RS_Vector& p);
    //void createLine2P(const RS_Vector& p1, const RS_Vector& p2);
    //void createRectangle(const RS_Vector& e1, const RS_Vector& e2);
    //RS_Polyline* createPolyline(const RS_Vector& p);

protected:
    RS_EntityContainer* container;
    RS_Graphic* graphic;
    RS_Document* document;
    RS_GraphicView* graphicView;
    bool handleUndo;
};

#endif
