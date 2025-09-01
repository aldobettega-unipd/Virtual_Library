/****************************************************************************
** Meta object code from reading C++ file 'JsonManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/model/persistence/JsonManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JsonManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JsonManager_t {
    QByteArrayData data[12];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JsonManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JsonManager_t qt_meta_stringdata_JsonManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "JsonManager"
QT_MOC_LITERAL(1, 12, 13), // "saveNewObject"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "Biblioteca*"
QT_MOC_LITERAL(4, 39, 3), // "obj"
QT_MOC_LITERAL(5, 43, 12), // "updateObject"
QT_MOC_LITERAL(6, 56, 12), // "deleteObject"
QT_MOC_LITERAL(7, 69, 11), // "savePrenota"
QT_MOC_LITERAL(8, 81, 6), // "biblio"
QT_MOC_LITERAL(9, 88, 9), // "saveLetto"
QT_MOC_LITERAL(10, 98, 15), // "Media_cartaceo*"
QT_MOC_LITERAL(11, 114, 8) // "cartaceo"

    },
    "JsonManager\0saveNewObject\0\0Biblioteca*\0"
    "obj\0updateObject\0deleteObject\0savePrenota\0"
    "biblio\0saveLetto\0Media_cartaceo*\0"
    "cartaceo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JsonManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void JsonManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JsonManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveNewObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 1: _t->updateObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 2: _t->deleteObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 3: _t->savePrenota((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 4: _t->saveLetto((*reinterpret_cast< Media_cartaceo*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JsonManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_JsonManager.data,
    qt_meta_data_JsonManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JsonManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JsonManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JsonManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int JsonManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
