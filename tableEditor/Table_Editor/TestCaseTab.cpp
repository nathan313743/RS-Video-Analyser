#include "TestCaseTab.h"


TestCaseTab::TestCaseTab(QWidget *parent, CodeInterface &codInt, const bool editFlag)
{
	code_int = &codInt;
	test_ID = -1;
	setupButtons();
	setupTable();
	setupLayout();
	setReadWrite(editFlag);
}

TestCaseTab::~TestCaseTab(void)
{
	delete model;
	delete tableView;

	delete btnAdd;
	delete btnDelete;
}

void TestCaseTab::setupButtons()
{
	btnAdd = new QPushButton("Add");
	btnDelete = new QPushButton("Delete");

	connect(btnAdd, SIGNAL(clicked()), this, SLOT(on_add()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(on_delete()));
}

void TestCaseTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		btnAdd->setEnabled(false);
		btnDelete->setEnabled(false);
	}
}

void TestCaseTab::on_delete()
{
	if(test_ID < 0)
	{
		return;
	}

	code_int->delete_case(test_ID);
	QString query = "SELECT pk_test_ID, test_case FROM Test_Case WHERE fk_file_ID = ";
	code_int->update_model(model, query);

}

void TestCaseTab::on_add()
{
	bool ok;
	QString text = QInputDialog::getText(this, "Add Case","Enter a case:", 
		QLineEdit::Normal, "", &ok);
	
	if(ok && !text.isEmpty())
	{
		code_int->add_case(text);
		QString query = "SELECT pk_test_ID, test_case FROM Test_Case WHERE fk_file_ID = ";
		code_int->update_model(model, query);
	}
}

void TestCaseTab::setupLayout()
{
	QGridLayout *gridLayout = new QGridLayout();


	gridLayout->addWidget(tableView, 0, 0, 10, 1);
	gridLayout->addWidget(btnAdd, 0, 1, 1, 1);
	gridLayout->addWidget(btnDelete, 1, 1, 1, 1);

	this->setLayout(gridLayout);
}

void TestCaseTab::setupTable()
{
	QString strQuery = "SELECT pk_test_ID, test_case FROM Test_Case WHERE fk_file_ID = ";
	model = new QSqlQueryModel();	
	code_int->update_model(model, strQuery);

	tableView = new QTableView();
	tableView->setModel(model);
	tableView->setColumnWidth(1, 280);
	tableView->setColumnHidden(0, true);

	model->setHeaderData(1, Qt::Horizontal, tr("Test Case"));

	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_recevied_index(const QModelIndex &)));
}

void TestCaseTab::on_recevied_index(const QModelIndex &index)
{
	int row = index.row();
	test_ID = model->data(tableView->model()->index(row, 0)).toInt();	//Get file name
}