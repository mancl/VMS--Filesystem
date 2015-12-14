/****************************************************************************
** Meta object code from reading C++ file 'sockethandler.h'
**
** Created: Wed Apr 10 16:45:18 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sockethandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sockethandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SocketHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   14,   14,   14, 0x0a,
      71,   66,   14,   14, 0x0a,
     101,   94,   14,   14, 0x0a,
     122,   94,   14,   14, 0x0a,
     139,   14,   14,   14, 0x0a,
     160,  152,   14,   14, 0x0a,
     182,   94,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SocketHandler[] = {
    "SocketHandler\0\0sgnlUpdateRecord(QList<mFile>*)\0"
    "sltConnectServer()\0path\0sltUploadFile(QString)\0"
    "fileId\0sltDownloadFile(int)\0"
    "sltEnterDir(int)\0sltBackDir()\0dirName\0"
    "sltCreateDir(QString)\0sltDeleteFile(int)\0"
};

const QMetaObject SocketHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SocketHandler,
      qt_meta_data_SocketHandler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SocketHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SocketHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SocketHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SocketHandler))
        return static_cast<void*>(const_cast< SocketHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int SocketHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sgnlUpdateRecord((*reinterpret_cast< QList<mFile>*(*)>(_a[1]))); break;
        case 1: sltConnectServer(); break;
        case 2: sltUploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: sltDownloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sltEnterDir((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: sltBackDir(); break;
        case 6: sltCreateDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: sltDeleteFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SocketHandler::sgnlUpdateRecord(QList<struct mFile> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
