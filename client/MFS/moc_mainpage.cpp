/****************************************************************************
** Meta object code from reading C++ file 'mainpage.h'
**
** Created: Tue Apr 16 10:04:34 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainpage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   10,    9,    9, 0x05,
      70,   56,    9,    9, 0x05,
     124,  103,    9,    9, 0x05,
     166,  159,    9,    9, 0x05,
     202,  185,    9,    9, 0x05,
     226,    9,    9,    9, 0x05,
     258,  241,    9,    9, 0x05,
     306,  290,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     331,    9,    9,    9, 0x0a,
     352,    9,    9,    9, 0x0a,
     372,    9,    9,    9, 0x0a,
     394,    9,    9,    9, 0x0a,
     426,    9,    9,    9, 0x0a,
     444,    9,    9,    9, 0x0a,
     462,    9,    9,    9, 0x0a,
     482,    9,    9,    9, 0x0a,
     502,    9,    9,    9, 0x0a,
     532,    9,    9,    9, 0x0a,
     563,  552,    9,    9, 0x0a,
     590,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainPage[] = {
    "MainPage\0\0hostName,port\0"
    "sgnalConnectServer(QString,int)\0"
    "path,userName\0sgnalUploadFile(QString,QString)\0"
    "fileId,size,filePath\0"
    "sgnalDownloadFile(int,int,QString)\0"
    "fileId\0sgnalEnterDir(int)\0fileId,moveFlags\0"
    "sgnalMoveFile(int,bool)\0sgnalBackDir()\0"
    "dirName,userName\0sgnalCreateDir(QString,QString)\0"
    "fileId,fileType\0sgnalDeleteFile(int,int)\0"
    "slotConnectClicked()\0slotUploadClicked()\0"
    "slotDownloadClicked()\0"
    "slotEnterFile(QListWidgetItem*)\0"
    "slotMoveClicked()\0slotBackClicked()\0"
    "slotCreateClicked()\0slotDeleteClicked()\0"
    "slotUpdateData(QList<MFile>*)\0"
    "slotAddFile(MFile*)\0type,state\0"
    "slotOperateResult(int,int)\0"
    "slotItemClicked(QListWidgetItem*)\0"
};

const QMetaObject MainPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainPage,
      qt_meta_data_MainPage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainPage))
        return static_cast<void*>(const_cast< MainPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sgnalConnectServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: sgnalUploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: sgnalDownloadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: sgnalEnterDir((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sgnalMoveFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: sgnalBackDir(); break;
        case 6: sgnalCreateDir((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: sgnalDeleteFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: slotConnectClicked(); break;
        case 9: slotUploadClicked(); break;
        case 10: slotDownloadClicked(); break;
        case 11: slotEnterFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: slotMoveClicked(); break;
        case 13: slotBackClicked(); break;
        case 14: slotCreateClicked(); break;
        case 15: slotDeleteClicked(); break;
        case 16: slotUpdateData((*reinterpret_cast< QList<MFile>*(*)>(_a[1]))); break;
        case 17: slotAddFile((*reinterpret_cast< MFile*(*)>(_a[1]))); break;
        case 18: slotOperateResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: slotItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MainPage::sgnalConnectServer(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainPage::sgnalUploadFile(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainPage::sgnalDownloadFile(int _t1, int _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainPage::sgnalEnterDir(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainPage::sgnalMoveFile(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainPage::sgnalBackDir()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MainPage::sgnalCreateDir(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainPage::sgnalDeleteFile(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
