/****************************************************************************
** $Id: rs_simplepython.h,v 1.2 2004/03/13 00:00:04 andrew Exp $
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

#ifndef RS_SIMPLEPYTHON_H
#define RS_SIMPLEPYTHON_H

#ifdef RS_OPT_SIMPLEPYTHON

#include "Python.h"

#include "rs_graphic.h"

#define RS_SIMPLEPYTHON RS_SimplePython::instance()

/**
 * Python scripting support. Obsolete.
 *
 * @author Andrew Mustun
 */
class RS_SimplePython {
private:
    RS_SimplePython() {
        graphic = NULL;
    }

public:
    static RS_SimplePython* instance();

    void setGraphic(RS_Graphic* g) {
        graphic = g;
    }

    RS_Graphic* getGraphic() {
        return graphic;
    }

    int launch(const RS_String& script);

private:
    static RS_SimplePython* uniqueInstance;

    RS_Graphic* graphic;
};



/**
 * Global method needed by the python lib for initialisation.
 */
void init_pyextension();

/**
 * Test method.
 */
long inc(long i);

/**
 * Adds a line to the current graphic document.
 */
void rsPyAddLine(double x1, double y1, double x2, double y2);

#endif

#endif
