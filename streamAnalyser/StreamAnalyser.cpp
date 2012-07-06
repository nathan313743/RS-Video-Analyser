#include "StreamAnalyser.h"


StreamAnalyser::StreamAnalyser(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
    this->setWindowModality(Qt::WindowModal);
    setupInterface();

    setupGUI();
    if(!check_database())
    {
        this->show();
    }
}

StreamAnalyser::~StreamAnalyser()
{
    delete code_int;
    delete qProBar;
    delete cButton;
}

bool StreamAnalyser::check_database()
{
    if(!code_int->check_database())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Database Error");
        msgBox.setInformativeText("Database is missing.  Can not proceed.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        return true;
    }

    return false;
}



void StreamAnalyser::setupGUI()
{
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    qProBar = new QProgressBar;
    qProBar->setRange(0,1);
    qProBar->setAlignment(Qt::AlignCenter);

    infoLabel = new QLabel(tr("Start"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    cButton = new QPushButton("Cancel");
    connect(cButton, SIGNAL(clicked()), this, SLOT(onCancelClick()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(infoLabel);
    layout->addWidget(qProBar);
    layout->addWidget(cButton);
    createActions();
    createMenus();
    widget->setLayout(layout);
}

void StreamAnalyser::setupInterface()
{
    code_int = new CodeInterface;
    connect(code_int, SIGNAL(updateProgBar(int)), this, SLOT(onProgBar(int)));							//turn progress bar on/off
    connect(code_int, SIGNAL(updateStatus(QString)), this, SLOT(onStatusUpdate(QString)));	//status messages
    connect(code_int, SIGNAL(finished()), this, SLOT(onFinish()));
}

void StreamAnalyser::createActions()
{
    openAct = new QAction(tr("&Choose Folder"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    resetAct = new QAction("&Reset Database", this);
    connect(resetAct, SIGNAL(triggered()), this, SLOT (onReset_db()));
}

void StreamAnalyser::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(resetAct);
}


void StreamAnalyser::openFile()
{
    MyFolderDialog fd(this, code_int);

    // If OK is clicked
    if(fd.exec())
    {
        QStringList selected = fd.get_selected_paths();

        if(selected.size() > 0)
        {
            startProcess(selected);
        }
    }
}

void StreamAnalyser::startProcess(QStringList &paths)
{
    resetAct->setEnabled(false);
    code_int->startProcess(paths);
}

void StreamAnalyser::onFinish()
{
    resetAct->setEnabled(true);
    create_log();
}

void StreamAnalyser::create_log()
{
    QStringList unprocessed = code_int->get_unprocessed_list();
    QStringList skipped = code_int->get_skipped_list();
    QStringList added = code_int->get_added_list();

    LogOutput lo(this, unprocessed, skipped, added);

    if(lo.exec())
    {
        // Nothing to add here yet.
    }


}

void StreamAnalyser::onStatusUpdate(QString update)
{
    infoLabel->setText((update));
}

void StreamAnalyser::onCancelClick()
{
    onStatusUpdate("Please Wait");
    stopThread();
    onStatusUpdate("Cancelled");
}

void StreamAnalyser::onReset_db()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("All data will be deleted");
    msgBox.setInformativeText("Are you sure you want to remove all entries from the database?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int result = msgBox.exec();

    switch(result)
    {
    case QMessageBox::Ok:
        reset_db();
        break;
    }
}

void StreamAnalyser::reset_db()
{
    code_int->reset_db();
}

void StreamAnalyser::stopThread()
{
    code_int->stopThread();						//send stop message
}

void StreamAnalyser::onProgBar(int i)
{
    qProBar->setRange(0,i);			//set progress bar to on

    if(i == 1)
    {
        qProBar->reset();				//turns it off
    }
}



