/****************************************************************************
** $Id: rs_color.h,v 1.2 2003/06/11 06:55:57 andrew Exp $
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


#ifndef RS_COLOR_H
#define RS_COLOR_H

#include <qcolor.h>

#include "rs_flags.h"


//! Color defined by layer not entity
//#define C_BY_LAYER     0x00000001
//! Color defined by block not entity
//#define C_BY_BLOCK     0x00000002

/**
 * Color class.
 *
 * @author Andrew Mustun
 */
class RS_Color: public QColor, public RS_Flags {
public:
    RS_Color() : QColor(), RS_Flags() {}
    RS_Color(int r, int g, int b) : QColor(r, g, b), RS_Flags() {}
    RS_Color(const QColor& c) : QColor(c), RS_Flags() {}
    RS_Color(const RS_Color& c) : QColor(c), RS_Flags() {
        setFlags(c.getFlags());
    }
    RS_Color(unsigned int f) : QColor(), RS_Flags(f) {}

    /** @return A copy of this color without flags. */
    RS_Color stripFlags() const {
        return RS_Color(red(), green(), blue());
    }

    /** @return true if the color is defined by layer. */
    bool isByLayer() const {
        return getFlag(RS2::FlagByLayer);
    }

    /** @return true if the color is defined by block. */
    bool isByBlock() const {
        return getFlag(RS2::FlagByBlock);
    }


    RS_Color& operator = (const RS_Color& c) {
        setRgb(c.red(), c.green(), c.blue());
        setFlags(c.getFlags());

        return *this;
    }

    bool operator == (const RS_Color& c) const {
        return (red()==c.red() &&
                green()==c.green() &&
                blue()==c.blue() &&
                getFlags()==c.getFlags());
    }

    friend std::ostream& operator << (std::ostream& os, const RS_Color& c) {
        os << " color: " << c.name().latin1()
        << " flags: " << (c.getFlag(RS2::FlagByLayer) ? "RS2::FlagByLayer " : "")
        << (c.getFlag(RS2::FlagByBlock) ? "RS2::FlagByBlock " : "");
        return os;
    }
};

#endif

