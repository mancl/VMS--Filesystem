/****************************************************************************
** Meta object code from reading C++ file 'mainpage.h'
**
** Created: Wed Apr 10 16:45:15 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainpage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      36,   31,    9,    9, 0x05,
      68,   61,    9,    9, 0x05,
      91,   61,    9,    9, 0x05,
     110,    9,    9,    9, 0x05,
     133,  125,    9,    9, 0x05,
     157,   61,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     178,    9,    9,    9, 0x0a,
     210,    9,    9,    9, 0x0a,
     230,    9,    9,    9, 0x0a,
     252,    9,    9,    9, 0x0a,
     270,    9,    9,    9, 0x0a,
     288,    9,    9,    9, 0x0a,
     308,    9,    9,    9, 0x0a,
     328,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainPage[] = {
    "MainPage\0\0sgnalConnectServer()\0path\0"
    "sgnalUploadFile(QString)\0fileId\0"
    "sgnalDownloadFile(int)\0sgnalEnterDir(int)\0"
    "sgnalBackDir()\0dirName\0sgnalCreateDir(QString)\0"
    "sgnalDeleteFile(int)\0"
    "slotEnterFile(QListWidgetItem*)\0"
    "slotUploadClicked()\0slotDownloadClicked()\0"
    "slotMoveClicked()\0slotBackClicked()\0"
    "slotDeleteClicked()\0slotCreateClicked()\0"
    "slotUpdateData(QList<mFile>*)\0"
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
        case 0: sgnalConnectServer(); break;
        case 1: sgnalUploadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: sgnalDownloadFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: sgnalEnterDir((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sgnalBackDir(); break;
        case 5: sgnalCreateDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: sgnalDeleteFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: slotEnterFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: slotUploadClicked(); break;
        case 9: slotDownloadClicked(); break;
        case 10: slotMoveClicked(); break;
        case 11: slotBackClicked(); break;
        case 12: slotDeleteClicked(); break;
        case 13: slotCreateClicked(); break;
        case 14: slotUpdateData((*reinterpret_cast< QList<mFile>*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainPage::sgnalConnectServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainPage::sgnalUploadFile(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainPage::sgnalDownloadFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainPage::sgnalEnterDir(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainPage::sgnalBackDir()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainPage::sgnalCreateDir(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainPage::sgnalDeleteFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
