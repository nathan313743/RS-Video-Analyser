#pragma once
#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include "DatabaseAccessor.h"
#include <QCompleter>
#include "CodeInterface.h"

class VideoTab : public QWidget
{
	Q_OBJECT

public:
	VideoTab(QWidget *, CodeInterface &, const bool);
	~VideoTab();
	bool writeNewValues();

private slots:
	void onComboSelect(int);

private:
	void invalidMessage(QString);
	void noStreams();
	void getStreamNum();
	void populateBoxes(const int);
	void setupDisplay();
	void createActions();
	void setReadWrite(const bool);
	void setup_autocomplete();

	int* stream_nums;
	CodeInterface *code_int;

	int current_index;
	bool no_streams;

	QCompleter *fmt_completer;
	QCompleter *enc_completer;
	QCompleter *rs_completer;
	QCompleter *rt_completer;
	QCompleter *scn_completer;
	QCompleter *clr_completer;
	QCompleter *ar_completer;
	QCompleter *sam_completer;
	QCompleter *mtn_completer;
	QCompleter *sty_completer;
	QCompleter *dim_completer;

	QGroupBox *videoGroupBox;
	QComboBox *cmb_vStream;
	QDoubleSpinBox *spn_bitrate;
	QDoubleSpinBox *spn_frameRate;
	
	QLineEdit *edt_vFormat;
	QLineEdit *edt_vResSize;
	QLineEdit *edt_vResType;
	QLineEdit *edt_vScan;
	QLineEdit *edt_vColorMatrix;
	QLineEdit *edt_vAspectRatio;
	QLineEdit *edt_vEncryption;
	QLineEdit *edt_vSampling;
	QLineEdit *edt_vDimension;
	QLineEdit *edt_vMotion;
	QLineEdit *edt_vStyle;

};

