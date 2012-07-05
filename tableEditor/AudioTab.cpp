#include "AudioTab.h"


AudioTab::AudioTab(QWidget *parent, CodeInterface &codInt, const bool editFlag) : QWidget(parent)
{
	code_int = &codInt;
	setupDisplay();
	getStreamNum();
	createActions();
	setReadWrite(editFlag);
	onComboSelect(0);				//Initialise
	setup_autocomplete();
}

AudioTab::~AudioTab()
{	
	delete fmt_completer;
	delete sr_completer;
	delete chn_completer;
	delete con_completer;
	delete enc_completer;
	delete lan_completer;

	delete edt_aFormat;
	delete edt_aSample;
	delete edt_aChannel;
	delete edt_aContent;
	delete edt_aEncryption;
	delete edt_aLanguage;
	delete spn_aBitRate;
}

void AudioTab::createActions()
{
	connect(cmb_aStream, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboSelect(int)));
}

void AudioTab::getStreamNum()
{
	QStringList valueList = code_int->get_aud_stream_nums();

	int size = valueList.size();

	if(size == 0)
	{
		noStreams();
		return;
	}

	stream_nums = new int[size];	//Array of stream pk ids

	//Map audio ID to combobox
	int count = 1;
	for(int i = 0; i < size; i++)
	{
		stream_nums[i] = valueList.at(i).toInt();						
		cmb_aStream->addItem(QString::number(count));
		count++;
	}

}

void AudioTab::noStreams()
{
	no_streams = true;
	stream_nums = new int[1];	
	cmb_aStream->addItem(QString::number(0));
	edt_aFormat->setEnabled(false);
	spn_aBitRate->setEnabled(false);
	edt_aSample->setEnabled(false);
	edt_aChannel->setEnabled(false);
	edt_aContent->setEnabled(false);
	edt_aEncryption->setEnabled(false);
	edt_aLanguage->setEnabled(false);
}

void AudioTab::onComboSelect(int index)
{
	populateBoxes(stream_nums[index]);
	current_index = stream_nums[index];
}

void AudioTab::populateBoxes(const int streamNum)
{
	if(no_streams == true)
	{
		return;
	}

	QStringList valueList = code_int->populate_aud_boxes(streamNum);

	edt_aFormat->setText(valueList.at(0));
	spn_aBitRate->setValue(valueList.at(1).toDouble());
	edt_aSample->setText(valueList.at(2));
	edt_aChannel->setText(valueList.at(3));
	edt_aContent->setText(valueList.at(4));
	edt_aEncryption->setText(valueList.at(5));
	edt_aLanguage->setText(valueList.at(6));
}

void AudioTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		edt_aFormat->setReadOnly(true);
		spn_aBitRate->setReadOnly(true);
		edt_aSample->setReadOnly(true);
		edt_aChannel->setReadOnly(true);
		edt_aContent->setReadOnly(true);
		edt_aEncryption->setReadOnly(true);
		edt_aLanguage->setReadOnly(true);
	}
}

void AudioTab::setup_autocomplete()
{
	QVector<QStringList> completeList = code_int->get_vid_autocomplete();
	
	//format
	fmt_completer = new QCompleter(completeList.at(0));
	fmt_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aFormat->setCompleter(fmt_completer);

	//sample rate
	sr_completer = new QCompleter(completeList.at(1));
	sr_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aSample->setCompleter(sr_completer);

	//channel
	chn_completer = new QCompleter(completeList.at(2));
	chn_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aChannel->setCompleter(chn_completer);

	//content
	con_completer = new QCompleter(completeList.at(3));
	con_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aContent->setCompleter(con_completer);

	//content
	enc_completer = new QCompleter(completeList.at(4));
	enc_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aEncryption->setCompleter(enc_completer);

	//language
	lan_completer = new QCompleter(completeList.at(5));
	lan_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_aLanguage->setCompleter(lan_completer);
}

void AudioTab::setupDisplay()
{
	QGridLayout *layout = new QGridLayout();
	this->setMaximumSize(250,200);

	//Labels
	QLabel *lbl_aStream = new QLabel(("Select Stream:"));
	QLabel *lbl_aFormat = new QLabel(("Format:"));
	QLabel *lbl_aBitRate = new QLabel(("Bit Rate:"));
	QLabel *lbl_aSample = new QLabel(("Sample Rate:"));
	QLabel *lbl_aChannel = new QLabel(("Channel:"));
	QLabel *lbl_aContent = new QLabel(("Content:"));
	QLabel *lbl_aEncryption = new QLabel(("Encryption:"));
	QLabel *lbl_aLanguage = new QLabel(("Language Code:"));

	//Edit boxes
	cmb_aStream = new QComboBox;
	edt_aFormat = new QLineEdit;
	spn_aBitRate = new QDoubleSpinBox;
	spn_aBitRate->setMaximum(1000000);
	edt_aSample = new QLineEdit;
	edt_aChannel = new QLineEdit;
	edt_aContent = new QLineEdit;
	edt_aEncryption = new QLineEdit;
	edt_aLanguage = new QLineEdit;

	lbl_aStream->setBuddy(cmb_aStream);
	lbl_aFormat->setBuddy(edt_aFormat);
	lbl_aBitRate->setBuddy(spn_aBitRate);
	lbl_aSample->setBuddy(edt_aSample);
	lbl_aChannel->setBuddy(edt_aChannel);
	lbl_aContent->setBuddy(edt_aContent);


	layout->addWidget(lbl_aStream, 0, 0, 1, 1);
	layout->addWidget(cmb_aStream, 0, 1, 1, 1);

	layout->addWidget(lbl_aFormat, 1, 0, 1, 1);
	layout->addWidget(edt_aFormat, 1, 1, 1, 1);

	layout->addWidget(lbl_aBitRate, 2, 0, 1, 1);
	layout->addWidget(spn_aBitRate, 2, 1, 1, 1);

	layout->addWidget(lbl_aSample, 3, 0, 1, 1);
	layout->addWidget(edt_aSample, 3, 1, 1, 1);

	layout->addWidget(lbl_aChannel, 4, 0, 1, 1);
	layout->addWidget(edt_aChannel, 4, 1, 1, 1);

	layout->addWidget(lbl_aContent, 5, 0, 1, 1);
	layout->addWidget(edt_aContent, 5, 1, 1, 1);
	
	layout->addWidget(lbl_aEncryption, 6, 0, 1, 1);
	layout->addWidget(edt_aEncryption, 6, 1, 1, 1);
	
	layout->addWidget(lbl_aLanguage, 7, 0, 1, 1);
	layout->addWidget(edt_aLanguage, 7, 1, 1, 1);
		this->setMaximumSize(350,250);
	this->setLayout(layout);
}


bool AudioTab::writeNewValues()
{
	if(no_streams == true)
	{
		true;
	}

	//get values and send them to the database
	QStringList textBoxVals;
	textBoxVals.push_back(edt_aFormat->text());
	textBoxVals.push_back(QString::number(spn_aBitRate->value()));
	textBoxVals.push_back(edt_aChannel->text());
	textBoxVals.push_back(edt_aContent->text());
	textBoxVals.push_back(edt_aEncryption->text());
	textBoxVals.push_back(edt_aLanguage->text());
	textBoxVals.push_back(edt_aSample->text());

	bool success = code_int->write_aud_values(textBoxVals, current_index);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}

}