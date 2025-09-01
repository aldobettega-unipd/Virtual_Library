/****************************************************************************
** Meta object code from reading C++ file 'AdminPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/gui/AdminPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AdminPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AdminPage_t {
    QByteArrayData data[13];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AdminPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AdminPage_t qt_meta_stringdata_AdminPage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AdminPage"
QT_MOC_LITERAL(1, 10, 11), // "onEditMedia"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "Biblioteca*"
QT_MOC_LITERAL(4, 35, 5), // "media"
QT_MOC_LITERAL(5, 41, 13), // "onDeleteMedia"
QT_MOC_LITERAL(6, 55, 15), // "createNewObject"
QT_MOC_LITERAL(7, 71, 8), // "newMedia"
QT_MOC_LITERAL(8, 80, 12), // "removeObject"
QT_MOC_LITERAL(9, 93, 12), // "modifyObject"
QT_MOC_LITERAL(10, 106, 18), // "onAddButtonClicked"
QT_MOC_LITERAL(11, 125, 15), // "handleEditMedia"
QT_MOC_LITERAL(12, 141, 17) // "handleDeleteMedia"

    },
    "AdminPage\0onEditMedia\0\0Biblioteca*\0"
    "media\0onDeleteMedia\0createNewObject\0"
    "newMedia\0removeObject\0modifyObject\0"
    "onAddButtonClicked\0handleEditMedia\0"
    "handleDeleteMedia"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AdminPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
       9,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   69,    2, 0x08 /* Private */,
      11,    1,   70,    2, 0x08 /* Private */,
      12,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, 0x80000000 | 3,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void AdminPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AdminPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEditMedia((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 1: _t->onDeleteMedia((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 2: _t->createNewObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 3: _t->removeObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 4: _t->modifyObject((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 5: _t->onAddButtonClicked(); break;
        case 6: _t->handleEditMedia((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        case 7: _t->handleDeleteMedia((*reinterpret_cast< Biblioteca*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AdminPage::onEditMedia)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AdminPage::onDeleteMedia)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AdminPage::createNewObject)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AdminPage::removeObject)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AdminPage::*)(Biblioteca * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AdminPage::modifyObject)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AdminPage::staticMetaObject = { {
    QMetaObject::SuperData::link<BasePage::staticMetaObject>(),
    qt_meta_stringdata_AdminPage.data,
    qt_meta_data_AdminPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AdminPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AdminPage.stringdata0))
        return static_cast<void*>(this);
    return BasePage::qt_metacast(_clname);
}

int AdminPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasePage::qt_metacall(_c, _id, _a);
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
void AdminPage::onEditMedia(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AdminPage::onDeleteMedia(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AdminPage::createNewObject(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AdminPage::removeObject(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AdminPage::modifyObject(Biblioteca * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
