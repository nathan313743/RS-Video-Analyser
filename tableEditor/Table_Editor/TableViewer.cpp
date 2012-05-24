#include "TableViewer.h"
#include <qvariant.h>

TableViewer::TableViewer(QWidget *parent) : QDialog(parent)
{
	file_ID = -1;

	setupTable();
	setupButtons();
	QGridLayout *layout = new QGridLayout();
	layout->addWidget(tableView, 0, 0, 20, 1);
	layout->addWidget(btnView, 0, 1, 1, 1);
	layout->addWidget(btnEdit, 1, 1, 1, 1);
	layout->addWidget(btnDelete, 2, 1, 1, 1);
	layout->addWidget(btnCancel, 3, 1, 1, 1);
	this->setLayout(layout);
	this->resize(700, 400);
}

TableViewer::~TableViewer()
{
}

void TableViewer::setupTable()
{
	QString strQuery = "SELECT pk_file_ID, file_name, file_path FROM File_Properties";
	model = new QSqlQueryModel();	
	
	code_int.update_model_main(model, strQuery);

	tableView = new QTableView();
	tableView->setModel(model);
	tableView->setColumnWidth(1, 280);
	tableView->setColumnWidth(2, 400);
	tableView->setColumnHidden(0, true);

	model->setHeaderData(1, Qt::Horizontal, tr("File Name"));
	model->setHeaderData(2, Qt::Horizontal, tr("File Path"));

	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onReceviedIndex(const QModelIndex &)));
}

void TableViewer::setupButtons()
{
	btnView = new QPushButton("View");
	btnEdit = new QPushButton("Edit");
	btnDelete = new QPushButton("Delete");
	btnCancel = new QPushButton("Cancel");

	connect(btnView, SIGNAL(clicked()), this, SLOT(onView()));
	connect(btnEdit, SIGNAL(clicked()), this, SLOT(onEdit()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(onDelete()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

}

void TableViewer::onReceviedIndex(const QModelIndex &index)
{
	int row = index.row();
	file_ID = model->data(tableView->model()->index(row, 0)).toInt();	//Get file name
}

void TableViewer::onView()
{
	if(file_ID < 0)
	{
		return;
	}
	
	show_details_window(false);
}

void TableViewer::show_details_window(bool editFlag)
{
	code_int.set_file_ID(file_ID);
	DetailsWindow dWindow(editFlag, code_int, this);
	dWindow.exec();
}

void TableViewer::onEdit()
{
	if(file_ID < 0)
	{
		return;
	}

	show_details_window(true);
}

void TableViewer::onDelete()
{
	if(file_ID < 0)
	{
		return;
	}

	QMessageBox msgBox(QMessageBox::Warning, 
		"Delete File From Database",
		"Are you sure you want to remove this file from the database?"
		);
	msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();

	switch (ret) 
	{
	case QMessageBox::Yes:
		break;
	case QMessageBox::No:
		return;
		break;
	}
	
	if(code_int.delete_file(file_ID) != true)
	{
		errorMessage(QString::number(file_ID) + " could not be deleted");
	}

	QString strQuery = "SELECT pk_file_ID, file_name, file_path FROM File_Properties";
	code_int.update_model_main(model, strQuery);
}

void TableViewer::onCancel()
{
	close();
}

void TableViewer::errorMessage(QString strError)
{
	QMessageBox msgBox(QMessageBox::Warning, "Error", strError);
	msgBox.setStandardButtons(QMessageBox::Ok);
	int ret = msgBox.exec();
}
