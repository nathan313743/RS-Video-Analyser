#include "FileTab.h"

FileTab::FileTab(QWidget *parent, CodeInterface &codInt, const bool editFlag) : QWidget(parent)
{
	code_int = &codInt;
	setupDisplay();
	populateBoxes();
	setReadWrite(editFlag);
}


FileTab::~FileTab()
{
	delete edt_fName;
	delete edt_fExt;
	delete edt_fSize;
	delete edt_fLoc;
	delete edt_fDate;
}

void FileTab::setReadWrite(const bool editFlag)
{
	//set the all as read-only regardless
	edt_fName->setReadOnly(true);
	edt_fExt->setReadOnly(true);
	edt_fSize->setReadOnly(true);
	edt_fLoc->setReadOnly(true);
	edt_fDate->setReadOnly(true);
}

void FileTab::setupDisplay()
{
	QGridLayout *gridLayout = new QGridLayout();

	//Labels
	QLabel *lbl_fName = new QLabel("File Name:");
	QLabel *lbl_fExt = new QLabel("Extension:");
	QLabel *lbl_fSize = new QLabel("File Size MB:");
	QLabel *lbl_fLoc = new QLabel("Location:");
	QLabel *lbl_fDate = new QLabel("Date Added:");

	//Edit boxes
	edt_fName = new QLineEdit;
	edt_fExt = new QLineEdit;
	edt_fSize = new QLineEdit;
	edt_fLoc = new QLineEdit;
	edt_fDate = new QLineEdit;
	
	lbl_fName->setBuddy(edt_fName);
	lbl_fExt->setBuddy(edt_fExt);
	lbl_fSize->setBuddy(edt_fSize);
	lbl_fLoc->setBuddy(edt_fLoc);
	lbl_fDate->setBuddy(edt_fDate);

	gridLayout->addWidget(lbl_fName, 0, 0, 1, 1);
	gridLayout->addWidget(edt_fName, 0, 1, 1, 1);

	gridLayout->addWidget(lbl_fExt, 1, 0, 1, 1);
	gridLayout->addWidget(edt_fExt, 1, 1, 1, 1);

	gridLayout->addWidget(lbl_fSize, 2, 0, 1, 1);
	gridLayout->addWidget(edt_fSize, 2, 1, 1, 1);

	gridLayout->addWidget(lbl_fLoc, 3, 0, 1, 1);
	gridLayout->addWidget(edt_fLoc, 3, 1, 1, 1);

	gridLayout->addWidget(lbl_fDate, 4, 0, 1, 1);
	gridLayout->addWidget(edt_fDate, 4, 1, 1, 1);

	this->setLayout(gridLayout);
	this->setMaximumSize(350,150);
}

void FileTab::populateBoxes()
{
	QStringList valueList = code_int->populate_file_boxes();

	edt_fName->setText(valueList.at(0));
	edt_fExt->setText(valueList.at(1));
	edt_fSize->setText(valueList.at(2));
	edt_fLoc->setText(valueList.at(3));
	edt_fDate->setText(valueList.at(4));
}
