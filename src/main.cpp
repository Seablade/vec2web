/*****************************************************************************
**  $Id: main.cpp,v 1.12 2003/09/24 22:58:45 andrew23 Exp $
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

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "vec2web.h"

#include "rs_system.h"
#include "rs_fontlist.h"
#include "rs_patternlist.h"

#include <qapplication.h>
#include <qprinter.h>

#define VW_APPNAME "vec2web"
#define VW_VERSION "0.0.5"
#define VW_DIRNAME "vec2web"

void usage();

int main(int argc, char** argv) {

    // Check given arguments:
    if (argc<2) {
        usage();
    }

    // Load DXF file into memory and convert it to whatever:
    else {
        int c=1;                     // argument counter
        double width=256;            // arg: width
        double height=256;           // arg: height
        bool blackWhite = false;     // arg: b/w instead of colors
        QPrinter::Orientation orientation = QPrinter::Landscape;
        QPrinter::PageSize pageSize = QPrinter::A4;

        // parse arguments:
        while (c<argc) {
            // width:
            if (c<argc-1 &&
                    (!strcmp(argv[c], "--maxx") ||
                     !strcmp(argv[c], "-x") ||
                     !strcmp(argv[c], "--width") ||
                     !strcmp(argv[c], "-w"))) {
                ++c;
                width = atof(argv[c]);
            }
            // height:
            else if (c<argc-1 &&
                     (!strcmp(argv[c], "--maxy") ||
                      !strcmp(argv[c], "-y") ||
                      !strcmp(argv[c], "--height") ||
                      !strcmp(argv[c], "-h"))) {
                ++c;
                height = atof(argv[c]);
            }
            // blackwhite:
            else if (!strcmp(argv[c], "--blackwhite") ||
                     !strcmp(argv[c], "-b")) {
                blackWhite = true;
            }
            // page orientation for PS
            else if (c<argc-1 &&
                     (!strcmp(argv[c], "--orientation") ||
                      !strcmp(argv[c], "-o"))) {
                ++c;
                if (!strcmp(argv[c], "landscape") ||
                        !strcmp(argv[c], "l")) {
                    orientation = QPrinter::Landscape;
                } else if (!strcmp(argv[c], "portrait") ||
                           !strcmp(argv[c], "p")) {
                    orientation = QPrinter::Portrait;
                } else {
                    std::cerr << "unknown paper orientation\n";
                    exit(1);
                }
            }
            // page size for PS
            else if (c<argc-1 &&
                     (!strcmp(argv[c], "--size") ||
                      !strcmp(argv[c], "-s"))) {
                ++c;
                if (!strcmp(argv[c], "a4") ||
                        !strcmp(argv[c], "A4")) {
                    pageSize = QPrinter::A4;
                } else if (!strcmp(argv[c], "a5") ||
                           !strcmp(argv[c], "A5")) {
                    pageSize = QPrinter::A5;
                } else {
                    std::cerr << "unknown paper size\n";
                    exit(2);
                }
            }

            ++c;
        }

        QApplication a(argc, argv);

    	RS_DEBUG->setLevel(RS_Debug::D_WARNING);
    	RS_SYSTEM->init(VW_APPNAME, VW_VERSION, VW_DIRNAME);
        RS_FONTLIST->init();
        RS_PATTERNLIST->init();

        Vec2Web v2w;
        v2w.setInputFile(argv[1]);
        if (argc>2) {
            v2w.setOutputFile(argv[2]);
        }
        v2w.setMaxSize(width, height);
        v2w.setScaleUp(true);
        v2w.setPageSize(pageSize);
        v2w.setOrientation(orientation);
        v2w.setBlackWhite(blackWhite);

        v2w.convert();
    }


}



void usage () {
    std::cout << "\nUsage: vec2web <input file> <output file> [options]\n";
    std::cout << "Where options are:\n";
    std::cout << "\t-x #      maximum x size for the output bitmap in pixel\n";
    std::cout << "\t-y #      maximum y size for the output bitmap in pixel\n";
    std::cout << "\t-b        black/white instead of using colors\n";
    std::cout << "\t-o [l|p]  orientation for PS output (landscape or portrait)\n";
    std::cout << "\t-s ..     page size for PS output (A4, A5)\n";

    //std::cout << "e.g. vec2web drawing.dxf\n";
    //std::cout << "\tshows the drawing in X11 or Win\n";
    std::cout << "\ne.g. vec2web drawing.dxf drawing.png\n";
    std::cout << "\tconverts drawing.dxf to a portable network graphic (PNG)\n\n";
}

// EOF
