/****************************************************************************
** $Id: rs_python.cpp,v 1.5 2003/09/30 22:50:17 andrew Exp $
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

#include "rs_python.h"

#ifdef RS_OPT_PYTHON

//
// This is exported from the Boost::Python library declarations
// that are declared inside rs_python_wrappers.cpp.
//
extern "C" void initqcad();

/**
 * The unique instance of the Python scripting engine
 */
RS_Python* RS_Python::uniqueInstance = NULL;

/**
 * Constructor
 */
RS_Python::RS_Python()
{
    graphic = NULL;
    Py_Initialize();
    initqcad();
}

/**
 *  Gets the one and only RS_Python instance
 *  (creates a new one on first call only)
 *
 *  @return Pointer to the single instance of this
 * singleton class
 */
RS_Python* RS_Python::instance() {
    if(uniqueInstance==NULL) {
        uniqueInstance = new RS_Python;
    }
    return uniqueInstance;
}


/**
 * Launches the given script.
 */
int RS_Python::launch(const RS_String& script) {
    PyObject *modname, *mod, *mdict, *func, *rslt;
    //Py_SetProgramName(argv[0]);

    modname = PyString_FromString(script);
    mod = PyImport_Import(modname);
    if (mod) {
        //printf( "mod\n");
        mdict = PyModule_GetDict(mod);

        // Borrowed reference to start function
        func = PyDict_GetItemString(mdict, "start");
        if (func) {
            //printf( "func\n");
            if (PyCallable_Check(func)) {
                //printf("calling..\n");
                rslt = PyObject_CallFunction(func, "(s)", "noparam");
                //printf("calling ok\n");
                if (rslt) {
		    // The result value is currently not used
                    Py_XDECREF(rslt);
                } else
		{
		    // Give user some feed back what went wrong
	            printf("*** PYTHON RUNTIME ERROR ***\n");
		    PyErr_Print();
		}
            }
        } else {
            printf("no such function: start\n");
        }
        Py_XDECREF(mod);
    } else {
        printf("*** ERROR LOADING SCRIPT '%s' ***\n", script.latin1());
	PyErr_Print();	
    }
    Py_XDECREF(modname);
    //Py_Finalize();
    return 0;
}

#endif
