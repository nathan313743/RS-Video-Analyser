/*********************************************
 ** Defines the Audio tab and its components.
 *********************************************/

#ifndef AUDIO_TAB_H_
#define AUDIO_TAB_H_

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>

#include "CodeInterface.h"

class AudioTab : public QWidget 
{ 
	Q_OBJECT

public:
	AudioTab(QWidget *parent, CodeInterface &);

private:
	void createActions();
	void createDisplay();
	void populateBoxes();

	CodeInterface *code_int;

	QGroupBox *groupCodec();
	QGroupBox *groupOther();

	QComboBox *cmb_audio_format;
	QComboBox *cmb_audio_bitrate;
	QComboBox *cmb_channel;
	QComboBox *cmb_content;
	QComboBox *cmb_encryption;
	QComboBox *cmb_language;
	QComboBox *cmb_sampling;

signals:

	/******************************************
	 ** Emmitted when a combo box is changed.
	 ** @param QString - Table name.
	 ** @param QString - field name.
	 ** @param QString - value
	 ******************************************/
	void comboChange(QString, QString, QString);


	public slots:

   /*******************************************************
    ** Calls method to repopulate combobox after selection
    ** has been made.
    *******************************************************/
		void on_repopulate();

    /************************
     ** Rests combo fields.
     ************************/
    void on_reset();

		private slots:

    /******************************************
			 ** Called when combo box has been changed.
			 ** Emits  comboChange().
			 ** QString - Combo box value selected.
			 ******************************************/
			void on_format_change(QString);
			void on_bitrate_change(QString);
			void on_channel_change(QString);
			void on_content_change(QString);
			void on_encryption_change(QString);
			void on_language_change(QString);
			void on_sampling_change(QString);

};
#endif
