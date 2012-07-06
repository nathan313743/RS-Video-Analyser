#include "StartWindow.h"

StartWindow::StartWindow()
{

  //stream_analyser->setModal(true);


  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(createHorizontalGroupBox());

  setLayout(mainLayout);
  this->setMinimumWidth(200);

  setWindowTitle(tr("Start"));

  connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
}

QGroupBox* StartWindow::createHorizontalGroupBox()
{
  QGroupBox *horizontalGroupBox = new QGroupBox(this);
  QHBoxLayout *layout = new QHBoxLayout(this);
  button = new QPushButton(tr("Start"), this);

  layout->addWidget(button);
  horizontalGroupBox->setLayout(layout);
  return horizontalGroupBox;
}

void StartWindow::buttonPushed()
{
  stream_analyser = new StreamAnalyser(this);
}
