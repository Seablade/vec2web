/****************************************************************************
** $Id: rs_coordinateevent.h,v 1.3 2004/02/18 16:03:00 andrew Exp $
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


#ifndef RS_COORDINATEEVENT_H
#define RS_COORDINATEEVENT_H


/**
 * Coordinate Events.
 */
class RS_CoordinateEvent {
public:
	/**
	 * @param pos coordinate
	 * @param abs true: absolute coordinate, false: relative coordinate
	 */
    RS_CoordinateEvent(const RS_Vector& pos) {
		this->pos = pos;
    }
 
    /**
	 * @return the position of the event in real graphic measures.
	 */
    RS_Vector getCoordinate() {
        return pos;
    }
 
protected:
    RS_Vector pos;
};

#endif
