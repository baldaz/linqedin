/****************************************************************************
** Meta object code from reading C++ file 'gui_adminwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/gui_adminwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_adminwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Gui_AdminWindow_t {
    QByteArrayData data[10];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Gui_AdminWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Gui_AdminWindow_t qt_meta_stringdata_Gui_AdminWindow = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 8),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 11),
QT_MOC_LITERAL(4, 38, 16),
QT_MOC_LITERAL(5, 55, 8),
QT_MOC_LITERAL(6, 64, 7),
QT_MOC_LITERAL(7, 72, 10),
QT_MOC_LITERAL(8, 83, 11),
QT_MOC_LITERAL(9, 95, 12)
    },
    "Gui_AdminWindow\0modified\0\0startSearch\0"
    "showSearchResult\0showUser\0addUser\0"
    "removeUser\0upgradeUser\0refreshLists\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui_AdminWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a,
       4,    0,   56,    2, 0x0a,
       5,    0,   57,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    0,   59,    2, 0x0a,
       8,    0,   60,    2, 0x0a,
       9,    0,   61,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gui_AdminWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gui_AdminWindow *_t = static_cast<Gui_AdminWindow *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->startSearch(); break;
        case 2: _t->showSearchResult(); break;
        case 3: _t->showUser(); break;
        case 4: _t->addUser(); break;
        case 5: _t->removeUser(); break;
        case 6: _t->upgradeUser(); break;
        case 7: _t->refreshLists(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Gui_AdminWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Gui_AdminWindow::modified)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Gui_AdminWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gui_AdminWindow.data,
      qt_meta_data_Gui_AdminWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *Gui_AdminWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui_AdminWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui_AdminWindow.stringdata))
        return static_cast<void*>(const_cast< Gui_AdminWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gui_AdminWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Gui_AdminWindow::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
