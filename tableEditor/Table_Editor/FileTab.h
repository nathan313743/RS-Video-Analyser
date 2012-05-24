#pragma once
#include <qobject.h>
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qgridlayout.h>
#include <qstring.h>
#include <qdebug.h>
#include "DatabaseAccessor.h"
#include <qsqlquery.h>
#include <qvariant.h>
#include "CodeInterface.h"

class FileTab : public QWidget
{
	Q_OBJECT

public:
	FileTab(QWidget *, CodeInterface &, const bool);
	~FileTab();
	CodeInterface *code_int;

private:
	void populateBoxes();
	void setupDisplay();
	void setReadWrite(const bool);

	int file_ID;											//id for writing updates
	QString _fileName;
	QLineEdit *edt_fName;
	QLineEdit *edt_fExt;
	QLineEdit *edt_fSize;
	QLineEdit *edt_fLoc;
	QLineEdit *edt_fDate;
};

