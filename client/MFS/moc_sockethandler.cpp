/****************************************************************************
** Meta object code from reading C++ file 'sockethandler.h'
**
** Created: Tue Apr 16 10:04:35 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sockethandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sockethandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SocketHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      49,   47,   14,   14, 0x05,
      76,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,   98,   14,   14, 0x0a,
     156,  142,   14,   14, 0x0a,
     208,  187,   14,   14, 0x0a,
     248,  241,   14,   14, 0x0a,
     265,   14,   14,   14, 0x0a,
     295,  278,   14,   14, 0x0a,
     341,  325,   14,   14, 0x0a,
     381,  364,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SocketHandler[] = {
    "SocketHandler\0\0sgnlUpdateRecord(QList<MFile>*)\0"
    ",\0sgnlOperateResult(int,int)\0"
    "sgnlAddRecord(MFile*)\0hostName,port\0"
    "sltConnectServer(QString,int)\0"
    "path,userName\0sltUploadFile(QString,QString)\0"
    "fileId,size,filePath\0"
    "sltDownloadFile(int,int,QString)\0"
    "fileId\0sltEnterDir(int)\0sltBackDir()\0"
    "dirName,userName\0sltCreateDir(QString,QString)\0"
    "fileId,fileType\0sltDeleteFile(int,int)\0"
    "fileId,moveFlags\0sltMoveFile(int,bool)\0"
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
        case 0: sgnlUpdateRecord((*reinterpret_cast< QList<MFile>*(*)>(_a[1]))); break;
        case 1: sgnlOperateResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: sgnlAddRecord((*reinterpret_cast< MFile*(*)>(_a[1]))); break;
        case 3: sltConnectServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: sltUploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: sltDownloadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: sltEnterDir((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: sltBackDir(); break;
        case 8: sltCreateDir((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: sltDeleteFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: sltMoveFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SocketHandler::sgnlUpdateRecord(QList<struct MFile> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SocketHandler::sgnlOperateResult(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SocketHandler::sgnlAddRecord(MFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
