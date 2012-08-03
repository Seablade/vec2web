/****************************************************************************
** $Id: rs_selection.h,v 1.9 2004/04/05 23:12:06 andrew Exp $
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

#ifndef RS_SELECTION_H
#define RS_SELECTION_H

#include "rs_entitycontainer.h"
#include "rs_graphicview.h"



/**
 * API Class for selecting entities. 
 * There's no interaction handled in this class.
 * This class is connected to an entity container and
 * can be connected to a graphic view.
 *
 * @author Andrew Mustun
 */
class RS_Selection {
public:
    RS_Selection(RS_EntityContainer& entityContainer,
                 RS_GraphicView* graphicView=NULL);

    void selectSingle(RS_Entity* e);
    void selectAll(bool select=true);
    void deselectAll() {
        selectAll(false);
    }
    void invertSelection();
    void selectWindow(const RS_Vector& v1, const RS_Vector& v2,
                      bool select=true, bool cross=false);
    void deselectWindow(const RS_Vector& v1, const RS_Vector& v2) {
        selectWindow(v1, v2, false);
    }
    void selectIntersected(const RS_Vector& v1, const RS_Vector& v2,
                      bool select=true);
    void deselectIntersected(const RS_Vector& v1, const RS_Vector& v2) {
		selectIntersected(v1, v2, false);
	}
    void selectContour(RS_Entity* e);
	
    void selectLayer(RS_Entity* e);
    void selectLayer(const RS_String& layerName, bool select=true);
    void deselectLayer(RS_String& layerName) {
		selectLayer(layerName, false);
	}

protected:
    RS_EntityContainer* container;
    RS_Graphic* graphic;
    RS_GraphicView* graphicView;
};

#endif
