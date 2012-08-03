/****************************************************************************
** $Id: rs_layerlist.h,v 1.7 2004/04/09 19:56:42 andrew Exp $
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


#ifndef RS_LAYERLIST_H
#define RS_LAYERLIST_H

//#include <vector.h>


#include "rs_layer.h"
#include "rs_layerlistlistener.h"
#include "rs_entity.h"
#include "rs_ptrlist.h"

/**
 * A list of layers.
 *
 * @author Andrew Mustun
 */
class RS_LayerList {
public:
    RS_LayerList();
    virtual ~RS_LayerList() {}

    void clear();

    /**
     * @return Number of layers in the list.
     */
    uint count() const {
        return layers.count();
    }

    /**
     * @return Layer at given position or NULL if i is out of range.
     */
    RS_Layer* at(uint i) {
        return layers.at(i);
    }

    void activate(const RS_String& name, bool notify = false);
    void activate(RS_Layer* layer, bool notify = false);
    //! @return The active layer of NULL if no layer is activated.
    RS_Layer* getActive() {
        return activeLayer;
    }
    virtual void add(RS_Layer* layer);
    virtual void remove(RS_Layer* layer);
    virtual void edit(RS_Layer* layer, const RS_Layer& source);
    RS_Layer* find(const RS_String& name);
    int getIndex(const RS_String& name);
    int getIndex(RS_Layer* layer);
    void toggle(const RS_String& name);
    void toggle(RS_Layer* layer);
    void toggleLock(RS_Layer* layer);
    void freezeAll(bool freeze);
    //! @return First layer of the list.
    //RS_Layer* firstLayer() {
    //    return layers.first();
    //}
    /** @return Next layer from the list after
     * calling firstLayer() or nextLayer().
     */
    //RS_Layer* nextLayer() {
    //    return layers.next();
    //}

    void addListener(RS_LayerListListener* listener);
    void removeListener(RS_LayerListListener* listener);
	
	/**
	 * Sets the layer lists modified status to 'm'.
	 */
	void setModified(bool m) {
		modified = m;
	}
	
	/**
	 * @retval true The layer list has been modified.
	 * @retval false The layer list has not been modified.
	 */
    virtual bool isModified() const {
        return modified;
    }

    friend std::ostream& operator << (std::ostream& os, RS_LayerList& l);

private:
    //! layers in the graphic
    RS_PtrList<RS_Layer> layers;
    //! List of registered LayerListListeners
    RS_PtrList<RS_LayerListListener> layerListListeners;
    //! Currently active layer
    RS_Layer* activeLayer;
    /** Flag set if the layer list was modified and not yet saved. */
    bool modified;
};

#endif
