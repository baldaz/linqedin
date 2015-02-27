/****************************************************************************
** Meta object code from reading C++ file 'gui_groups.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/gui_groups.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_groups.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Gui_Groups_t {
    QByteArrayData data[15];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Gui_Groups_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Gui_Groups_t qt_meta_stringdata_Gui_Groups = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 7),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 7),
QT_MOC_LITERAL(4, 28, 9),
QT_MOC_LITERAL(5, 38, 8),
QT_MOC_LITERAL(6, 47, 12),
QT_MOC_LITERAL(7, 60, 8),
QT_MOC_LITERAL(8, 69, 8),
QT_MOC_LITERAL(9, 78, 11),
QT_MOC_LITERAL(10, 90, 11),
QT_MOC_LITERAL(11, 102, 10),
QT_MOC_LITERAL(12, 113, 10),
QT_MOC_LITERAL(13, 124, 11),
QT_MOC_LITERAL(14, 136, 10)
    },
    "Gui_Groups\0created\0\0refresh\0showGroup\0"
    "sendPost\0showNewGroup\0newGroup\0addGroup\0"
    "searchGroup\0deleteGroup\0clearPosts\0"
    "leaveGroup\0memListMenu\0kickMember\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui_Groups[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   82,    2, 0x0a,
       4,    0,   85,    2, 0x0a,
       5,    0,   86,    2, 0x0a,
       6,    0,   87,    2, 0x0a,
       7,    0,   88,    2, 0x0a,
       8,    0,   89,    2, 0x0a,
       9,    0,   90,    2, 0x0a,
      10,    0,   91,    2, 0x0a,
      11,    0,   92,    2, 0x0a,
      12,    0,   93,    2, 0x0a,
      13,    1,   94,    2, 0x0a,
      14,    0,   97,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void Gui_Groups::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gui_Groups *_t = static_cast<Gui_Groups *>(_o);
        switch (_id) {
        case 0: _t->created((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->refresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showGroup(); break;
        case 3: _t->sendPost(); break;
        case 4: _t->showNewGroup(); break;
        case 5: _t->newGroup(); break;
        case 6: _t->addGroup(); break;
        case 7: _t->searchGroup(); break;
        case 8: _t->deleteGroup(); break;
        case 9: _t->clearPosts(); break;
        case 10: _t->leaveGroup(); break;
        case 11: _t->memListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->kickMember(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Gui_Groups::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Gui_Groups::created)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Gui_Groups::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_Gui_Groups.data,
      qt_meta_data_Gui_Groups,  qt_static_metacall, 0, 0}
};


const QMetaObject *Gui_Groups::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui_Groups::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui_Groups.stringdata))
        return static_cast<void*>(const_cast< Gui_Groups*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int Gui_Groups::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGridLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Gui_Groups::created(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
