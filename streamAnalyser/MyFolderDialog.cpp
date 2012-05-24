#include "MyFolderDialog.h"

MyFolderDialog::MyFolderDialog( QWidget *parent, CodeInterface *&codeInt) : QDialog(parent)
{
  this->model_ = new MyFileSystemModel(this, codeInt);
  setup_model(codeInt);
  setup_tree();
  setup_buttons();
  create_actions();
  setup_display();

}


void MyFolderDialog::setup_display()
{
  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addWidget(&tree);

  QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Horizontal);
  btnBox->addButton(btnOK,QDialogButtonBox::ActionRole);
  btnBox->addButton(btnCancel, QDialogButtonBox::ActionRole);
  mainLayout->addWidget(btnBox);

  this->setLayout(mainLayout);
  this->resize(800, 480);
  tree.show();
}

void MyFolderDialog::create_actions()
{
  connect(btnOK, SIGNAL(clicked()), this, SLOT(on_ok()));
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(on_cancel()));
  connect(&tree, SIGNAL(expanded(const QModelIndex &)), model_, SLOT(on_expand(const QModelIndex &)));
  connect(model_, SIGNAL(directoryLoaded(const QString&)), model_, SLOT(on_fetched(const QString&)));

}

void MyFolderDialog::setup_buttons()
{
  btnOK = new QPushButton("OK");
  btnCancel = new QPushButton("Cancel");
  btnCancel->setDefault(true);
}

void MyFolderDialog::setup_model(CodeInterface *&)
{
   model_->setRootPath("");
   model_->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}

void MyFolderDialog::setup_tree()
{
  tree.sortByColumn(0, Qt::AscendingOrder);
  tree.setModel(model_);
  tree.setAnimated(false);
  tree.setIndentation(20);
  tree.setSortingEnabled(true);
  tree.setColumnHidden(1, true);
  tree.setColumnWidth(0, 350);
  tree.expandAll();
  tree.setWindowTitle("Select Folders");
}

void MyFolderDialog::on_ok()
{
  paths_ = model_->get_paths();
  accept();                       // Tells parent that OK has been pressed
  this->close();
}

void MyFolderDialog::on_cancel()
{
  this->close();
}

QStringList MyFolderDialog::get_selected_paths()
{
  return paths_;
}
