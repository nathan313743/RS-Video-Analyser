/****************************************************************************
** Meta object code from reading C++ file 'TransportTab.h'
**
** Created: Fri 26. Aug 15:47:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Table_Editor/TransportTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransportTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransportTab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x08,
      51,   13,   13,   13, 0x08,
      63,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TransportTab[] = {
    "TransportTab\0\0index\0on_recevied_index(QModelIndex)\0"
    "on_delete()\0on_add()\0"
};

const QMetaObject TransportTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TransportTab,
      qt_meta_data_TransportTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransportTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransportTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransportTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransportTab))
        return static_cast<void*>(const_cast< TransportTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int TransportTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_recevied_index((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: on_delete(); break;
        case 2: on_add(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
