#ifndef STARTWINDOW_H_
#define STARTWINDOW_H_

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QAction>
#include <QLayout>

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
