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
    QByteArrayData data[18];
    char stringdata[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Gui_Settings_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Gui_Settings_t qt_meta_stringdata_Gui_Settings = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 7),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 17),
QT_MOC_LITERAL(4, 40, 10),
QT_MOC_LITERAL(5, 51, 13),
QT_MOC_LITERAL(6, 65, 13),
QT_MOC_LITERAL(7, 79, 15),
QT_MOC_LITERAL(8, 95, 13),
QT_MOC_LITERAL(9, 109, 8),
QT_MOC_LITERAL(10, 118, 11),
QT_MOC_LITERAL(11, 130, 11),
QT_MOC_LITERAL(12, 142, 14),
QT_MOC_LITERAL(13, 157, 11),
QT_MOC_LITERAL(14, 169, 14),
QT_MOC_LITERAL(15, 184, 13),
QT_MOC_LITERAL(16, 198, 16),
QT_MOC_LITERAL(17, 215, 16)
    },
    "Gui_Settings\0refresh\0\0triggerFileDialog\0"
    "skillsMenu\0interestsMenu\0languagesMenu\0"
    "experiencesMenu\0buttonToggled\0addSkill\0"
    "deleteSkill\0addInterest\0deleteInterest\0"
    "addLanguage\0deleteLanguage\0addExperience\0"
    "deleteExperience\0modifyExperience\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui_Settings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a,
       3,    0,   95,    2, 0x0a,
       4,    1,   96,    2, 0x0a,
       5,    1,   99,    2, 0x0a,
       6,    1,  102,    2, 0x0a,
       7,    1,  105,    2, 0x0a,
       8,    0,  108,    2, 0x0a,
       9,    0,  109,    2, 0x0a,
      10,    0,  110,    2, 0x0a,
      11,    0,  111,    2, 0x0a,
      12,    0,  112,    2, 0x0a,
      13,    0,  113,    2, 0x0a,
      14,    0,  114,    2, 0x0a,
      15,    0,  115,    2, 0x0a,
      16,    0,  116,    2, 0x0a,
      17,    0,  117,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
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
        case 0: _t->refresh(); break;
        case 1: _t->triggerFileDialog(); break;
        case 2: _t->skillsMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->interestsMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->languagesMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: _t->experiencesMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: _t->buttonToggled(); break;
        case 7: _t->addSkill(); break;
        case 8: _t->deleteSkill(); break;
        case 9: _t->addInterest(); break;
        case 10: _t->deleteInterest(); break;
        case 11: _t->addLanguage(); break;
        case 12: _t->deleteLanguage(); break;
        case 13: _t->addExperience(); break;
        case 14: _t->deleteExperience(); break;
        case 15: _t->modifyExperience(); break;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
