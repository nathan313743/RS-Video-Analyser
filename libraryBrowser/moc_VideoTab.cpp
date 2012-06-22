/****************************************************************************
** Meta object code from reading C++ file 'VideoTab.h'
**
** Created: Sun Jun 10 20:59:33 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "VideoTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,    9,    9,    9, 0x0a,
      66,    9,    9,    9, 0x0a,
      77,    9,    9,    9, 0x08,
     103,    9,    9,    9, 0x08,
     128,    9,    9,    9, 0x08,
     158,    9,    9,    9, 0x08,
     182,    9,    9,    9, 0x08,
     215,    9,    9,    9, 0x08,
     248,    9,    9,    9, 0x08,
     275,    9,    9,    9, 0x08,
     306,    9,    9,    9, 0x08,
     334,    9,    9,    9, 0x08,
     364,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoTab[] = {
    "VideoTab\0\0,,\0comboChange(QString,QString,QString)\0"
    "on_repopulate()\0on_reset()\0"
    "on_aspect_change(QString)\0"
    "on_color_change(QString)\0"
    "on_encryption_change(QString)\0"
    "on_scan_change(QString)\0"
    "on_framerate_change_min(QString)\0"
    "on_framerate_change_max(QString)\0"
    "on_resSize_change(QString)\0"
    "on_resStandard_change(QString)\0"
    "on_sampling_change(QString)\0"
    "on_vidBitrate_change(QString)\0"
    "on_vidFormat_change(QString)\0"
};

void VideoTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoTab *_t = static_cast<VideoTab *>(_o);
        switch (_id) {
        case 0: _t->comboChange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->on_repopulate(); break;
        case 2: _t->on_reset(); break;
        case 3: _t->on_aspect_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_color_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_encryption_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_scan_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_framerate_change_min((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_framerate_change_max((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->on_resSize_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_resStandard_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_sampling_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->on_vidBitrate_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->on_vidFormat_change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoTab,
      qt_meta_data_VideoTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoTab))
        return static_cast<void*>(const_cast< VideoTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void VideoTab::comboChange(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
