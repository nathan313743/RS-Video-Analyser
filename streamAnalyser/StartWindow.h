#ifndef STARTWINDOW_H_
#define STARTWINDOW_H_

#include <QWidget>
#include <qstring.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qlayout.h>

#include "StreamAnalyser.h"

class StartWindow : public QWidget
{
	Q_OBJECT

public:
	StartWindow();
	
	public slots:
	void buttonPushed();

private:
	StreamAnalyser *stream_analyser;
	QPushButton *button;
	QAction *exitAction;

	QGroupBox* createHorizontalGroupBox();


};

#endif
