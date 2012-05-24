#ifndef SignalRootTab_H_
#define SignalRootTab_H_
#include <qwidget.h>
#include <qlineedit.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qcompleter.h>
#include "CodeInterface.h"


class SignalRootTab : public QWidget
{
	Q_OBJECT

public:
	SignalRootTab(QWidget *, CodeInterface &, const bool);
	~SignalRootTab();
	bool writeNewValues();

private:
	CodeInterface *code_int;
	
	QLineEdit *edt_region;
	QLineEdit *edt_producer;
	QLineEdit *edt_source;

	QCompleter *reg_completer;
	QCompleter *prd_completer;
	QCompleter *src_completer;

	void populate_boxes();
	void setup_autocomplete();
	void setupDisplay();
	void setReadWrite(const bool);


};
#endif