/****************************************************************************
** Meta object code from reading C++ file 'TableViewer.h'
**
** Created: Fri Jul 6 20:18:31 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tableEditor/TableViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TableViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      42,   12,   12,   12, 0x0a,
      51,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,
      71,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TableViewer[] = {
    "TableViewer\0\0onReceviedIndex(QModelIndex)\0"
    "onView()\0onEdit()\0onDelete()\0onCancel()\0"
};

void TableViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TableViewer *_t = static_cast<TableViewer *>(_o);
        switch (_id) {
        case 0: _t->onReceviedIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onView(); break;
        case 2: _t->onEdit(); break;
        case 3: _t->onDelete(); break;
        case 4: _t->onCancel(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TableViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TableViewer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableViewer,
      qt_meta_data_TableViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TableViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TableViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TableViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableViewer))
        return static_cast<void*>(const_cast< TableViewer*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
