#pragma once
#include <qwidget.h>
#include <QGroupBox>
#include <qradiobutton.h>
#include <QVBoxLayout>
#include <QLabel>
#include <qspinbox.h>
#include "DatabaseAccessor.h"
#include <qlineedit.h>
#include <QDoubleSpinBox>
#include <qcompleter.h>
#include <qtableview.h>
#include <QPushButton>
#include <QInputDialog>

#include "CodeInterface.h"

class TransportTab : public QWidget
{
	Q_OBJECT

public:
	TransportTab(QWidget *, CodeInterface &, const bool);
	~TransportTab();

	bool writeNewValues();

	private slots:
		void on_recevied_index(const QModelIndex &index);
		void on_delete();
		void on_add();

private:
	int ts_Data_ID;
	CodeInterface *code_int;
	QSqlQueryModel *model;;
	QTableView *tableView;

	QSpinBox *vidNum;
	QSpinBox *audNum;
	QSpinBox *loop_length;
	QDoubleSpinBox *spn_bitrate;
	QLineEdit *edt_packet_size;
	QLineEdit *edt_standard;
	QCompleter *std_completer;
	QCompleter *pck_completer;
	QPushButton *btnAdd;
	QPushButton *btnDelete;

	void setup_autocomplete();
	void setupTable();
	void setupButtons();
	void populateBoxes();
	void setupDisplay();
	void setReadWrite(const bool);

	QRadioButton *rad_audYes;
	QRadioButton *rad_audNo;
};

