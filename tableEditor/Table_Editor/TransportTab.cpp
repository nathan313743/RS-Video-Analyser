#include "TransportTab.h"
#include <QButtonGroup>


TransportTab::TransportTab(QWidget *parent, CodeInterface &codInt, const bool editFlag)
{
	code_int = &codInt;
	ts_Data_ID = -1;
	setupTable();
	setupButtons();
	setupDisplay();
	populateBoxes();
	setReadWrite(editFlag);
	setup_autocomplete();
}

TransportTab::~TransportTab()
{
	delete model;;
	delete tableView;

	delete vidNum;
	delete audNum;
	delete loop_length;
	delete spn_bitrate;
	delete edt_packet_size;
	delete edt_standard;
	delete std_completer;
	delete pck_completer;
	delete btnAdd;
	delete btnDelete;
	delete rad_audYes;
	delete rad_audNo;
}

void TransportTab::populateBoxes()
{

	QStringList valueList = code_int->populate_trans_boxes();
	
	if(valueList.at(0).toInt() == 1)
	{
		rad_audYes->setChecked(true);
	}
	else
	{
		rad_audNo->setChecked(true);
	}
	
	audNum->setValue(valueList.at(1).toInt());
	vidNum->setValue(valueList.at(2).toInt());
	loop_length->setValue(valueList.at(3).toInt());
	edt_standard->setText(valueList.at(4));
	spn_bitrate->setValue(valueList.at(5).toDouble());
	edt_packet_size->setText(valueList.at(6));
}

void TransportTab::setupDisplay()
{
	QGridLayout *gridLayout = new QGridLayout();
	QButtonGroup *audGroup = new QButtonGroup;
	QGridLayout *gridLayout1 = new QGridLayout();

	//labels
	QLabel *lbl_audOnly = new QLabel("Audio Only:");
	QLabel *lbl_audService = new QLabel("Number of Audio Services:");
	QLabel *lbl_vidService = new QLabel("Number of Video Services:");
	QLabel *lbl_loopLength = new QLabel("Loop Length (ms)");
	QLabel *lbl_standard = new QLabel("Standard:");
	QLabel *lbl_bitrate = new QLabel("Transport Bitrate (Kb)");
	QLabel *lbl_packet = new QLabel("Transport Packet Size");

	//audio only buttons
	rad_audYes = new QRadioButton("Yes");
	rad_audNo = new QRadioButton("No");
	audGroup->addButton(rad_audYes);
	audGroup->addButton(rad_audNo);
	rad_audNo->setChecked(true);

	//services
	audNum = new QSpinBox;
	vidNum = new QSpinBox;
	loop_length = new QSpinBox;
	loop_length->setMaximum(1000000);
	edt_packet_size = new QLineEdit();
	edt_standard = new QLineEdit();
	spn_bitrate = new QDoubleSpinBox();
	spn_bitrate->setMaximum(1000000);

	QHBoxLayout *radioLayout = new QHBoxLayout;
	radioLayout->addWidget(rad_audYes);
	radioLayout->addWidget(rad_audNo);

	//layout
	gridLayout->addWidget(lbl_audOnly, 0, 0, 1, 1);
	gridLayout->addLayout(radioLayout, 0, 1, 1, 1);
	//gridLayout->addWidget(rad_audNo, 0, 2, 1, 1);

	gridLayout->addWidget(lbl_audService, 1, 0, 1, 1);
	gridLayout->addWidget(audNum, 1, 1, 1, 1);

	gridLayout->addWidget(lbl_vidService, 2, 0, 1, 1);
	gridLayout->addWidget(vidNum, 2, 1, 1, 1);

	gridLayout->addWidget(lbl_loopLength, 3, 0, 1, 1);
	gridLayout->addWidget(loop_length, 3, 1, 1, 1);

	gridLayout->addWidget(lbl_standard, 4, 0, 1, 1);
	gridLayout->addWidget(edt_standard, 4, 1, 1, 1);

	gridLayout->addWidget(lbl_bitrate, 5, 0, 1, 1);
	gridLayout->addWidget(spn_bitrate, 5, 1, 1, 1);

	gridLayout->addWidget(lbl_packet, 6, 0, 1, 1);
	gridLayout->addWidget(edt_packet_size, 6, 1, 1, 1);
		

	gridLayout1->addWidget(tableView, 0, 0, 10, 1);
	gridLayout1->addWidget(btnAdd, 0, 1, 1, 1);
	gridLayout1->addWidget(btnDelete, 1, 1, 1, 1);

	gridLayout->addLayout(gridLayout1, 7, 0, 1, 10);

	
	this->setLayout(gridLayout);
	//this->setMaximumSize(250,120);
}

void TransportTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		vidNum->setReadOnly(true);
		audNum->setReadOnly(true);
		rad_audYes->setEnabled(false);
		rad_audNo->setEnabled(false);
		loop_length->setReadOnly(true);
		edt_packet_size->setReadOnly(true);
		edt_standard->setReadOnly(true);
		spn_bitrate->setReadOnly(true);
		btnAdd->setEnabled(false);
		btnDelete->setEnabled(false);
	}
}

bool TransportTab::writeNewValues()
{
	QStringList textBoxVals;

	int audioOnly = 0;

	if(rad_audYes->isChecked())
	{
		audioOnly = 1;
	}

	textBoxVals.push_back(QString::number(audioOnly));
	textBoxVals.push_back( QString::number(audNum->value()));
	textBoxVals.push_back(QString::number(vidNum->value()));
	textBoxVals.push_back(QString::number(loop_length->value()));
	textBoxVals.push_back(edt_standard->text());
	textBoxVals.push_back(QString::number(spn_bitrate->value()));
	textBoxVals.push_back(edt_packet_size->text());
	textBoxVals.push_back(edt_packet_size->text());

	bool success = code_int->write_trans_values(textBoxVals);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void TransportTab::setup_autocomplete()
{
	QVector<QStringList> list = code_int->get_trans_autocomplete();

	std_completer = new QCompleter(list.at(0));
	std_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_standard->setCompleter(std_completer);

	pck_completer = new QCompleter(list.at(1));
	pck_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_packet_size->setCompleter(pck_completer);

}

void TransportTab::setupTable()
{
	QString strQuery = "SELECT pk_TSdata_ID, data_type FROM TS_Data WHERE fk_file_ID = ";
	model = new QSqlQueryModel();	
	code_int->update_model(model, strQuery);

	tableView = new QTableView();
	tableView->setModel(model);
	
	tableView->setColumnHidden(0, true);
	tableView->setColumnWidth(1, 300);
	model->setHeaderData(1, Qt::Horizontal, tr("Data Type"));

	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_recevied_index(const QModelIndex &)));
}

void TransportTab::on_recevied_index(const QModelIndex &index)
{
	int row = index.row();
	ts_Data_ID = model->data(tableView->model()->index(row, 0)).toInt();	//Get file name
}

void TransportTab::on_delete()
{
	if(ts_Data_ID < 0)
	{
		return;
	}

	code_int->delete_TS_data(ts_Data_ID);
	QString query = "SELECT pk_TSdata_ID, data_type FROM TS_Data WHERE fk_file_ID = ";
	code_int->update_model(model, query);

}

void TransportTab::on_add()
{
	bool ok;
  QString text = QInputDialog::getText(this, "Add Transport Data","Enter data type:",
		QLineEdit::Normal, "", &ok);
	
	if(ok && !text.isEmpty())
	{
		code_int->add_TS_data(text);
		QString query = "SELECT pk_TSdata_ID, data_type FROM TS_Data WHERE fk_file_ID = ";
		code_int->update_model(model, query);
	}
}

void TransportTab::setupButtons()
{
	btnAdd = new QPushButton("Add");
	btnDelete = new QPushButton("Delete");

	connect(btnAdd, SIGNAL(clicked()), this, SLOT(on_add()));
	connect(btnDelete, SIGNAL(clicked()), this, SLOT(on_delete()));
}
