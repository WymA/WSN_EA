/****************************************************************************
** Meta object code from reading C++ file 'eaworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../eaworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eaworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EAWorker_t {
    QByteArrayData data[13];
    char stringdata[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EAWorker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EAWorker_t qt_meta_stringdata_EAWorker = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 11),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 14),
QT_MOC_LITERAL(4, 37, 3),
QT_MOC_LITERAL(5, 41, 12),
QT_MOC_LITERAL(6, 54, 6),
QT_MOC_LITERAL(7, 61, 8),
QT_MOC_LITERAL(8, 70, 8),
QT_MOC_LITERAL(9, 79, 7),
QT_MOC_LITERAL(10, 87, 8),
QT_MOC_LITERAL(11, 96, 9),
QT_MOC_LITERAL(12, 106, 8)
    },
    "EAWorker\0updatePiant\0\0QVector<Indiv>\0"
    "vec\0startPauseEA\0stopEA\0setNSGA2\0"
    "setMOEAD\0setPara\0setCache\0singleRun\0"
    "getCache\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EAWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   62,    2, 0x0a,
       6,    0,   63,    2, 0x0a,
       7,    0,   64,    2, 0x0a,
       8,    0,   65,    2, 0x0a,
       9,    0,   66,    2, 0x0a,
      10,    0,   67,    2, 0x0a,
      11,    0,   68,    2, 0x0a,
      12,    0,   69,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 3,

       0        // eod
};

void EAWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EAWorker *_t = static_cast<EAWorker *>(_o);
        switch (_id) {
        case 0: _t->updatePiant((*reinterpret_cast< QVector<Indiv>(*)>(_a[1]))); break;
        case 1: _t->startPauseEA(); break;
        case 2: _t->stopEA(); break;
        case 3: _t->setNSGA2(); break;
        case 4: _t->setMOEAD(); break;
        case 5: _t->setPara(); break;
        case 6: _t->setCache(); break;
        case 7: _t->singleRun(); break;
        case 8: { QVector<Indiv> _r = _t->getCache();
            if (_a[0]) *reinterpret_cast< QVector<Indiv>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EAWorker::*_t)(QVector<Indiv> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EAWorker::updatePiant)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EAWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EAWorker.data,
      qt_meta_data_EAWorker,  qt_static_metacall, 0, 0}
};


const QMetaObject *EAWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EAWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EAWorker.stringdata))
        return static_cast<void*>(const_cast< EAWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int EAWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EAWorker::updatePiant(QVector<Indiv> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
