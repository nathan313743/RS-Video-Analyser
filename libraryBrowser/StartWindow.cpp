#include "StartWindow.h"

StartWindow::StartWindow()
 {
     createHorizontalGroupBox();
		 main_window = new MainWindow(this);
		 main_window->setModal(true);
   

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(createHorizontalGroupBox());

     setLayout(mainLayout);

     setWindowTitle(tr("Start"));
		   
		 connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
		 connect(main_window, SIGNAL(pass_file(QString&)), this, SLOT(on_pass_file(QString&)));
 }

 QGroupBox* StartWindow::createHorizontalGroupBox()
 {
     QGroupBox *horizontalGroupBox = new QGroupBox();
     QHBoxLayout *layout = new QHBoxLayout;
     button = new QPushButton(tr("Start"));
     _ptrLabel1 = new QLabel("Nothing selected yet");

		 layout->addWidget(button);
		 layout->addWidget(_ptrLabel1);
     horizontalGroupBox->setLayout(layout);
		 return horizontalGroupBox;
 }

 void StartWindow::buttonPushed()
 {
	 main_window->show();
 }

 void StartWindow::on_pass_file(QString &filePath)
 {
	 _ptrLabel1->setText(filePath);
 }