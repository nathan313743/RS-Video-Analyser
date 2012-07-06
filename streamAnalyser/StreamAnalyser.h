#ifndef STREAMANALYSER_H
#define STREAMANALYSER_H

#include <qlabel.h>
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <qmessagebox.h>
#include <qaction.h>
#include <qmenu.h>
#include <qmenubar.h>

#include "CodeInterface.h"
#include "MyFolderDialog.h"
#include "LogOutput.h"

using namespace std;

class StreamAnalyser : public QMainWindow
{
    Q_OBJECT

public:
    StreamAnalyser(QWidget *parent = 0, Qt::WindowFlags = 0);
    ~StreamAnalyser();

public slots:

    /******************************************
     ** Called when processing is finished.
     ** 'Rest Database' button becomes active.
     *******************************************/
    void onFinish();

    /*******************************************************************
     ** Receives status messages and updates the QLabel on the screen.
     * @param QString  - The message to display.
     *******************************************************************/
    void onStatusUpdate(QString);

    /********************************************************
     ** Receives messages and turns the progress bar on or
     ** off accordingly.
     * @param int - 0 = on, 1 = off.
     ********************************************************/
    void onProgBar(int);

private slots:
    /*************************************************
     ** Activated when QFileDialog close.  Starts the
     ** analysing process if a directory was selected.
     **************************************************/
    void openFile();
    void onReset_db();

    /**
     * Stops the thread if the cancel button was clicked during
     * the analysing process.
     */
    void onCancelClick();

private:
    QPushButton *cButton;						//Cancel button
    QMenu *fileMenu;
    QMenu *editMenu;
    CodeInterface *code_int;			//seperate GUI from code
    QLabel *infoLabel;
    QAction *openAct;
    QAction *resetAct;
    QProgressBar *qProBar;

    bool check_database();

    /***********************************
     ** Creates actions for the file menu.
     ************************************/
    void createActions();

    /**************************
     * Create the top file menu
     **************************/
    void createMenus();

    void create_log();

    void reset_db();

    /**
     * Creates GUI layout.
     */
    void setupGUI();

    /****************************************//**
     * Creates the interface object and sets up
     * the signal and slots.
     ********************************************/
    void setupInterface();

    /*********************************//**
     * Starts the analysing process.
     *
     * @param QString& - Directory path.
     *************************************/
    void startProcess(QStringList&);

    /*******************************//**
     * Stops the work thread process.
     **********************************/
    void stopThread();

};

#endif // STREAMANALYSER_H
