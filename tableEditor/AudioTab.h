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
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QCompleter>
#include "CodeInterface.h"
#include "DatabaseAccessor.h"

class AudioTab : public QWidget
{
	Q_OBJECT

public:
	AudioTab(QWidget *, CodeInterface &, const bool);
	~AudioTab();
	bool writeNewValues();

private slots:
	/**************************************************
	 ** Called when a stream from combobox is selected.
	 ** Populates boxes with that stream's values.
	 * @param int - stream number.
	 **************************************************/
	void onComboSelect(int);

private:
	bool no_streams;
	CodeInterface *code_int;
	
	int current_index;
	int* stream_nums;		//stream numbers array

	QComboBox *cmb_aStream;
	QCompleter *fmt_completer;
	QCompleter *sr_completer;
	QCompleter *chn_completer;
	QCompleter *con_completer;
	QCompleter *enc_completer;
	QCompleter *lan_completer;
	
	QDoubleSpinBox *spn_aBitRate;
	
	QLineEdit *edt_aFormat;
	QLineEdit *edt_aSample;
	QLineEdit *edt_aChannel;
	QLineEdit *edt_aContent;
	QLineEdit *edt_aEncryption;
	QLineEdit *edt_aLanguage;

	void createActions();

	/***********************************************************
	 ** Finds the number of audio streams the file has
	 ** in the database.  Numbers are then put into a combobox.
	 ***********************************************************/
	void getStreamNum();	

	/*****************************************************************
	 ** If no streams are avavilable, all editable controls are made
	 ** 'unabled'
	 ****************************************************************/
	void noStreams();

	/**********************************************************
	 ** Populates editable boxes with values from the database.
	 * @param const int - Selected stream number.
	 ***********************************************************/
	void populateBoxes(const int);

	/*****************************************
	 ** Sets whether components are writable.
	 * @param const bool - if true = editable.
	 ******************************************/
	void setReadWrite(const bool);

	/***********************************************************
	 ** Gives editable componets autocomplete features.
	 ** Values that are currently available in the database for
	 ** that field.
	 ************************************************************/
	void setup_autocomplete();

	/************************
	 ** Creates the display.
	 ************************/
	void setupDisplay();





	






};

