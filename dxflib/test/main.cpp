/*
 * @file main.cpp
 */

/*****************************************************************************
**  $Id: main.cpp,v 1.4 2004/07/21 22:43:29 andrew Exp $
**
**  This is part of the dxflib library
**  Copyright (C) 2000-2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "dl_dxf.h"
#include "dl_creationadapter.h"

#include "test_creationclass.h"

void usage();


/*
 * @brief Main function for DXFLib test program.
 *
 * @param argc Number of delimited items on command line,
 *		including program name.
 * @param argv Pointer to array of command line items
 *
 * @retval 0 if missing input file argument or
 *		file couldn't be opened
 * @retval 1 if file opened
 */
int main(int argc, char** argv) {

    // Check given arguments:
    if (argc<2) {
        usage();
        return 0;
    }

	//DL_Dxf::test();

    // Load DXF file into memory:
    std::cout << "Reading file " << argv[1] << "...\n";
    Test_CreationClass creationClass;
    DL_Dxf dxf;
    if (!dxf.in(argv[1], &creationClass)) { // if file open failed
        std::cerr << argv[1] << " could not be opened.\n";
        return 0;
    }
	
    return 1; // file could be opened

}



/*
 * @brief Prints error message if file name not specified as command
 * line argument.
 */
void usage() {
    std::cout << "\nUsage: test <DXF file>\n\n";
}

// EOF
