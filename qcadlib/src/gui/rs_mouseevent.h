/****************************************************************************
** $Id: rs_mouseevent.h,v 1.2 2003/06/11 06:56:01 andrew Exp $
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


#ifndef RS_MOUSEEVENT_H
#define RS_MOUSEEVENT_H

#include <qevent.h>

#define RS_MouseEvent QMouseEvent

/**
 * Events which can be triggered for every action.
 */
//enum RS_MouseButton { LEFT, MIDDLE, RIGHT, NONE };

/**
 * Mouse Events.
 */
/*
class RS_MouseEvent {
public:
    RS_MouseEvent(int x, int y, RS_MouseButton button) {
        this->x = x;
        this->y = y;
        this->button = button;
    }
 
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    RS_MouseButton getButton() {
        return button;
    }
 
protected:
    int x;
    int y;
    RS_MouseButton button;
};
*/

#endif
