/*****************************************************************************
**  $Id: vec2web.cpp,v 1.20 2003/02/11 20:00:16 xiru Exp $
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

#include <qimage.h>

#include <ctype.h>

#ifdef SWF_SUPPORT
#include <mingpp.h>
#include <rs.h>
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

    // View in x11 if no outputfile was given.
    if (strlen(outputFile)==0) {
        output("X11");
        getchar();
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

    if ( strcmp(format, "SWF") ) {
        outputQt(format);
    } else {
        outputMing(9);
    }

    return ret;
}


/**
 * Outputs a png image from the graphic.
 */
bool Vec2Web::outputQt(const char* format) {
    GraphicView gv((int)maxSize.x, (int)maxSize.y);
    gv.setContainer(&graphic);
    gv.zoomAuto();
    gv.drawEntity(&graphic, false, true);
    QPixmap* buffer = gv.getBuffer();

    if (buffer!=NULL) {
        QImageIO iio;
        QImage img;
        img = *buffer;
        iio.setImage(img);
        iio.setFileName(outputFile);
        iio.setFormat(format);
        if (iio.write()) {
            return true;
        }
    }

    return false;
}


/**
 * Wrapper for SWF line width conversion.
 *
 * \author Fabiano Weimar dos Santos (Xiru) <fabiano@x3ng.com.br>
 */

unsigned short Vec2Web::swfw(const RS::LineWidth w) {
    unsigned short sw = (unsigned short) ( w / 2.4 );
    if ( sw < 1 ) {
        sw = 1;
    }
    if ( sw > 10 ) {
        sw = 10;
    }
    return sw;
}


/**
 * Outputs a SWF (Shockwave Flash) object from the graphic.
 *
 * \author Fabiano Weimar dos Santos (Xiru) <fabiano@x3ng.com.br>
 */

bool Vec2Web::outputMing(int compressLevel) {

#ifdef SWF_SUPPORT

    Ming_init();

    SWFMovie *movie = new SWFMovie();

    movie->setDimension( (float)size.x, (float)size.y );

    movie->setBackground( (int)255, (int)255, (int)255 );   // White

    for ( RS_Entity* e=graphic.firstEntity(); e!=0; e=graphic.nextEntity() ) {

        SWFShape *shape = new SWFShape();

        //RS_Color c = e->getPen().getColor();
        //shape->setLine( swfw(e->getPen().getWidth()), (int)c.red(), (int)c.green(), (int)c.blue() );
        shape->setLine( 1, 0, 0, 0 );  // Debuging...

        switch ( e->rtti() ) {
		
        case RS::EntityPoint: {
                RS_Point* p = (RS_Point*)e;
                shape->movePenTo( (float)transformX(p->getPos().x - 1),
                                  (float)transformY(p->getPos().y, true) );
                shape->drawLineTo( (float)transformX(p->getPos().x + 1),
                                   (float)transformY(p->getPos().y, true) );
                shape->movePenTo( (float)transformX(p->getPos().x),
                                  (float)transformY(p->getPos().y - 1, true) );
                shape->drawLineTo( (float)transformX(p->getPos().x),
                                   (float)transformY(p->getPos().y + 1, true) );
                movie->add( shape );
            }
            break;

        case RS::EntityLine: {
                RS_Line* l = (RS_Line*)e;
                shape->movePenTo( (float)transformX(l->getStartpoint().x),
                                  (float)transformY(l->getStartpoint().y, true) );
                shape->drawLineTo( (float)transformX(l->getEndpoint().x),
                                   (float)transformY(l->getEndpoint().y, true) );
                movie->add( shape );
            }
            break;

	case RS::EntityDimAligned: 
	case RS::EntityDimLinear: 
	case RS::EntityText: 
        case RS::EntityPolyline: {
                RS_Polyline* l = (RS_Polyline*)e;
                bool first = true;
                for ( RS_Entity* v=l->firstEntity(RS::ResolveNone); v!=NULL;
                      v=l->nextEntity(RS::ResolveNone) ) {
                    if (v->rtti()==RS::EntityLine) {
                        RS_Line* l = (RS_Line*)v;
                        if (first) {
                            shape->movePenTo( (float)transformX(l->getStartpoint().x),
                                              (float)transformY(l->getStartpoint().y, true) );
                        }
                        shape->drawLineTo( (float)transformX(l->getEndpoint().x),
                                           (float)transformY(l->getEndpoint().y, true) );
                    } else if (v->rtti()==RS::EntityArc) {
                        RS_Arc* a = (RS_Arc*)v;
                        shape->movePenTo( (float)transformX(a->getCenter().x),
                                          (float)transformY(a->getCenter().y, true) );
                        float a1, a2;
                        a1 = a->isReversed() ? a->getAngle2() : a->getAngle1();
                        a2 = a->isReversed() ? a->getAngle1() : a->getAngle2();
                        a1 = (float)( ( M_PI * 2 - a1 ) * ARAD + 90 );
                        a2 = (float)( ( M_PI * 2 - a2 ) * ARAD + 90 );
                        if ( a2 > a1 )
                            a1 += 360;
                        shape->drawArc( (float)transformD(a->getRadius()), a2, a1 );
                        shape->movePenTo( (float)transformX(a->getEndpoint().x),
                                          (float)transformY(a->getEndpoint().y, true) );
                    }
                    first = false;
                }
                movie->add( shape );
            }
            break;

        case RS::EntityCircle: {
                RS_Circle* c = (RS_Circle*)e;
                shape->movePenTo( (float)transformX(c->getCenter().x),
                                  (float)transformY(c->getCenter().y, true) );
                shape->drawCircle( (float)transformD(c->getRadius()) );
                movie->add( shape );
            }
            break;

        case RS::EntityArc: {
                RS_Arc* a = (RS_Arc*)e;
                shape->movePenTo( (float)transformX(a->getCenter().x),
                                  (float)transformY(a->getCenter().y, true) );
                float a1, a2;
                a1 = (float)( ( M_PI * 2 - a->getAngle1() ) * ARAD + 90 );
                a2 = (float)( ( M_PI * 2 - a->getAngle2() ) * ARAD + 90 );
                if ( a2 > a1 )
                    a1 += 360;
                shape->drawArc( (float)transformD(a->getRadius()), a2, a1 );
                movie->add( shape );
            }
            break;

        default:
            break;
        }

    }

    movie->save(outputFile,compressLevel);

    return true;

#else

    std::cerr << "No SWF Support compiled.\n";
    return false;
    
#endif

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
