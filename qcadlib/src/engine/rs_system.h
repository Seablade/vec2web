/****************************************************************************
** $Id: rs_system.h,v 1.14 2004/12/15 01:38:12 andrew Exp $
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


#ifndef RS_SYSTEM_H
#define RS_SYSTEM_H

#include <iostream>

#include "rs_debug.h"
#include "rs_dir.h"
#include "rs_string.h"
#include "rs_stringlist.h"

#define RS_SYSTEM RS_System::instance()

/**
 * Class for some system methods such as file system operations.
 * Implemented as singleton. Use init to Initialize the class
 * before you use it.
 *
 * @author Andrew Mustun
 */
class RS_System {
protected:
    RS_System() {
        initialized = false;
    }

public:
    /**
     * @return Instance to the unique system object.
     */
    static RS_System* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_System();
        }
        return uniqueInstance;
    }

    void init(const RS_String& appName, const RS_String& appVersion, 
	          const RS_String& appDirName, const RS_String& appDir="");
	void initLanguageList();

    bool checkInit();
	bool createHomePath(const QString& p);

    /**
     * @return Users home directory.
     */
    RS_String getHomeDir() {
        return RS_Dir::homeDirPath();
    }

    /**
     * @return Current directory.
     */
    RS_String getCurrentDir() {
        return RS_Dir::currentDirPath();
    }

	/**
	 * @return Application directory.
	 */
	RS_String getAppDir() {
		return appDir;
	}

    /**
     * @return A list of absolute paths to all font files found.
     */
    RS_StringList getFontList() {
        RS_StringList ret = getFileList("fonts", "cxf");
		return ret;
    }
	
    /**
     * @return A list of absolute paths to all hatch pattern files found.
     */
    RS_StringList getPatternList() {
        RS_StringList ret = getFileList("patterns", "dxf");
		return ret;
    }

    /**
     * @return A list of absolute paths to all script files found.
     */
    RS_StringList getScriptList() {
        RS_StringList ret = getFileList("scripts/qsa", "qs");
		return ret;
    }
	
    /**
     * @return A list of absolute paths to all machine configuration files found.
     */
    RS_StringList getMachineList() {
        RS_StringList ret = getFileList("machines", "cxm");
		return ret;
    }
	
    /**
     * @return Absolute path to the documentation.
     */
    RS_String getDocPath() {
        RS_StringList lst = getDirectoryList("doc");
		return lst.first();
    }

	/**
	 * @return The application name.
	 */
	RS_String getAppName() {
		return appName;
	}

	/**
	 * @return The application version.
	 */
	RS_String getAppVersion() {
		return appVersion;
	}

    RS_StringList getFileList(const RS_String& subDirectory,
                              const RS_String& fileExtension);
							  
    RS_StringList getDirectoryList(const RS_String& subDirectory);
							  
	RS_StringList getLanguageList() {
		return languageList;
	}
	
	static RS_String languageToSymbol(const RS_String& lang);
	static RS_String symbolToLanguage(const RS_String& symb);

	static RS_String getEncoding(const RS_String& str);

	void loadTranslation(const RS_String& lang, const RS_String& langCmd);

    static bool test();

	/** Returns ISO code for given locale. Needed for win32 to convert 
	 from system encodings. */
	static QCString localeToISO(const QCString& locale);

protected:
    static RS_System* uniqueInstance;

    RS_String appName;
    RS_String appVersion;
    RS_String appDirName;
    RS_String appDir;
	
	//! List of available translations
	RS_StringList languageList;
	
    bool initialized;
};

#endif

