/*****************************************************************************
**  $Id: vec2web.cpp,v 1.27 2003/02/14 00:08:33 xiru Exp $
**
**  This is part of the vec2web tool
**  Copyright (C) 2000 Andrew Mustun, Causeway Technologies
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

#include "vec2web.h"
#include "graphicview.h"
#include "dl_creationinterface.h"
#include "dl_dxf.h"
#include "rs_creation.h"
#include "rs_color.h"
#include "rs_graphic.h"
#include "rs_import.h"
#include "rs_system.h"
#include "rs.h"
#include "dxmlpainter.h"

#include <qimage.h>
#include <ctype.h>

#ifdef SWF_SUPPORT
#include "swfpainter.h"
#endif


/**
 * Default constructor.
 */
Vec2Web::Vec2Web () {
    strcpy(inputFile, "");
    strcpy(outputFile, "");
    maxSize.set(200,200);
    size.set(200,200);
    scaleUp = true;
    factor = 1.0;
    offset.set(0,0);
    RS_SYSTEM->init("vec2web", "vec2web");
}


/**
 * Converts inputFile to outputFile.
 */
void Vec2Web::convert() {

    // Read the DXF into graphic object
    RS_Import import(graphic);
    import.fileImport(inputFile);

    // Default file format
    if (strlen(outputFile)==0) {
        output("PNG");
        return;
    }

    int len = strlen(outputFile);
    int i=len-2;
    while (i>0 && outputFile[i]!='.') {
        --i;
    }

    char extension[16];
    strncpy(extension, &outputFile[i+1], 15);
    for (i=0; i<(int)strlen(extension); ++i) {
        extension[i] = toupper(extension[i]);
    }

    output(extension);

}


/**
 * Outputs an image from the graphic in the format descibed by 'format'.
 */
bool Vec2Web::output(const char* format) {
    bool ret=true;

    size.set(graphic.getMax().x - graphic.getMin().x,
             graphic.getMax().y - graphic.getMin().y);

    if (scaleUp || size.x>maxSize.x) {
        factor = maxSize.x / size.x;
    }
    if (scaleUp || size.y>maxSize.y) {
        factor = min(maxSize.y / size.y, factor);
    }

    size *= factor;
    size += RS_Vector(20,20);

    offset.set(10 - (int)(graphic.getMin().x * factor),
               10 - (int)(graphic.getMin().y * factor));

    if ( ! strcmp(format, "SWF") ) {
        outputMing(9);
    } else if ( ! strcmp(format, "DXML") ) {
        outputDXML();
    } else {
        outputQt(format);
    }

    return ret;
}


/**
 * Outputs a png image from the graphic.
 */
bool Vec2Web::outputQt(const char* format) {

    bool ret = false;

    QPixmap* buffer = new QPixmap((int)maxSize.x, (int)maxSize.y);
    QG_Painter* painter = new QG_Painter(buffer);
    painter->setBackgroundColor(RS_Color(255,255,255));
    painter->eraseRect(0,0, (int)maxSize.x, (int)maxSize.y);

    GraphicView gv((int)maxSize.x, (int)maxSize.y, painter);

    gv.setContainer(&graphic);
    gv.zoomAuto();
    gv.drawEntity(&graphic, false, true);

    QImageIO iio;
    QImage img;
    img = *buffer;
    iio.setImage(img);
    iio.setFileName(outputFile);
    iio.setFormat(format);
    if (iio.write()) {
        ret = true;
    }

    // GraphicView deletes painter
    painter->end();
    delete buffer;

    return ret;
}


bool Vec2Web::outputMing(int compressLevel) {
	
#ifdef SWF_SUPPORT

    Ming_init();

    SWFMovie *movie = new SWFMovie();
    movie->setDimension((float)(maxSize.x), (float)(maxSize.y));
    movie->setBackground((int)255, (int)255, (int)255);   // White

    SWFPainter* painter= new SWFPainter(movie);
    GraphicView gv((int)maxSize.x, (int)maxSize.y, painter);
    gv.setContainer(&graphic);
    gv.zoomAuto();
    gv.drawEntity(&graphic, false, true);

    movie->save(outputFile, compressLevel);

    return true;
    
#else

    std::cerr << "No SWF Support compiled.\n";
    return false;
    
#endif
    
}


/**
 * Outputs a DXML file (a minimalistic XML representation of the DXF file format).
 *
 * Example:
 *
 * <draw>
 *   <point x="123" y="123" \>
 *   <line x0="123" y0="123" x1="123" y1="123" \>
 *   <circle x="123" y="123" radius="123" \>
 *   <arc x="123" y="123" radius="123" angle0="123" angle1="123" \>
 * </draw>
 * 
 * \author Fabiano Weimar dos Santos (Xiru) <fabiano@x3ng.com.br>
 */

bool Vec2Web::outputDXML() {

    DXMLPainter* painter= new DXMLPainter(outputFile);
    GraphicView gv((int)maxSize.x, (int)maxSize.y, painter);
    gv.setContainer(&graphic);
    gv.zoomAuto();
    gv.drawEntity(&graphic, false, true);

    return true;

}


/**
 * Transforms an x coordinate in the graphic to a x cordinate in a bitmap.
 */
double
Vec2Web::transformX (double x) {
    return (x * factor + offset.x);
}


/**
 * Transforms an y coordinate in the graphic to a y cordinate in a bitmap.
 *
 * \param swap Swap the coordinate (used if the bitmap has the zero on the top)
 */
double
Vec2Web::transformY (double y, bool swap) {
    return swap ? (size.y - (y * factor + offset.y)) :
           (y * factor + offset.y);
}


/**
 * Transforms a distance in the graphic to a distance in a bitmap.
 */
double
Vec2Web::transformD (double d) {
    return (d * factor);
}


// EOF
