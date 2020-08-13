/****************************************************************************
** Meta object code from reading C++ file 'MaFenetre.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/MaFenetre.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MaFenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MaFenetre_t {
    QByteArrayData data[15];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaFenetre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaFenetre_t qt_meta_stringdata_MaFenetre = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MaFenetre"
QT_MOC_LITERAL(1, 10, 15), // "initializeRadar"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "updateRadar"
QT_MOC_LITERAL(4, 39, 14), // "updateBandwith"
QT_MOC_LITERAL(5, 54, 11), // "requestData"
QT_MOC_LITERAL(6, 66, 11), // "processData"
QT_MOC_LITERAL(7, 78, 8), // "linspace"
QT_MOC_LITERAL(8, 87, 15), // "QVector<double>"
QT_MOC_LITERAL(9, 103, 5), // "start"
QT_MOC_LITERAL(10, 109, 3), // "end"
QT_MOC_LITERAL(11, 113, 3), // "num"
QT_MOC_LITERAL(12, 117, 9), // "fftwShift"
QT_MOC_LITERAL(13, 127, 20), // "std::vector<double>&"
QT_MOC_LITERAL(14, 148, 10) // "data_shift"

    },
    "MaFenetre\0initializeRadar\0\0updateRadar\0"
    "updateBandwith\0requestData\0processData\0"
    "linspace\0QVector<double>\0start\0end\0"
    "num\0fftwShift\0std::vector<double>&\0"
    "data_shift"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaFenetre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    3,   54,    2, 0x08 /* Private */,
      12,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 8, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void MaFenetre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaFenetre *_t = static_cast<MaFenetre *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initializeRadar(); break;
        case 1: _t->updateRadar(); break;
        case 2: _t->updateBandwith(); break;
        case 3: _t->requestData(); break;
        case 4: _t->processData(); break;
        case 5: { QVector<double> _r = _t->linspace((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVector<double>*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->fftwShift((*reinterpret_cast< std::vector<double>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MaFenetre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MaFenetre.data,
      qt_meta_data_MaFenetre,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MaFenetre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaFenetre::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MaFenetre.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MaFenetre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
