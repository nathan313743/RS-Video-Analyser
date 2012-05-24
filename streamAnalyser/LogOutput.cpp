#include "LogOutput.h"


LogOutput::LogOutput(QWidget *parent,  QStringList& unprocessed, QStringList& skipped, QStringList& added) : QDialog(parent)
{
  create_buttons();
  create_layout();
  set_text(unprocessed,skipped, added);
}

void LogOutput::create_buttons()
{
  btnBox = new QDialogButtonBox(Qt::Horizontal);
  QPushButton *btnOK = new QPushButton("OK");
  btnBox->addButton(btnOK,QDialogButtonBox::ActionRole);
  connect(btnOK, SIGNAL(clicked()), this, SLOT(close()));
}

void LogOutput::create_layout()
{
  QVBoxLayout *mainLayout = new QVBoxLayout;

  textEdit = new QTextEdit;
  textEdit->setReadOnly(true);


  mainLayout->addWidget(textEdit);
  mainLayout->addWidget(btnBox);

  this->setLayout(mainLayout);
  this->resize(1000, 500);
}

void LogOutput::set_text(QStringList& unprocessed, QStringList& skipped, QStringList& added)
{
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("yyyy-dd-MM_hh.mm.ss");

  QString output = "Log: (" + date + ")";

  output += "<br />";
  output += "<br />";
  output += "Number of files added to database: " + QString::number(added.size()) + "<br />" ;

  for(QStringList::const_iterator itr1 = added.begin(); added.end() != itr1 ; ++itr1)
  {
    output += "<br />" + *itr1;
  }


  output += "<br />";
  output += "<br />";
  output += "<br />";
  output += "Number of unprocessed files: " + QString::number(unprocessed.size()) + "<br />" ;

  for(QStringList::const_iterator itr1 = unprocessed.begin(); unprocessed.end() != itr1 ; ++itr1)
  {
    output += "<br />" + *itr1;
  }

  output += "<br />";
  output += "<br />";
  output += "<br />";
  output += "Number of skipped files (already in database): " + QString::number(skipped.size()) + "<br />" ;

  for(QStringList::const_iterator itr1 = skipped.begin(); skipped.end() != itr1 ; ++itr1)
  {
    output += "<br />" + *itr1;
  }

  textEdit->setHtml(output);

	output.replace("<br />", "\n");

	QFile file("C:/temp/stream_analyser_log_" + date + ".txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{

	}

    QTextStream out(&file);
    out << output;

}

