/****************************************************************************
** $Id: rs_previewactioninterface.h,v 1.3 2003/07/03 08:44:58 andrew Exp $
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


#ifndef RS_PREVIEWACTIONINTERFACE_H
#define RS_PREVIEWACTIONINTERFACE_H

#include "rs_actioninterface.h"
#include "rs_painter.h"
#include "rs_preview.h"

/**
 * This is the interface that must be implemented for all 
 * action classes which need a preview. 
 *
 * @author Andrew Mustun
 */
class RS_PreviewActionInterface : public RS_ActionInterface {
public:
    RS_PreviewActionInterface(const char* name,
                              RS_EntityContainer& container,
                              RS_GraphicView& graphicView);
    virtual ~RS_PreviewActionInterface();

    virtual void init(int status=0);
    virtual void finish();
    virtual void suspend();
    virtual void resume();
    virtual void trigger();
    void clearPreview();
    void drawPreview();
    void deletePreview();
	
private:
    void xorPreview();

protected:
    /**
     * Preview that holds the entities to be previewed.
     */
    RS_Preview* preview;
    /**
     * Keeps track of the drawings in XOR mode.
     */
    bool visible;
    /**
     * Current offset of the preview.
     */
    RS_Vector offset;
};

#endif
