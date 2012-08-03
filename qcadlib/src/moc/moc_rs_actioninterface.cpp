/****************************************************************************
** RS_ActionInterface meta object code from reading C++ file 'rs_actioninterface.h'
**
** Created: Thu Feb 16 17:02:07 2012
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../actions/rs_actioninterface.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *RS_ActionInterface::className() const
{
    return "RS_ActionInterface";
}

QMetaObject *RS_ActionInterface::metaObj = 0;
static QMetaObjectCleanUp cleanUp_RS_ActionInterface( "RS_ActionInterface", &RS_ActionInterface::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString RS_ActionInterface::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RS_ActionInterface", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString RS_ActionInterface::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RS_ActionInterface", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* RS_ActionInterface::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"RS_ActionInterface", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_RS_ActionInterface.setMetaObject( metaObj );
    return metaObj;
}

void* RS_ActionInterface::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "RS_ActionInterface" ) )
	return this;
    if ( !qstrcmp( clname, "RS_Snapper" ) )
	return (RS_Snapper*)this;
    return QObject::qt_cast( clname );
}

bool RS_ActionInterface::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool RS_ActionInterface::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool RS_ActionInterface::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool RS_ActionInterface::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
