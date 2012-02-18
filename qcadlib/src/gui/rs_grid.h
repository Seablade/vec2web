/****************************************************************************
** $Id: rs_grid.h,v 1.4 2003/12/29 23:04:00 andrew Exp $
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


#ifndef RS_GRID_H
#define RS_GRID_H

#include "rs_graphicview.h"
#include "rs_vector.h"

/**
 * This class represents a grid. Grids can be drawn on graphic
 * views and snappers can snap to the grid points.
 *
 * @author Andrew Mustun
 */
class RS_Grid {
public:
    RS_Grid(RS_GraphicView* graphicView);
    ~RS_Grid();

    void update();
	
	/**
	 * @return Array of all visible grid points.
	 */
    RS_Vector* getPoints() {
        return pt;
    }
	
	/**
	 * @return Number of visible grid points.
	 */
    int count() {
        return number;
    }

	/**
	 * @return Current grid spacing.
	 */
	//double getSpacing() {
	//	return spacing;
	//}
	
	/**
	 * @return Current meta grid spacing.
	 */
	//double getMetaSpacing() {
	//	return metaSpacing;
	//}

	/**
	 * @return Grid info for status widget.
	 */
	RS_String getInfo() {
		return RS_String("%1 / %2").arg(spacing).arg(metaSpacing);
	}

	/**
	 * @return Meta grid positions in X.
	 */
	double* getMetaX() {
		return metaX;
	}
	
	/**
	 * @return Number of visible meta grid lines in X.
	 */
    int countMetaX() {
        return numMetaX;
    }
	
	/**
	 * @return Meta grid positions in Y.
	 */
	double* getMetaY() {
		return metaY;
	}
	
	/**
	 * @return Number of visible meta grid lines in Y.
	 */
    int countMetaY() {
        return numMetaY;
    }

protected:
    //! Graphic view this grid is connected to.
    RS_GraphicView* graphicView;
	
	//! Current grid spacing
	double spacing;
	//! Current meta grid spacing
	double metaSpacing;
	
    //! Pointer to array of grid points
    RS_Vector* pt;
    //! Number of points in the array
    int number;
	//! Meta grid positions in X
	double* metaX;
	//! Number of meta grid lines in X
	int numMetaX;
	//! Meta grid positions in Y
	double* metaY;
	//! Number of meta grid lines in Y
	int numMetaY;
};

#endif
