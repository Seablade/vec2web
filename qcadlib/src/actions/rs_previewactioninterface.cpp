/****************************************************************************
** $Id: rs_previewactioninterface.cpp,v 1.8 2004/01/31 23:31:24 andrew Exp $
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


#include "rs_previewactioninterface.h"


/**
 * Constructor.
 *
 * Sets the entity container on which the action class inherited 
 * from this interface operates.
 */
RS_PreviewActionInterface::RS_PreviewActionInterface(const char* name,
        RS_EntityContainer& container,
        RS_GraphicView& graphicView) :
RS_ActionInterface(name, container, graphicView) {

    RS_DEBUG->print("RS_PreviewActionInterface::RS_PreviewActionInterface: Setting up action with preview: \"%s\"", name);

    // preview is linked to the container for getting access to
    //   document settings / dictionary variables
    preview = new RS_Preview(&container);
    visible = false;

    /*
    //extension by ST for handling locked layers
    // 20040101: by andrew: only the selection of entities is 
    // disabled for locked layers
    RS_Document* doc = container.getDocument();
    if (doc!=NULL) {
    	RS_LayerList* layerList = doc->getLayerList();
    	if (layerList!=NULL) {
    		RS_Layer* activeLayer = layerList->getActive();
    		if (activeLayer!=NULL) {
    			if (activeLayer->isLocked()) {
    				finish();
    			}
    		}
    	}
}
    */

    RS_DEBUG->print("RS_PreviewActionInterface::RS_PreviewActionInterface: Setting up action with preview: \"%s\": OK", name);
}



/** Destructor */
RS_PreviewActionInterface::~RS_PreviewActionInterface() {
    delete preview;
}



void RS_PreviewActionInterface::init(int status) {
    RS_ActionInterface::init(status);
    //deletePreview();
    clearPreview();
}



void RS_PreviewActionInterface::finish() {
    RS_ActionInterface::finish();
    deletePreview();
    clearPreview();
}



void RS_PreviewActionInterface::suspend() {
    RS_ActionInterface::suspend();
    deletePreview();
    //clearPreview();
}



void RS_PreviewActionInterface::resume() {
    RS_ActionInterface::resume();
    drawPreview();
}



void RS_PreviewActionInterface::trigger() {
    RS_ActionInterface::trigger();
    deletePreview();
    clearPreview();
}



/**
 * Clears the preview by removing all entities in it.
 */
void RS_PreviewActionInterface::clearPreview() {
    preview->clear();
}



/**
 * Draws the preview on the screen.
 */
void RS_PreviewActionInterface::drawPreview() {
    if (!visible) {
        xorPreview();
    }
}



/**
 * Deletes the preview from the screen.
 */
void RS_PreviewActionInterface::deletePreview() {
    if (visible) {
        xorPreview();
    }
}



/**
 * Draws / deletes the current preview.
 */
void RS_PreviewActionInterface::xorPreview() {
    if (!preview->isEmpty()) {
        RS_Painter* painter = graphicView->createDirectPainter();
        painter->setPreviewMode();
        painter->setOffset(offset);
        graphicView->drawEntity(preview, false);
        graphicView->destroyPainter();
    }
    visible = !visible;
}

