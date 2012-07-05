#pragma once
#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include "DatabaseAccessor.h"
#include <QSqlQuery>
#include <QVariant>
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

