#include "InterfaceTab.h"


InterfaceTab::InterfaceTab(QWidget *parent, CodeInterface &codInt, const bool editFlag) : QWidget(parent)
{
	code_int = &codInt;
	interface_id = -1;
	setupButtons();
	setupTable();
	setupLayout();
	setReadWrite(editFlag);
}

InterfaceTab::~InterfaceTab(void)
{
	delete model;
	delete tableView;

	delete btnAdd;
	delete btnDelete;
}

void InterfaceTab::setupButtons()
{
	btnAdd = new QPushButton("Add");
	btnDelete = new QPushButton("Delete");

	connect(btnAdd, SIGNAL(clicked()), this, SLOT(on_add()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(on_delete()));
}

void InterfaceTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		btnAdd->setEnabled(false);
		btnDelete->setEnabled(false);
	}
}

void InterfaceTab::on_delete()
{
	if(interface_id < 0)			//Check if something has been selected
	{
		return;
	}

	code_int->delete_interface(interface_id);
	QString query = "SELECT pk_interface_id, interface FROM Interface WHERE fk_file_ID = ";
	code_int->update_model(model, query);

}

void InterfaceTab::on_add()
{
	bool ok;
	QString text = QInputDialog::getText(this, "Add Interface","Enter an Interface:", 
		QLineEdit::Normal, "", &ok);
	
	if(ok && !text.isEmpty())
	{
		code_int->add_interface(text);
		QString query = "SELECT pk_interface_id, interface FROM Interface WHERE fk_file_ID = ";
		code_int->update_model(model, query);
	}
}

void InterfaceTab::setupLayout()
{
	QGridLayout *gridLayout = new QGridLayout();


	gridLayout->addWidget(tableView, 0, 0, 10, 1);
	gridLayout->addWidget(btnAdd, 0, 1, 1, 1);
	gridLayout->addWidget(btnDelete, 1, 1, 1, 1);

	this->setLayout(gridLayout);
}

void InterfaceTab::setupTable()
{
	QString strQuery = "SELECT pk_interface_id, interface FROM Interface WHERE fk_file_ID = ";
	model = new QSqlQueryModel();	
	code_int->update_model(model, strQuery);

	tableView = new QTableView();
	tableView->setModel(model);
	tableView->setColumnWidth(1, 280);
	tableView->setColumnHidden(0, true);

	model->setHeaderData(1, Qt::Horizontal, "Interface");

	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_recevied_index(const QModelIndex &)));
}

void InterfaceTab::on_recevied_index(const QModelIndex &index)
{
	int row = index.row();
	interface_id = model->data(tableView->model()->index(row, 0)).toInt();	//Get file name
}