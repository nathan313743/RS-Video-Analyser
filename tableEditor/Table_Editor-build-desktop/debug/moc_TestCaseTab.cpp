/****************************************************************************
** Meta object code from reading C++ file 'TestCaseTab.h'
**
** Created: Fri 26. Aug 15:47:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Table_Editor/TestCaseTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestCaseTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestCaseTab[] = {

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
      13,   12,   12,   12, 0x08,
      25,   12,   12,   12, 0x08,
      40,   34,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestCaseTab[] = {
    "TestCaseTab\0\0on_delete()\0on_add()\0"
    "index\0on_recevied_index(QModelIndex)\0"
};

const QMetaObject TestCaseTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TestCaseTab,
      qt_meta_data_TestCaseTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestCaseTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestCaseTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestCaseTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestCaseTab))
        return static_cast<void*>(const_cast< TestCaseTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int TestCaseTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_delete(); break;
        case 1: on_add(); break;
        case 2: on_recevied_index((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
