/****************************************************************************
** $Id: rs_settings.cpp,v 1.8 2004/03/10 21:46:17 andrew Exp $
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


#include "rs_settings.h"
#include <iostream>

RS_Settings* RS_Settings::uniqueInstance = NULL;


RS_Settings::RS_Settings() {
    initialized = false;
    companyKey = "";
    appKey = "";
    group = "";
    cache.setAutoDelete(true);
}

/**
 * Initialisation.
 *
 * @param companyKey String that identifies the company. Must start
 *        with a "/". E.g. "/RibbonSoft"
 * @param appKey String that identifies the application. Must start
 *        with a "/". E.g. "/QCad2"
 */
void RS_Settings::init(const RS_String& companyKey,
                       const RS_String& appKey) {

    group = "";
    this->appKey = appKey;
    this->companyKey = companyKey;

    //insertSearchPath(QSettings::Windows, companyKey + appKey);
    //insertSearchPath(QSettings::Unix, "/usr/share/");
    initialized = true;
}


/**
 * Destructor
 */
RS_Settings::~RS_Settings() {}



void RS_Settings::beginGroup(const RS_String& group) {
    this->group = group;
}

void RS_Settings::endGroup() {
    this->group = "";
}

bool RS_Settings::writeEntry(const RS_String& key, int value) {
    RS_String s = RS_String("%1").arg(value);
    return writeEntry(key, s);
}

bool RS_Settings::writeEntry(const RS_String& key, double value) {
    RS_String s = RS_String("%1").arg(value);
    return writeEntry(key, s);
}

bool RS_Settings::writeEntry(const RS_String& key, const RS_String& value) {
#if QT_VERSION>=0x030000
    bool ret;
    QSettings s(QSettings::Ini);
    s.insertSearchPath(QSettings::Windows, companyKey);

    ret = s.writeEntry(QString("%1%2%3").arg(appKey).arg(group).arg(key), value);

	addToCache(key, value);
    return ret;
#else

    return true;
#endif

}

RS_String RS_Settings::readEntry(const RS_String& key,
                                 const RS_String& def,
                                 bool* ok) {

#if QT_VERSION>=0x030000
    // lookup:
    RS_String ret = readEntryCache(key);
    if (ret==RS_String::null) {
        QSettings s(QSettings::Ini);
    	s.insertSearchPath(QSettings::Windows, companyKey);

        ret = s.readEntry(QString("%1%2%3").arg(appKey).arg(group).arg(key), 
			def, ok);
		
		addToCache(key, ret);
    }

    return ret;
#else

    return def;
#endif

}

int RS_Settings::readNumEntry(const RS_String& key, int def, bool* ok) {
#if QT_VERSION>=0x030000
	
    // lookup:
    RS_String sret = readEntryCache(key);
    if (sret==RS_String::null) {
    	int ret;
    	QSettings s(QSettings::Ini);
    	s.insertSearchPath(QSettings::Windows, companyKey);

        ret = s.readNumEntry(QString("%1%2%3").arg(appKey).arg(group).arg(key), 
			def, ok);
		addToCache(key, RS_String("%1").arg(ret));
		return ret;
	}
	else {
    	return sret.toInt();
	}
#else

    return def;
#endif

}


RS_String RS_Settings::readEntryCache(const RS_String& key) {
	RS_String* s = cache.find(key);
	if (s==NULL) {
		return RS_String::null;
	}
	else {
		return *s;
	}
}


void RS_Settings::addToCache(const RS_String& key, const RS_String& value) {
	cache.replace(key, new RS_String(value));
}
