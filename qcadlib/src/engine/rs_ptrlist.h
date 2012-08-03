/****************************************************************************
** $Id: rs_ptrlist.h,v 1.5 2003/12/02 18:59:02 andrew Exp $
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


#ifndef RS_PTRLIST_H
#define RS_PTRLIST_H

#if QT_VERSION>=0x030000
#include <qptrlist.h>

#define RS_PtrList QPtrList
#define RS_PtrListIterator QPtrListIterator
#else
#include <qlist.h>

#define RS_PtrList QList
#define RS_PtrListIterator QListIterator
#endif


#endif
