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
    QByteArrayData data[34];
    char stringdata0[433];
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
QT_MOC_LITERAL(12, 117, 13), // "butter_filter"
QT_MOC_LITERAL(13, 131, 21), // "std::complex<double>*"
QT_MOC_LITERAL(14, 153, 6), // "Signal"
QT_MOC_LITERAL(15, 160, 14), // "FilteredSignal"
QT_MOC_LITERAL(16, 175, 9), // "NumSigPts"
QT_MOC_LITERAL(17, 185, 9), // "fftwShift"
QT_MOC_LITERAL(18, 195, 20), // "std::vector<double>&"
QT_MOC_LITERAL(19, 216, 10), // "data_shift"
QT_MOC_LITERAL(20, 227, 16), // "fftwShiftComplex"
QT_MOC_LITERAL(21, 244, 35), // "std::vector<std::complex<doub..."
QT_MOC_LITERAL(22, 280, 4), // "STFT"
QT_MOC_LITERAL(23, 285, 12), // "signalLength"
QT_MOC_LITERAL(24, 298, 10), // "windowSize"
QT_MOC_LITERAL(25, 309, 7), // "hopSize"
QT_MOC_LITERAL(26, 317, 9), // "FFTPoints"
QT_MOC_LITERAL(27, 327, 49), // "std::vector<std::vector<std::..."
QT_MOC_LITERAL(28, 377, 6), // "result"
QT_MOC_LITERAL(29, 384, 13), // "fftw_complex*"
QT_MOC_LITERAL(30, 398, 9), // "Data_stft"
QT_MOC_LITERAL(31, 408, 8), // "out_stft"
QT_MOC_LITERAL(32, 417, 10), // "fftw_plan*"
QT_MOC_LITERAL(33, 428, 4) // "plan"

    },
    "MaFenetre\0initializeRadar\0\0updateRadar\0"
    "updateBandwith\0requestData\0processData\0"
    "linspace\0QVector<double>\0start\0end\0"
    "num\0butter_filter\0std::complex<double>*\0"
    "Signal\0FilteredSignal\0NumSigPts\0"
    "fftwShift\0std::vector<double>&\0"
    "data_shift\0fftwShiftComplex\0"
    "std::vector<std::complex<double> >&\0"
    "STFT\0signalLength\0windowSize\0hopSize\0"
    "FFTPoints\0std::vector<std::vector<std::complex<double> > >&\0"
    "result\0fftw_complex*\0Data_stft\0out_stft\0"
    "fftw_plan*\0plan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaFenetre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    3,   69,    2, 0x08 /* Private */,
      12,    3,   76,    2, 0x08 /* Private */,
      17,    1,   83,    2, 0x08 /* Private */,
      20,    1,   86,    2, 0x08 /* Private */,
      22,    9,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 8, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13, QMetaType::Int,   14,   15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   19,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, 0x80000000 | 27, 0x80000000 | 29, 0x80000000 | 29, 0x80000000 | 32,   14,   23,   24,   25,   26,   28,   30,   31,   33,

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
        case 6: _t->butter_filter((*reinterpret_cast< std::complex<double>*(*)>(_a[1])),(*reinterpret_cast< std::complex<double>*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->fftwShift((*reinterpret_cast< std::vector<double>(*)>(_a[1]))); break;
        case 8: _t->fftwShiftComplex((*reinterpret_cast< std::vector<std::complex<double> >(*)>(_a[1]))); break;
        case 9: _t->STFT((*reinterpret_cast< std::complex<double>*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< std::vector<std::vector<std::complex<double> > >(*)>(_a[6])),(*reinterpret_cast< fftw_complex*(*)>(_a[7])),(*reinterpret_cast< fftw_complex*(*)>(_a[8])),(*reinterpret_cast< fftw_plan*(*)>(_a[9]))); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
