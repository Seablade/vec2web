/*****************************************************************************
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
#include "dxflib/dl_entity.h"
#include "dxflib/dl_dxf.h"

extern "C" {
	#include <gd.h>
	#include <gdfontl.h>
	#include <g2.h>
	#include <g2_PS.h>
	#include <g2_X11.h>
}

/**
 * Default constructor.
 */
Vec2Web::Vec2Web ()
{
	strcpy (inputFile, "");
	strcpy (outputFile, "");
	maxSize.set (200,200);
	size.set (200,200);
	scaleUp = true;
	factor = 1.0;
	offset.set (0,0);
}


/**
 * Converts inputFile to outputFile.
 */
void
Vec2Web::convert ()
{
	// Read the DXF into graphic object
	DL_Dxf::in (inputFile, &graphic);
	//std::cout << graphic;
	
	// View in x11 if no outputfile was given.
	if (strlen(outputFile)==0) {
		output (F_X11);
		getchar ();
		return;
	}
	
	int len = strlen(outputFile);
	
	if (len<4) {	
		std::cout << "Can't find out file type of output file... please specify!";
	}
	else {
		if (len>4 && !strcmp(&outputFile[len-4], "wbmp")) {
			output (F_WBMP);
		}
		else if (len>3 && !strcmp(&outputFile[len-3], "png")) {
			output (F_PNG);
		}
		else if (len>2 && !strcmp(&outputFile[len-2], "ps")) {
			output (F_PS);
		}
	}
}


/**
 * Outputs an image from the graphic in the format descibed by 'format'.
 */
bool 
Vec2Web::output (Format format)
{
	bool ret=true;

	size.set ( graphic.getMax().x - graphic.getMin().x,
	           graphic.getMax().y - graphic.getMin().y );
			
	if (scaleUp || size.x>maxSize.x) 
		factor = maxSize.x / size.x;
	if (scaleUp || size.y>maxSize.y) 
		factor = min (maxSize.y / size.y, factor);
					
	size *= factor;
	size += DL_Vector (20,20);
	
	offset.set ( 10 - (int)(graphic.getMin().x * factor),
	             10 - (int)(graphic.getMin().y * factor) );

	switch (format) {
		case F_PNG:
		case F_JPEG:
		case F_WBMP:
			outputGd (format);
			break;
			
		case F_PS:
		case F_X11:
		case F_WIN:
			outputG2 (format);
			break;
		
		default:
			ret = false;
			break;
	}
	
	return ret;
}


/**
 * Outputs a png image from the graphic.
 */
bool
Vec2Web::outputGd (Format format)
{
	if (format!=F_PNG && format!=F_JPEG && format!=F_WBMP) return false;

	// Declare the image
	gdImagePtr im;
	// Declare output files
	FILE *fp;
	// Declare color indexes
	int black;
	int white;
	
	// Allocate the image:
	im = gdImageCreate ((int)size.x, (int)size.y);
	
	// Allocate the colors.
	// The first color in a new image will be the background color.
	white = gdImageColorAllocate(im, 255, 255, 255);
	black = gdImageColorAllocate(im, 0, 0, 0);
	
	for (DL_Entity* e = graphic.first(); e != 0; e = graphic.next())
	{
		switch (e->rtti ()) {
			case DL_ENTITY_LINE:
				gdImageLine (im, 
				             (int)transformX (e->getStartPoint().x),
										 (int)transformY (e->getStartPoint().y, true),
										 (int)transformX (e->getEndPoint().x),
										 (int)transformY (e->getEndPoint().y, true),
										 black);
				break;
				
			case DL_ENTITY_ARC: {
				DL_Arc* a = (DL_Arc*)e;
				
				gdImageArc (im,
				            (int)transformX (a->getCenter().x),
										(int)transformY (a->getCenter().y, true),
										(int)transformD (a->getRadius() * 2),
										(int)transformD (a->getRadius() * 2),
										(int)(360 - a->getAngle2()),
										(int)(360 - a->getAngle1()),
										black);
				} break;
				
			case DL_ENTITY_CIRCLE: {
				DL_Circle* c = (DL_Circle*)e;
				
				gdImageArc (im,
				            (int)transformX (c->getCenter().x),
										(int)transformY (c->getCenter().y, true),
										(int)transformD (c->getRadius() * 2),
										(int)transformD (c->getRadius() * 2),
										0, 360,
										black);
				} break;
				
			case DL_ENTITY_TEXT: {
				/*
				DL_Text* t = (DL_Text*)e;
				
				int brect[8];
				gdImageStringTTF (im,
				                  brect,
				                  black,
				                  "arial.ttf",
				                  transformD (t->getHeight ()),
				                  t->getAngle (),
				                  (int)transformX (t->getStartPoint ().x),
				                  (int)transformY (t->getStartPoint ().y),
				                  t->getText ());
				*/
				} break;
				
			default:
				break;
		}
		
	}
	
	// Open a file for writing.
	fp = fopen(outputFile, "wb");

	// Output the image to the disk file in the given format.
	switch (format) {
		case F_PNG:
			gdImagePng (im, fp);
			break;
			
		case F_JPEG:
			//gdImageJpeg (im, fp, -1);
			break;
			
		case F_WBMP:
			gdImageWBMP (im, black, fp);
			break;
			
		default:
			break;
	}

	// Close the file
	fclose (fp);

	// Destroy the image in memory
	gdImageDestroy (im);

	return true;
}


/**
 * Outputs the graphic into a format supported by the g2 library.
 *
 * \param handle The format handle of g2 created by a 2_open_* method.
 *               e.g. int handle = g2_open_GIF("simple.gif", 100, 100);
 */
bool
Vec2Web::outputG2 (Format format)
{
	if (format!=F_X11 && format!=F_PS && format!=F_WIN) return false;

	int handle;			// handle which identifies the image for g2

	switch (format) {
		case F_PS:
			handle = g2_open_PS (outputFile, g2_A4, g2_PS_land);
			break;
			
		case F_X11:
			handle = g2_open_X11 ((int)size.x, (int)size.y);
			break;
			
		default:
			handle = -1;
			break;
	}
	
	if (handle==-1) return false;

	for (DL_Entity* e = graphic.first(); e != 0; e = graphic.next())
	{
		switch (e->rtti ()) {
			case DL_ENTITY_LINE:
				g2_line (handle, 
				         transformX (e->getStartPoint().x), transformY (e->getStartPoint().y),
				         transformX (e->getEndPoint().x), transformY (e->getEndPoint().y) );
				break;
				
			case DL_ENTITY_ARC: {
				DL_Arc* a = (DL_Arc*)e;
				
				g2_arc (handle, 
				        transformX (a->getCenter().x), transformY (a->getCenter().y),
				        transformD (a->getRadius()), transformD (a->getRadius()),
				        a->getAngle1(), a->getAngle2() );
				} break;
				
			case DL_ENTITY_CIRCLE: {
				DL_Circle* a = (DL_Circle*)e;
				
				g2_ellipse (handle, 
				            transformX (a->getCenter().x), transformY (a->getCenter().y),
				            transformD (a->getRadius()), transformD (a->getRadius()) );
				} break;
		
			default:
				break;
		}
	}
	
	if (format!=F_X11 && format!=F_WIN) g2_close(handle);
                                                                                
	return true;                                                                  
}


/**
 * Transforms an x coordinate in the graphic to a x cordinate in a bitmap.
 */
double
Vec2Web::transformX (double x)
{
	return (x * factor + offset.x);
}


/**
 * Transforms an y coordinate in the graphic to a y cordinate in a bitmap.
 *
 * \param swap Swap the coordinate (used if the bitmap has the zero on the top)
 */
double
Vec2Web::transformY (double y, bool swap)
{
	return swap ? (size.y - (y * factor + offset.y)) :
	              (y * factor + offset.y);
}


/**
 * Transforms a distance in the graphic to a distance in a bitmap.
 */
double
Vec2Web::transformD (double d)
{
	return (d * factor);
}


// EOF
