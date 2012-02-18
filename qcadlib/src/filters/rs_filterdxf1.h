/****************************************************************************
** $Id: rs_filterdxf1.h,v 1.7 2004/02/29 00:29:32 andrew Exp $
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


#ifndef RS_FILTERDXF1_H
#define RS_FILTERDXF1_H

#include <fstream>

#include "rs_filterinterface.h"
#include "rs_file.h"

/**
 * This format filter class can import and export old DXF files
 * from QCad 1.x.
 *
 * This is legacy code from QCad 1.x.
 *
 * @author Andrew Mustun
 */
class RS_FilterDXF1 : public RS_FilterInterface {
public:
    RS_FilterDXF1();
    ~RS_FilterDXF1() {}

	/**
	 * @return RS2::FormatDXF1.
	 */
	//RS2::FormatType rtti() {
	//	return RS2::FormatDXF1;
	//}

	/*
    virtual bool canImport(RS2::FormatType t) {
		return (t==RS2::FormatDXF1);
	}
	
    virtual bool canExport(RS2::FormatType t) {
		return false;
	}*/

    virtual bool fileImport(RS_Graphic& g, const RS_String& file, RS2::FormatType /*type*/);

    virtual bool fileExport(RS_Graphic& /*g*/, const RS_String& /*file*/, 
		RS2::FormatType /*type*/) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "Exporting of QCad 1.x file not implemented");
		return false;
    }

    bool readFromBuffer();

    void    reset();
    void    resetBufP();

    void    setBufP(int _fBufP);
    int     getBufP() {
        return fBufP;
    }
    void    delBuffer();
    void    dos2unix();

    RS_String getBufLine();
    char*   getBufLineCh();
    char*   getBuf() {
        return fBuf;
    }
    void    setBuf(char* _buf) {
        fBuf=_buf;
    }
    void    setFSize(uint _s) {
        fSize=_s;
    }
    void    copyBufFrom(const char* _buf);
    bool    gotoBufLine(char* _lstr);
    bool    gotoBufLineString(char* _lstr);

    void    replaceBinaryBytesBy(char _c);
    void    separateBuf(char _c1=13,
                        char _c2=10,
                        char _c3=0,
                        char _c4=0);
    void    removeComment(char _fc='(',
                          char _lc=')');

    bool    readFileInBuffer(char* _name, int _bNum=-1);
    bool    readFileInBuffer(int _bNum=-1);

    void     strDecodeDxfString(RS_String& str);
    bool     mtCompFloat(double _v1, double _v2, double _tol=1.0e-6);

protected:
    /** Pointer to the graphic we currently operate on. */
    RS_Graphic* graphic;
    FILE*   fPointer;         // File pointer
    char*   fBuf;             // Filebuffer
    int     fBufP;            // Filebuffer-Pointer (walks through 'fBuf')
    uint    fSize;            // Filesize
    bool    dosFile;          // File is in DOS-format
    int       numElements;
    RS_String name;
    RS_File  file;
}
;

#endif
