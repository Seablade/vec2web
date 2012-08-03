/****************************************************************************
** $Id: rs_dialogfactory.h,v 1.6 2004/07/07 22:51:46 andrew Exp $
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


#ifndef RS_DIALOGFACTORY_H
#define RS_DIALOGFACTORY_H

#include "rs_dialogfactoryinterface.h"
#include "rs_dialogfactoryadapter.h"
#include "rs_debug.h"


#define RS_DIALOGFACTORY RS_DialogFactory::instance()->getFactoryObject()

/**
 * Interface for objects that can create and show dialogs.
 */
class RS_DialogFactory {

private:
    RS_DialogFactory();

public:
    virtual ~RS_DialogFactory() {}

    static RS_DialogFactory* instance();

	void setFactoryObject(RS_DialogFactoryInterface* fo);
	RS_DialogFactoryInterface* getFactoryObject();

	void commandMessage(const RS_String& m);

private:
	RS_DialogFactoryInterface* factoryObject;
	RS_DialogFactoryAdapter factoryAdapter;
	static RS_DialogFactory* uniqueInstance;
};


#endif
