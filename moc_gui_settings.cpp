/****************************************************************************
** Meta object code from reading C++ file 'gui_settings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/gui_settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Gui_Settings_t {
    QByteArrayData data[15];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Gui_Settings_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Gui_Settings_t qt_meta_stringdata_Gui_Settings = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 13),
QT_MOC_LITERAL(4, 39, 13),
QT_MOC_LITERAL(5, 53, 13),
QT_MOC_LITERAL(6, 67, 8),
QT_MOC_LITERAL(7, 76, 11),
QT_MOC_LITERAL(8, 88, 11),
QT_MOC_LITERAL(9, 100, 11),
QT_MOC_LITERAL(10, 112, 14),
QT_MOC_LITERAL(11, 127, 14),
QT_MOC_LITERAL(12, 142, 11),
QT_MOC_LITERAL(13, 154, 14),
QT_MOC_LITERAL(14, 169, 14)
    },
    "Gui_Settings\0skillsMenu\0\0interestsMenu\0"
    "languagesMenu\0buttonToggled\0addSkill\0"
    "deleteSkill\0modifySkill\0addInterest\0"
    "deleteInterest\0modifyInterest\0addLanguage\0"
    "deleteLanguage\0modifyLanguage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui_Settings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a,
       3,    1,   82,    2, 0x0a,
       4,    1,   85,    2, 0x0a,
       5,    0,   88,    2, 0x0a,
       6,    0,   89,    2, 0x0a,
       7,    0,   90,    2, 0x0a,
       8,    0,   91,    2, 0x0a,
       9,    0,   92,    2, 0x0a,
      10,    0,   93,    2, 0x0a,
      11,    0,   94,    2, 0x0a,
      12,    0,   95,    2, 0x0a,
      13,    0,   96,    2, 0x0a,
      14,    0,   97,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Gui_Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gui_Settings *_t = static_cast<Gui_Settings *>(_o);
        switch (_id) {
        case 0: _t->skillsMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->interestsMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->languagesMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->buttonToggled(); break;
        case 4: _t->addSkill(); break;
        case 5: _t->deleteSkill(); break;
        case 6: _t->modifySkill(); break;
        case 7: _t->addInterest(); break;
        case 8: _t->deleteInterest(); break;
        case 9: _t->modifyInterest(); break;
        case 10: _t->addLanguage(); break;
        case 11: _t->deleteLanguage(); break;
        case 12: _t->modifyLanguage(); break;
        default: ;
        }
    }
}

const QMetaObject Gui_Settings::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_Gui_Settings.data,
      qt_meta_data_Gui_Settings,  qt_static_metacall, 0, 0}
};


const QMetaObject *Gui_Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui_Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui_Settings.stringdata))
        return static_cast<void*>(const_cast< Gui_Settings*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int Gui_Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
