/****************************************************************************
** $Id: rs_fileio.h,v 1.4 2004/04/17 10:22:57 andrew Exp $
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

#ifndef RS_FILEIO_H
#define RS_FILEIO_H

#include "rs_entitycontainer.h"
#include "rs_filterinterface.h"

#define RS_FILEIO RS_FileIO::instance()

/**
 * API Class for importing files. 
 *
 * @author Andrew Mustun
 */
class RS_FileIO {
protected:
    RS_FileIO() {}
	
public:
    /**
     * @return Instance to the unique import object.
     */
    static RS_FileIO* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_FileIO();
        }
        return uniqueInstance;
    }
	
    /**
     * Registers a new import filter.
     */
	void registerFilter(RS_FilterInterface* f) {
		filterList.append(f);
	}

    /**
     * @return List of registered filters.
     */
	RS_PtrList<RS_FilterInterface> getFilterList() {
		return filterList;
	}

	/**
	 * @return Filter which can import the given file type.
	 */
	RS_FilterInterface* getImportFilter(RS2::FormatType t) {
		for (RS_FilterInterface* f=filterList.first(); 
			f!=NULL; f=filterList.next()) {
		
			if (f->canImport(t)) {
				return f;
			}
		}

		return NULL;
	}
	
	/**
	 * @return Filter which can export the given file type.
	 */
	RS_FilterInterface* getExportFilter(RS2::FormatType t) {
		for (RS_FilterInterface* f=filterList.first(); 
			f!=NULL; f=filterList.next()) {
		
			if (f->canExport(t)) {
				return f;
			}
		}

		return NULL;
	}

    bool fileImport(RS_Graphic& graphic, const RS_String& file, 
		RS2::FormatType type = RS2::FormatUnknown);
		
    bool fileExport(RS_Graphic& graphic, const RS_String& file,
		RS2::FormatType type = RS2::FormatUnknown);

	RS2::FormatType detectFormat(const RS_String& file);

protected:
    static RS_FileIO* uniqueInstance;
    RS_PtrList<RS_FilterInterface> filterList;
}
;

#endif
