/****************************************************************************
** $Id: rs_painteradapter.h,v 1.2 2004/04/04 22:48:00 andrew Exp $
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


#ifndef RS_PAINTERADAPTER_H
#define RS_PAINTERADAPTER_H

#include "rs_painter.h"



/**
 * An abstract adapter class for painter object. The methods in this class are empty. 
 * This class exists as convenience for creating painter objects.
 */
class RS_PainterAdapter: public RS_Painter {
public:
    RS_PainterAdapter() : RS_Painter() {}
    virtual ~RS_PainterAdapter() {}
	
	virtual void moveTo(int , int ) {}
	virtual void lineTo(int , int ) {}

    virtual void drawGridPoint(const RS_Vector&) {}
    virtual void drawPoint(const RS_Vector&) {}
    virtual void drawLine(const RS_Vector&, const RS_Vector&) {}
    virtual void drawRect(const RS_Vector&, const RS_Vector&) {}
    virtual void drawArc(const RS_Vector&, double,
                         double, double,
                         const RS_Vector&, const RS_Vector&,
                         bool ) {}
    virtual void drawArc(const RS_Vector&, double,
                         double, double,
                         bool ) {}
    void createArc(QPointArray& ,
                   const RS_Vector&, double,
                   double, double,
                   bool ) {}
    virtual void drawCircle(const RS_Vector&, double) {}
    virtual void drawEllipse(const RS_Vector&,
                             double, double,
                             double,
                             double, double,
                             bool ) {}
	virtual void drawImg(RS_Img& , const RS_Vector&, 
			double, const RS_Vector&,
			int, int, int, int) {}

    virtual void drawTextH(int, int, int, int,
                           const RS_String&) {}
    virtual void drawTextV(int, int, int, int,
                           const RS_String&) {}

    virtual void fillRect(int, int, int, int,
                          const RS_Color&) {}

    virtual void fillTriangle(const RS_Vector&,
                              const RS_Vector&,
                              const RS_Vector&) {}

    virtual void setPreviewPen() {}
    virtual RS_Pen getPen() { return RS_Pen(); }
    virtual void setPen(const RS_Pen&) {}
    virtual void setPen(const RS_Color&) {}
    virtual void setPen(int, int, int) {}
    virtual void disablePen() {}
	virtual void setBrush(const RS_Color&) {}
	virtual void drawPolygon(const RS_PointArray& ) {}
	virtual void erase() {}
	virtual int getWidth() { return 0; }
	virtual int getHeight() { return 0; }

    virtual void setXORMode() {}
    virtual void setNormalMode() {}

    virtual void setClipRect(int, int, int, int) {}
    virtual void resetClipping() {}

};

#endif
