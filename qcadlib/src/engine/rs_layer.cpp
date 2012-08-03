/****************************************************************************
** $Id: rs_layer.cpp,v 1.7 2004/12/09 23:09:51 andrew Exp $
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


#include "rs_layer.h"

#include <iostream>

#include "rs_color.h"

#include "rs_math.h"


/**
 * Constructor.
 */
RS_Layer::RS_Layer(const RS_String& name) {
    setName(name);

    data.pen.setLineType(RS2::SolidLine);
    data.pen.setWidth(RS2::Width00);
    data.pen.setColor(Qt::black);
	data.frozen = false;
	data.locked = false;
}


/**
 * Dumps the layers data to stdout.
 */
std::ostream& operator << (std::ostream& os, const RS_Layer& l) {
    os << " name: " << l.getName().latin1()
    << " pen: " << l.getPen()
	<< " frozen: " << (int)l.isFrozen()
	<< " address: " << (int)(&l)
    << std::endl;
    return os;
}

