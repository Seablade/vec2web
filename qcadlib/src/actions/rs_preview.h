/****************************************************************************
** $Id: rs_preview.h,v 1.6 2003/09/09 23:16:17 andrew Exp $
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


#ifndef RS_PREVIEW_H
#define RS_PREVIEW_H

#include "rs_entitycontainer.h"

class RS_Entity;
class RS_GraphicView;
class RS_Vector;
class RS_MouseEvent;

/**
 * This class supports previewing. The RS_Snapper class uses
 * an instance of RS_Preview to preview entities, ranges, 
 * lines, arcs, ... on the fly.
 *
 * @author Andrew Mustun
 */
class RS_Preview : public RS_EntityContainer {
public:
    RS_Preview(RS_EntityContainer* parent=NULL);
    ~RS_Preview();
	
    virtual void addEntity(RS_Entity* entity);
	void addCloneOf(RS_Entity* entity);
    virtual void addSelectionFrom(RS_EntityContainer& container);
    virtual void addAllFrom(RS_EntityContainer& container);
    virtual void addStretchablesFrom(RS_EntityContainer& container,
	       const RS_Vector& v1, const RS_Vector& v2);

private:
	int maxEntities;
};

#endif
