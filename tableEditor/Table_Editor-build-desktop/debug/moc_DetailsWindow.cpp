/****************************************************************************
** Meta object code from reading C++ file 'DetailsWindow.h'
**
** Created: Fri 26. Aug 15:47:14 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Table_Editor/DetailsWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DetailsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DetailsWindow[] = {

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
      15,   14,   14,   14, 0x08,
      22,   14,   14,   14, 0x08,
      33,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DetailsWindow[] = {
    "DetailsWindow\0\0onOK()\0onCancel()\0"
    "onAccept()\0"
};

const QMetaObject DetailsWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DetailsWindow,
      qt_meta_data_DetailsWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetailsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetailsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetailsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetailsWindow))
        return static_cast<void*>(const_cast< DetailsWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int DetailsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onOK(); break;
        case 1: onCancel(); break;
        case 2: onAccept(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
