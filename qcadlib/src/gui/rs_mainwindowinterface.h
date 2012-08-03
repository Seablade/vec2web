/****************************************************************************
** $Id: rs_mainwindowinterface.h,v 1.4 2004/12/17 04:31:59 andrew Exp $
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

#ifndef RS_MAINWINDOWINTERFACE_H
#define RS_MAINWINDOWINTERFACE_H

#include "rs_document.h"

#include "rs_graphicview.h"

/**
 * Interface for main application windows.
 */
class RS_MainWindowInterface {

public:
    RS_MainWindowInterface() {}
    virtual ~RS_MainWindowInterface() {}

    virtual RS_GraphicView* getGraphicView() = 0;
    virtual RS_Document* getDocument() = 0;

	virtual void createNewDocument(
		const RS_String& fileName = RS_String::null, RS_Document* doc=NULL) = 0;
	virtual void showSimulationControls() = 0;

};

#endif

