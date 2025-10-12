/****************************************************************************
** Meta object code from reading C++ file 'dashboardwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SimpleTemplate/dashboardwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboardwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DashboardWidget_t {
    QByteArrayData data[19];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DashboardWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DashboardWidget_t qt_meta_stringdata_DashboardWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DashboardWidget"
QT_MOC_LITERAL(1, 16, 11), // "setMinValue"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "v"
QT_MOC_LITERAL(4, 31, 11), // "setMaxValue"
QT_MOC_LITERAL(5, 43, 8), // "setValue"
QT_MOC_LITERAL(6, 52, 7), // "setUnit"
QT_MOC_LITERAL(7, 60, 1), // "u"
QT_MOC_LITERAL(8, 62, 12), // "setDialColor"
QT_MOC_LITERAL(9, 75, 1), // "c"
QT_MOC_LITERAL(10, 77, 15), // "setPointerColor"
QT_MOC_LITERAL(11, 93, 12), // "setTextColor"
QT_MOC_LITERAL(12, 106, 8), // "minValue"
QT_MOC_LITERAL(13, 115, 8), // "maxValue"
QT_MOC_LITERAL(14, 124, 5), // "value"
QT_MOC_LITERAL(15, 130, 4), // "unit"
QT_MOC_LITERAL(16, 135, 9), // "dialColor"
QT_MOC_LITERAL(17, 145, 12), // "pointerColor"
QT_MOC_LITERAL(18, 158, 9) // "textColor"

    },
    "DashboardWidget\0setMinValue\0\0v\0"
    "setMaxValue\0setValue\0setUnit\0u\0"
    "setDialColor\0c\0setPointerColor\0"
    "setTextColor\0minValue\0maxValue\0value\0"
    "unit\0dialColor\0pointerColor\0textColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DashboardWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
      10,    1,   64,    2, 0x0a /* Public */,
      11,    1,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QColor,    9,
    QMetaType::Void, QMetaType::QColor,    9,
    QMetaType::Void, QMetaType::QColor,    9,

 // properties: name, type, flags
      12, QMetaType::Double, 0x00095103,
      13, QMetaType::Double, 0x00095103,
      14, QMetaType::Double, 0x00095103,
      15, QMetaType::QString, 0x00095103,
      16, QMetaType::QColor, 0x00095103,
      17, QMetaType::QColor, 0x00095103,
      18, QMetaType::QColor, 0x00095103,

       0        // eod
};

void DashboardWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DashboardWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMinValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setMaxValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setUnit((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setDialColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->setPointerColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 6: _t->setTextColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DashboardWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->minValue(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->maxValue(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->value(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->unit(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->dialColor(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->pointerColor(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DashboardWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinValue(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setMaxValue(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setValue(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setUnit(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setDialColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setPointerColor(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DashboardWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DashboardWidget.data,
    qt_meta_data_DashboardWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DashboardWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DashboardWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
