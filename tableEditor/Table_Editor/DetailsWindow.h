/***************************
 ** Holds the Tabs together.
 ***************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <qdialog.h>
#include <QVBoxLayout>
#include <QTableView>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <QDialogButtonBox>

#include "FileTab.h"
#include "VideoTab.h"
#include "AudioTab.h"
#include "TransportTab.h"
#include "TestCaseTab.h"
#include "DatabaseAccessor.h"
#include "CodeInterface.h"
#include "SignalRootTab.h"
#include "InterfaceTab.h"

class DetailsWindow : public QDialog
{
	Q_OBJECT

public:
	/**********************************************************************************
	 * @param const bool - Edit flag
	 * @param CodeInterface & - Reference to the CodeInterface shared my many classes.
	 ***********************************************************************************/
	DetailsWindow(const bool, CodeInterface &, QWidget *parent = 0);
	~DetailsWindow();

private slots:
	void onOK();
	void onCancel();
	void onAccept();

private:
	void setupEditDisplay();
	void setupViewDisplay();

	FileTab *fTab;
	VideoTab *vTab;
	AudioTab *aTab;
	TransportTab *tTab;
	TestCaseTab *cTab;
	SignalRootTab *sTab;
	InterfaceTab *i_tab;

	QDialogButtonBox *btnBox;
	QPushButton *btnOK;
	QPushButton *btnCancel;
	QPushButton *btnApply;

	bool confirmMessage();
	void errorMessage(QString);
	void writeValues();
	bool edit_flag;
	QString _fileName;
	QTableView *_tableview;
};

#endif
