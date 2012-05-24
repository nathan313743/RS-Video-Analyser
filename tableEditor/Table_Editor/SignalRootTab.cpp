#include "SignalRootTab.h"


SignalRootTab::SignalRootTab(QWidget *parent, CodeInterface &codInt, const bool editFlag)
{
	code_int = &codInt;
	setupDisplay();
	populate_boxes();
	setReadWrite(editFlag);
	setup_autocomplete();
}

SignalRootTab::~SignalRootTab(void)
{
	delete edt_region;
	delete edt_producer;
	delete edt_source;

	delete reg_completer;
	delete prd_completer;
	delete src_completer;
}

void SignalRootTab::setupDisplay()
{
	QGridLayout *gridLayout = new QGridLayout();

	//labels
	QLabel *lbl_region = new QLabel("Region:");
	QLabel *lbl_producer = new QLabel("Producer:");
	QLabel *lbl_source = new QLabel("Source:");

	edt_region = new QLineEdit();
	edt_producer = new QLineEdit();
	edt_source = new QLineEdit();

	//layout
	gridLayout->addWidget(lbl_region, 0, 0, 1, 1);
	gridLayout->addWidget(edt_region, 0, 1, 1, 1);

	gridLayout->addWidget(lbl_producer, 1, 0, 1, 1);
	gridLayout->addWidget(edt_producer, 1, 1, 1, 1);

	gridLayout->addWidget(lbl_source, 2, 0, 1, 1);
	gridLayout->addWidget(edt_source, 2, 1, 1, 1);

	this->setLayout(gridLayout);
	this->setMaximumSize(350,100);
}

void SignalRootTab::populate_boxes()
{
	QStringList valueList = code_int->populate_sig_boxes();

	edt_region->setText(valueList.at(0));
	edt_producer->setText(valueList.at(1));
	edt_source->setText(valueList.at(2));
}

void SignalRootTab::setup_autocomplete()
{
	QVector<QStringList> list = code_int->get_sig_autocomplete();

	reg_completer = new QCompleter(list.at(0));
	reg_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_region->setCompleter(reg_completer);

	prd_completer = new QCompleter(list.at(1));
	prd_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_producer->setCompleter(prd_completer);

	src_completer = new QCompleter(list.at(2));
	src_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_source->setCompleter(src_completer);
}

void SignalRootTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		edt_region->setReadOnly(true);
		edt_producer->setReadOnly(true);
		edt_source->setReadOnly(true);

	}
}

bool SignalRootTab::writeNewValues()
{
	QStringList textBoxVals;

	textBoxVals.push_back(edt_region->text());
	textBoxVals.push_back(edt_producer->text());
	textBoxVals.push_back(edt_source->text());

	bool success = code_int->write_sig_values(textBoxVals);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}
}