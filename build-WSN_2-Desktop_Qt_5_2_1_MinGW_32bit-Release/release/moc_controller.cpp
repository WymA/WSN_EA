/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Controller_t {
    QByteArrayData data[15];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Controller_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Controller_t qt_meta_stringdata_Controller = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 11),
QT_MOC_LITERAL(4, 35, 11),
QT_MOC_LITERAL(5, 47, 18),
QT_MOC_LITERAL(6, 66, 12),
QT_MOC_LITERAL(7, 79, 11),
QT_MOC_LITERAL(8, 91, 9),
QT_MOC_LITERAL(9, 101, 12),
QT_MOC_LITERAL(10, 114, 16),
QT_MOC_LITERAL(11, 131, 14),
QT_MOC_LITERAL(12, 146, 3),
QT_MOC_LITERAL(13, 150, 7),
QT_MOC_LITERAL(14, 158, 10)
    },
    "Controller\0paraSignal\0\0NSGA2Signal\0"
    "MOEADSignal\0EAStartPauseSignal\0"
    "EAStopSignal\0updatePaint\0singleRun\0"
    "startPauseEA\0setDiagramPoints\0"
    "QVector<Indiv>\0vec\0setPara\0initialize\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06,
       3,    0,   70,    2, 0x06,
       4,    0,   71,    2, 0x06,
       5,    0,   72,    2, 0x06,
       6,    0,   73,    2, 0x06,
       7,    0,   74,    2, 0x06,
       8,    0,   75,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x0a,
      10,    1,   77,    2, 0x0a,
      13,    0,   80,    2, 0x0a,
      14,    0,   81,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Controller *_t = static_cast<Controller *>(_o);
        switch (_id) {
        case 0: _t->paraSignal(); break;
        case 1: _t->NSGA2Signal(); break;
        case 2: _t->MOEADSignal(); break;
        case 3: _t->EAStartPauseSignal(); break;
        case 4: _t->EAStopSignal(); break;
        case 5: _t->updatePaint(); break;
        case 6: _t->singleRun(); break;
        case 7: _t->startPauseEA(); break;
        case 8: _t->setDiagramPoints((*reinterpret_cast< QVector<Indiv>(*)>(_a[1]))); break;
        case 9: _t->setPara(); break;
        case 10: _t->initialize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::paraSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::NSGA2Signal)) {
                *result = 1;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::MOEADSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::EAStartPauseSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::EAStopSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::updatePaint)) {
                *result = 5;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::singleRun)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject Controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controller.data,
      qt_meta_data_Controller,  qt_static_metacall, 0, 0}
};


const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controller.stringdata))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Controller::paraSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Controller::NSGA2Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Controller::MOEADSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Controller::EAStartPauseSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Controller::EAStopSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Controller::updatePaint()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Controller::singleRun()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
