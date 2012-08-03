/****************************************************************************
** $Id: rs_layerlistlistener.h,v 1.2 2003/06/11 06:55:58 andrew Exp $
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


#ifndef RS_LAYERLISTLISTENER_H
#define RS_LAYERLISTLISTENER_H

#include "rs_layer.h"

/**
 * This class is an interface for classes that are interested in
 * knowing about changes in the layer list. 
 */
class RS_LayerListListener {
public:
    RS_LayerListListener() {}
    virtual ~RS_LayerListListener() {}

    /**
     * Called when the active layer changes.
     */
    virtual void layerActivated(RS_Layer*) {}

    /**
     * Called when a new layer is added to the list.
     */
    virtual void layerAdded(RS_Layer*) {}

    /**
     * Called when a layer is removed from the list.
     */
    virtual void layerRemoved(RS_Layer*) {}

    /**
     * Called when a layer's attributes are modified.
     */
    virtual void layerEdited(RS_Layer*) {}

    /**
     * Called when a layer's visibility is toggled. 
     */
    virtual void layerToggled(RS_Layer*) {}
}
;

#endif
