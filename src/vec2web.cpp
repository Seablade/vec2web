/*****************************************************************************
**  $Id: vec2web.cpp,v 1.24 2003/02/12 21:54:14 andrew23 Exp $
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
//#include <mingpp.h>
#include <rs.h>
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
        //outputMing(9);
        outputMing2(9);
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



bool Vec2Web::outputMing2(int compressLevel) {
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

    //SWFPainter p(movie);
    //gv.drawIt();

    movie->save(outputFile);

    return true;
#else

    std::cerr << "No SWF Support compiled.\n";
    return false;
#endif
}




/**
 * Outputs a SWF (Shockwave Flash) object from the graphic.
 *
 * \author Fabiano Weimar dos Santos (Xiru) <fabiano@x3ng.com.br>
 */
bool Vec2Web::outputMing(int compressLevel) {

#ifdef SWF_SUPPORT

    Ming_init();

    //SWFMovie *movie = new SWFMovie();

    //movie->setDimension( 100,100 );
    //movie->setBackground( 255, 255, 255 );   // White

    //SWFShape* shape = new SWFShape();
    /*
    shape->setLine(2, 1, 1, 1);
    shape->movePenTo(50,50);
    shape->drawLineTo(60,80);
    shape->drawLineTo(60,-60);
    shape->drawLineTo(-60,-60);
    shape->drawLineTo(60,60);
    */
    //movie->add(shape);
    //movie->nextFrame();
    //movie->save(outputFile);
    //delete shape;
    //delete movie;

    SWFMovie *movie = new SWFMovie();

    movie->setDimension( (float)maxSize.x, (float)maxSize.y );

    movie->setBackground( (int)255, (int)255, (int)255 );   // White

    for ( RS_Entity* e=graphic.firstEntity(); e!=0; e=graphic.nextEntity() ) {

        SWFShape *shape = new SWFShape();

        RS_Color c = e->getPen().getColor();
        //shape->setLine( swfw(e->getPen().getWidth()), (int)c.red(), (int)c.green(), (int)c.blue() );
        shape->setLine( 1, (int)c.red(), (int)c.green(), (int)c.blue() );
        //shape->setLine( 1, 0, 0, 0 );  // Debuging...

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

        case RS::EntityInsert:
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

    //movie->save(outputFile,compressLevel);
    movie->save(outputFile);

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
 * <draw x="200" y="200">
 *   <point x="123" y="123" \>
 *   <line x0="123" y0="123" x1="123" y1="123" \>
 *   <circle x="123" y="123" radius="123" \>
 *   <polyline closed="closed">
 *     <vertex x="123" y="123" \>
 *     <vertex x="123" y="123" bulge="1" \>
 *   </polyline>
 *   <arc x="123" y="123" radius="123" angle0="123" angle1="123" \>
 * </draw>
 * 
 * \author Fabiano Weimar dos Santos (Xiru) <fabiano@x3ng.com.br>
 */

bool Vec2Web::outputDXML() {

    FILE *dxml;

    dxml = fopen(outputFile, "w");

    fprintf(dxml, "<draw x=\"%i\" y=\"%i\">\n", (int)maxSize.x, (int)maxSize.y);

    for ( RS_Entity* e=graphic.firstEntity(); e!=0; e=graphic.nextEntity() ) {

        switch ( e->rtti() ) {

        case RS::EntityPoint: {
                RS_Point* p = (RS_Point*)e;
                fprintf(dxml, "  <point x=\"%f\" y=\"%f\" \\>\n",
                        transformX(p->getPos().x), transformY(p->getPos().y));
            }
            break;

        case RS::EntityLine: {
                RS_Line* l = (RS_Line*)e;
                fprintf(dxml, "  <line x0=\"%f\" y0=\"%f\" x1=\"%f\" y1=\"%f\" \\>\n",
                        transformX(l->getStartpoint().x), transformY(l->getStartpoint().y, true),
                        transformX(l->getEndpoint().x), transformY(l->getEndpoint().y, true));
            }
            break;

            //	case RS::EntityDimAligned:
            //	case RS::EntityDimLinear:
            //	case RS::EntityText:
        case RS::EntityPolyline: {
                RS_Polyline* l = (RS_Polyline*)e;
                bool first = true;
                if (! l->isClosed()) {
                    fprintf(dxml, "  <polyline>\n");
                } else {
                    fprintf(dxml, "  <polyline closed=\"closed\">\n");
                }
                for ( RS_Entity* v=l->firstEntity(RS::ResolveNone); v!=NULL;
                        v=l->nextEntity(RS::ResolveNone) ) {
                    if (v->rtti()==RS::EntityLine) {
                        RS_Line* l = (RS_Line*)v;
                        if (first) {
                            fprintf(dxml, "    <vertex x=\"%f\" y=\"%f\" \\>\n",
                                    transformX(l->getStartpoint().x), transformY(l->getStartpoint().y, true));
                            first = false;
                        }
                        fprintf(dxml, "    <vertex x=\"%f\" y=\"%f\" \\>\n",
                                transformX(l->getEndpoint().x), transformY(l->getEndpoint().y, true));
                    } else if (v->rtti()==RS::EntityArc) {
                        RS_Arc* a = (RS_Arc*)v;
                        if (first) {
                            fprintf(dxml, "    <vertex x=\"%f\" y=\"%f\" \\>\n",
                                    transformX(a->getStartpoint().x), transformY(a->getStartpoint().y, true));
                            first = false;
                        }
                        fprintf(dxml, "    <vertex x=\"%f\" y=\"%f\" bulge=\"%f\" \\>\n",
                                transformX(a->getEndpoint().x), transformY(a->getEndpoint().y, true), a->getBulge());
                    }
                }
                fprintf(dxml, "  </polyline>\n");
            }
            break;

        case RS::EntityCircle: {
                RS_Circle* c = (RS_Circle*)e;
                fprintf(dxml, "  <circle x=\"%f\" y=\"%f\" radius=\"%f\" \\>\n",
                        transformX(c->getCenter().x), transformY(c->getCenter().y, true), transformD(c->getRadius()));
            }
            break;

        case RS::EntityArc: {
                RS_Arc* a = (RS_Arc*)e;
                fprintf(dxml, "  <arc x=\"%f\" y=\"%f\" radius=\"%f\" angle0=\"%f\" angle1=\"%f\" \\>\n",
                        transformX(a->getCenter().x), transformY(a->getCenter().y, true), transformD(a->getRadius()),
                        a->getAngle1(), a->getAngle2());
            }
            break;

        default:
            break;
        }

    }

    fprintf(dxml, "</draw>\n");

    fclose(dxml);

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
