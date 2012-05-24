#ifndef STARTWINDOW_H_
#define STARTWINDOW_H_

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QAction>
#include <QLayout>

#include "MainWindow.h"

class StartWindow : public QWidget
{
	Q_OBJECT

public:
	StartWindow();
	
	public slots:
	void buttonPushed();

public slots:
	/****************************************************************
	 ** Receives file path of last selected node from the MainWindow.
	 * @param QString& - file path of selected node.
	 ****************************************************************/
	void on_pass_file(QString&);

private:
	MainWindow *main_window;
	QLabel *_ptrLabel1;	
	QPushButton *button;
	QAction *exitAction;

	QGroupBox* createHorizontalGroupBox();


};

#endif
