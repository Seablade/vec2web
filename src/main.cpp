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

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "vec2web.h"

void usage ();


int main(int argc, char** argv) {
	
	// Check given arguments:
	if (argc<2) {
		usage ();
	}
	
	// Load DXF file into memory and convert it to whatever:
	else {
		// Proccess parameters:
		int c=1;
		double maxX=256;
		double maxY=256;
		
		while( c<argc ) {
		
			if( c<argc-1 && !strcmp (argv[c], "--maxx") || !strcmp (argv[c], "-x") ) {
				++c;
				maxX = atof (argv[c]);
			}
			else if( c<argc-1 && !strcmp (argv[c], "--maxy") || !strcmp (argv[c], "-y") ) {
				++c;
				maxY = atof (argv[c]);
			}
			
			++c;
		}
	
		Vec2Web v2w;
		v2w.setInputFile (argv[1]);
		if (argc>2) v2w.setOutputFile (argv[2]);
		v2w.setMaxSize (maxX, maxY);
		v2w.setScaleUp (true);
		v2w.convert ();
	}
	

}



void usage () {
	std::cout << "\nUsage: vec2web input.dxf [output.png|output.ps|output.wbmp] [options]\n";
	std::cout << "Where options are:\n";
	std::cout << "\t-x #  maximum x size for the output bitmap\n";
	std::cout << "\t-y #  maximum y size for the output bitmap\n\n";
	
	std::cout << "e.g. vec2web drawing.dxf\n";
	std::cout << "\tshows the drawing in X11 or Win\n";
	std::cout << "e.g. vec2web drawing.dxf drawing.png\n";
	std::cout << "\tconverts drawing.dxf to a portable network graphic (PNG)\n\n";
}

// EOF
