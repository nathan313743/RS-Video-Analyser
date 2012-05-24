#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
	create_buttons();
	create_tabs();
	create_layout();
	create_actions();
	chosen_file = "";
}

void MainWindow::create_actions()
{
	connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_recevied_index(const QModelIndex &)));
	connect(buttonOK, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(button_reset, SIGNAL(clicked()), this, SLOT(on_reset()));
	connect(video_tab, SIGNAL(comboChange(QString, QString, QString)), this, SLOT(on_combo_update(QString, QString, QString)));
        connect(audio_tab, SIGNAL(comboChange(QString, QString, QString)), this, SLOT(on_combo_update(QString, QString, QString)));
}

void MainWindow::create_buttons()
{
	buttonOK = new QPushButton("OK");
	buttonCancel = new QPushButton("Cancel");
	button_reset = new QPushButton("Reset");
}

void MainWindow::create_tabs()
{
	//Create Tabs
	video_tab = new VideoTab(this, code_int);
	audio_tab = new AudioTab(this, code_int);
;

}

void MainWindow::create_layout()
{
	//Consolidates the tabs to one window
	tabWidget = new QTabWidget; 
	tabWidget->addTab((video_tab), "Video");
	tabWidget->addTab((audio_tab), "Audio");


	////Create TreeView
	tree_model = new TreeModel(code_int);
	view = new QTreeView();
	view->setModel(tree_model);
	//view->show();
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setColumnWidth(0, 300);

	//Create buttons and LineEdit
	QLabel *lblFile = new QLabel("File: ");
	lineEdit = new QLineEdit();
	lineEdit->setMinimumWidth(300);
	lineEdit->setReadOnly(true);
	


	//Top half of window
	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(view);
	topLayout->addWidget(tabWidget);
	

	//Bottom half of window
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(lblFile);
	bottomLayout->addWidget(lineEdit, 2, Qt::AlignLeft);
	bottomLayout->addWidget(buttonOK, 2, Qt::AlignRight);
	bottomLayout->addWidget(buttonCancel);
	bottomLayout->addWidget(button_reset);


	//Put layouts in GroupBoxes
	QGroupBox *horizontalGroupBox1 = new QGroupBox();
	horizontalGroupBox1->setLayout(topLayout);
	QGroupBox *horizontalGroupBox2 = new QGroupBox();
	horizontalGroupBox2->setLayout(bottomLayout);


	//Add group boxes to overal layout
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(horizontalGroupBox1);
	mainLayout->addWidget(horizontalGroupBox2);

	this->setLayout(mainLayout);
	this->setWindowTitle("Library Browser");
	this->setMinimumSize(200, 200);
	this->resize(1000, 450);

}

void MainWindow::on_reset()
{
	code_int.reset();
	tree_model->update_tree_items();
	emit repopulate_combos();
	emit reset_fields();
	lineEdit->clear();
}

void MainWindow::on_ok_clicked()
{
	emit pass_file(chosen_file);
	this->close();
}

void MainWindow::on_recevied_index(const QModelIndex &index)
{
	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
	int id = item->get_file_ID();
	
	lineEdit->clear();
	QString query = "SELECT file_path FROM File_Properties WHERE pk_file_ID = " + QString::number(id);
	QString folderPath = code_int.execute_query(query);

	query = "SELECT file_name FROM File_Properties WHERE pk_file_ID = " + QString::number(id);
	QString fileName = code_int.execute_query(query);
	
	QString filePath = folderPath + "/" + fileName;
	chosen_file = filePath;

	lineEdit->insert(filePath);
}

void MainWindow::on_combo_update(QString table, QString field, QString value)
{
	code_int.updateTable(table, field, value);
	tree_model->update_tree_items();
	emit repopulate_combos();
}


