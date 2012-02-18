/****************************************************************************
** $Id: rs_dialogfactoryadapter.h,v 1.6 2004/08/03 14:38:11 andrew Exp $
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


#ifndef RS_DIALOGFACTORYADAPTER_H
#define RS_DIALOGFACTORYADAPTER_H

#include "rs_dialogfactoryinterface.h"
#include "rs_block.h"
#include "rs_layer.h"

class RS_BlockList;
class RS_LayerList;


/**
 * Adapter for dialog factory interface.
 * Used when no factory object was set.
 */
class RS_DialogFactoryAdapter : public RS_DialogFactoryInterface {
public:
    RS_DialogFactoryAdapter() {}
    virtual ~RS_DialogFactoryAdapter() {}
    virtual void requestPreviousMenu() {}
    virtual void requestWarningDialog(const RS_String& ) {}
    virtual RS_GraphicView* requestNewDocument(const RS_String& = RS_String::null, 
			RS_Document* =NULL) { return NULL; }
    virtual void requestSimulationControls() {}
    virtual RS_Layer* requestNewLayerDialog(
        RS_LayerList* = NULL) { return NULL; }
    virtual RS_Layer* requestLayerRemovalDialog(
        RS_LayerList* = NULL) { return NULL; }
    virtual RS_Layer* requestEditLayerDialog(
        RS_LayerList* = NULL) { return NULL; }
    virtual RS_BlockData requestNewBlockDialog(RS_BlockList* ) 
		{ return RS_BlockData(); }
    virtual RS_Block* requestBlockRemovalDialog(
        RS_BlockList* ) { return NULL; }
    virtual RS_BlockData requestBlockAttributesDialog(
        RS_BlockList* ) { return RS_BlockData(); }
    virtual void requestEditBlockWindow(
        RS_BlockList* ) {}
	virtual void closeEditBlockWindow(RS_Block* ) {}
    virtual RS_String requestImageOpenDialog() { return ""; }
    virtual void requestOptions(RS_ActionInterface* , 
		bool , bool = false) {}
    virtual void requestSnapDistOptions(double& , bool ) {}
    virtual bool requestAttributesDialog(RS_AttributesData& ,
		RS_LayerList& ) { return false; }
    virtual bool requestMoveDialog(RS_MoveData& ) { return false; }
    virtual bool requestRotateDialog(RS_RotateData& ) { return false; }
    virtual bool requestScaleDialog(RS_ScaleData& ) { return false; }
    virtual bool requestMirrorDialog(RS_MirrorData& ) { return false; }
    virtual bool requestMoveRotateDialog(RS_MoveRotateData& ) { return false; }
    virtual bool requestRotate2Dialog(RS_Rotate2Data& ) { return false; }
    virtual void requestToolBar(RS2::ToolBarId ) {}
    virtual void requestToolBarSelect(RS_ActionInterface* ,
                                      RS2::ActionType ) {}
    virtual bool requestModifyEntityDialog(RS_Entity* ) { return false; }
    virtual bool requestTextDialog(RS_Text* ) { return false; }
    virtual bool requestHatchDialog(RS_Hatch* ) { return false; }
    virtual void requestOptionsGeneralDialog() {}
    virtual void requestOptionsDrawingDialog(RS_Graphic& ) {}
#ifdef RS_CAM
    virtual bool requestCamOptionsDialog(RS_Graphic& ) { printf("fake\n"); return false; }
#endif
    virtual void updateCoordinateWidget(const RS_Vector& ,
										const RS_Vector& ,
										bool =false) {}
    virtual void updateMouseWidget(const RS_String& ,
                                   const RS_String& ) {}
    virtual void updateSelectionWidget(int ) {}
    virtual void commandMessage(const RS_String& ) {}
	virtual bool isAdapter() { return true; }
};

#endif
