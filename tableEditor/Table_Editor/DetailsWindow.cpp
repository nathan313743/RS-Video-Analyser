#include "DetailsWindow.h"
#include <qlineedit.h>
#include <qtabwidget.h>

#include "DatabaseAccessor.h"

#include <qpushbutton.h>
#include <QMessageBox>


DetailsWindow::DetailsWindow(const bool editFlag, CodeInterface &codInt, QWidget *parent) 
{
	edit_flag = editFlag;
	QVBoxLayout *topLayout = new QVBoxLayout;

  i_tab = new InterfaceTab(this, codInt, editFlag);
	fTab = new FileTab(this, codInt, editFlag);
	vTab = new VideoTab(this, codInt, editFlag);
	aTab = new AudioTab(this, codInt, editFlag);
	tTab = new TransportTab(this, codInt, editFlag);
	cTab = new TestCaseTab(this, codInt, editFlag);
	sTab = new SignalRootTab(this, codInt, editFlag);


	QTabWidget *tabWidget = new QTabWidget;
	tabWidget->addTab(fTab, "File Details");
	tabWidget->addTab(vTab, "Video");
	tabWidget->addTab(aTab, "Audio");
	tabWidget->addTab(tTab, "Transport");
	tabWidget->addTab(cTab, "Test Case");
	tabWidget->addTab(sTab, "Signal Root");
	tabWidget->addTab(i_tab, "Interface");

	if(editFlag == true)
	{
		setupEditDisplay();
		this->setWindowTitle("File Details (*Edit)");
	}
	else
	{
		setupViewDisplay();
		this->setWindowTitle("File Details");
	}

	topLayout->addWidget(tabWidget);
	topLayout->addWidget(btnBox);

	this->setLayout(topLayout);
	//this->setMinimumSize(200, 200);
  this->resize(500, 350);
}

DetailsWindow::~DetailsWindow()
{
	delete fTab;
	delete vTab;
	delete aTab;
	delete tTab;
	delete cTab;
	delete sTab;

}

void DetailsWindow::setupEditDisplay()
{
	btnBox = new QDialogButtonBox(Qt::Horizontal);

	btnOK = new QPushButton("OK");
	btnCancel = new QPushButton("Cancel");
	btnCancel->setDefault(true);
	btnApply = new QPushButton("Apply");

	connect(btnOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	connect(btnApply, SIGNAL(clicked()), this, SLOT(onAccept()));

	btnBox->addButton(btnOK, QDialogButtonBox::ActionRole);
	btnBox->addButton(btnCancel, QDialogButtonBox::ActionRole);
	btnBox->addButton(btnApply, QDialogButtonBox::ActionRole);
}

void DetailsWindow::setupViewDisplay()
{
	btnBox = new QDialogButtonBox(Qt::Horizontal);
	btnOK = new QPushButton("OK");
	btnOK->setDefault(true);
	connect(btnOK, SIGNAL(clicked()), this, SLOT(onCancel()));
	btnBox->addButton(btnOK, QDialogButtonBox::ActionRole);
}

void DetailsWindow::onOK()
{
	if(edit_flag == true)
	{
		if(confirmMessage())
		{
			writeValues();
		}
		else
		{
			return;
		}
	}
	close();
}

void DetailsWindow::onCancel()
{
	close();
}

void DetailsWindow::onAccept()
{
	if(edit_flag == true)
	{
		if(confirmMessage())
		{
			writeValues();
		}
		else
		{
			return;
		}
	}
}

void DetailsWindow::writeValues()
{

	if(!vTab->writeNewValues())
	{
		errorMessage("Video Table");
		return;
	}

	if(!aTab->writeNewValues())
	{
		errorMessage("Audio Table");
		return;
	}

	if(!tTab->writeNewValues())
	{
		errorMessage("Transport Stream Table");
		return;
	}

	if(!sTab->writeNewValues())
	{
		errorMessage("Signal Root table");
		return;
	}
}

bool DetailsWindow::confirmMessage()
{ 
	QMessageBox msgBox(QMessageBox::Warning, 
		"Save Changes",
		"Any changes made will now be saved.  Proceed?"
		);
	msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();

	switch (ret) 
	{
	case QMessageBox::Ok:
		return true;
		break;
	case QMessageBox::Cancel:
		return false;
		break;
	}

	return false;
}

void DetailsWindow::errorMessage(QString strTable)
{
	QMessageBox msgBox(QMessageBox::Critical, 
		"Writing Error in " + strTable,
		"Changes could not be written to the database.\n"
		"This may be due to an existing entry in either the Video or Audio Table."
		);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int ret = msgBox.exec();
}
