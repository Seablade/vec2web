/*****************************************************************************
**  $Id: dxmlpainter.h,v 1.6 2003/05/18 00:08:40 andrew23 Exp $
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

#ifndef DXML_PAINTER_H
#define DXML_PAINTER_H

#include "rs_color.h"
#include "rs_graphicview.h"
#include "rs_painter.h"


/**
 * The DXML implementation of a painter. It will represent as a XML
 * file the graphic representation of a DXF file.
 */
class DXMLPainter: public RS_Painter {
public:
    DXMLPainter(char* dxml);
    virtual ~DXMLPainter();
    virtual void drawGridPoint(const RS_Vector&) {}
    virtual void drawPoint(const RS_Vector& p);
    virtual void drawLine(const RS_Vector& p1, const RS_Vector& p2);
    virtual void drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         const RS_Vector& p1, const RS_Vector& p2,
                         bool reversed);
    virtual void drawArc(const RS_Vector& cp, double radius,
                         double a1, double a2,
                         bool reversed);
    virtual void drawCircle(const RS_Vector&, double /*radius*/) {}
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
    virtual void setClipRect(int /*x*/, int /*y*/,
                             int /*w*/, int /*h*/) {}
    virtual void resetClipping() {}
private:
    FILE* dxml;
    int width;
    int colr,colg,colb;
    void StartDXML();
    void EndDXML();
};

#endif

