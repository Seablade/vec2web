/*****************************************************************************
**  $Id: swfpainter.h,v 1.12 2003/09/02 20:31:10 andrew23 Exp $
**
**  This is part of the QCad Qt GUI
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License (version 2) as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#ifndef SWF_PAINTER_H
#define SWF_PAINTER_H

#include "rs_color.h"
#include "rs_graphicview.h"
#include "rs_painter.h"

#ifdef SWF_SUPPORT
#include <mingpp.h>


/**
 * The SWF implementation of a painter. It can draw objects such as
 * lines or arcs in an SWF Movie. All coordinates are movie coordinates
 * and have nothing to do with the graphic view.
 */
class SWFPainter: public RS_Painter {
public:
    SWFPainter(SWFMovie* mov);
    virtual ~SWFPainter();
    virtual void drawGridPoint(const RS_Vector& /*p*/) {}
    virtual void drawPoint(const RS_Vector& p);
    virtual void drawLine(const RS_Vector& p1, const RS_Vector& p2);
    virtual void drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         const RS_Vector& p1, const RS_Vector& p2,
                         bool reversed);
    virtual void drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         bool reversed);
    virtual void drawCircle(const RS_Vector& /*cp*/, double /*radius*/) {}
    virtual void drawEllipse(const RS_Vector& cp,
                             double radius1, double radius2,
                             double angle,
                             double a1, double a2,
                             bool reversed);
    virtual void drawTextH(int /*x1*/, int /*y1*/,
                           int /*x2*/, int /*y2*/,
                           const QString& /*text*/) {}
    virtual void drawTextV(int /*x1*/, int /*y1*/,
                           int /*x2*/, int /*y2*/,
                           const QString& /*text*/) {}
    virtual void fillRect(int /*x1*/, int /*y1*/, int /*w*/, int /*h*/,
                          const RS_Color& /*col*/) {}
    virtual void fillTriangle(const RS_Vector& /*p1*/,
                              const RS_Vector& /*p2*/,
                              const RS_Vector& /*p3*/) {}
    virtual void setPreviewPen() {}
    virtual RS_Pen getPen();
    virtual void setPen(const RS_Pen& pen);
    virtual void setPen(const RS_Color& color);
    virtual void setPen(int r, int g, int b);
	virtual void disablePen() {}
	virtual void setBrush(const RS_Color& /*color*/) {}
	virtual void drawPolygon(const RS_PointArray& /*a*/) {}
    virtual void setXORMode() {}
    virtual void setNormalMode() {}
    virtual void setClipRect(int /*x*/, int /*y*/, int /*w*/, int /*h*/) {}
    virtual void resetClipping() {}
private:
    SWFMovie* movie;
    int width;
    int colr,colg,colb;
};

#endif
#endif

