/****************************************************************************
** $Id: rs_filtercxf.h,v 1.6 2004/01/25 01:05:41 andrew Exp $
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


#ifndef RS_FILTERCXF_H
#define RS_FILTERCXF_H

#include <fstream>

#include "rs_filterinterface.h"

/**
 * This format filter class can import and export CXF (CAM Expert Font) files.
 *
 * @author Andrew Mustun
 */
class RS_FilterCXF : public RS_FilterInterface {
public:
    RS_FilterCXF();
    ~RS_FilterCXF() {}
	
	/**
	 * @return RS2::FormatCXF.
	 */
	//RS2::FormatType rtti() {
	//	return RS2::FormatCXF;
	//}
	
    /*virtual bool canImport(RS2::FormatType t) {
		return (t==RS2::FormatCXF);
	}
	
    virtual bool canExport(RS2::FormatType t) {
		return (t==RS2::FormatCXF);
	}*/

    virtual bool fileImport(RS_Graphic& g, const RS_String& file, RS2::FormatType /*type*/);

    virtual bool fileExport(RS_Graphic& g, const RS_String& file, RS2::FormatType /*type*/);

    void stream(std::ofstream& fs, double value);
};

#endif
