#include "StartWindow.h"

StartWindow::StartWindow()
{
  createHorizontalGroupBox();

  //stream_analyser->setModal(true);


  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(createHorizontalGroupBox());

  setLayout(mainLayout);
  this->setMinimumWidth(200);

  setWindowTitle(tr("Start"));

  connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
}

QGroupBox* StartWindow::createHorizontalGroupBox()
{
  QGroupBox *horizontalGroupBox = new QGroupBox();
  QHBoxLayout *layout = new QHBoxLayout;
  button = new QPushButton(tr("Start"));

  layout->addWidget(button);
  horizontalGroupBox->setLayout(layout);
  return horizontalGroupBox;
}

void StartWindow::buttonPushed()
{
  stream_analyser = new StreamAnalyser(this);
}
