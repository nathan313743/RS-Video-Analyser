#include "VideoTab.h"
#include <qsqlresult.h>

VideoTab::VideoTab(QWidget *parent, CodeInterface &codInt, const bool editFlag) : QWidget(parent)
{
	code_int = &codInt;
	setupDisplay();
	getStreamNum();
	createActions();
	setReadWrite(editFlag);
	onComboSelect(0);		//Initialise
	setup_autocomplete();
}

VideoTab::~VideoTab()
{
	delete fmt_completer;
	delete enc_completer;
	delete rs_completer;
	delete rt_completer;
	delete scn_completer;
	delete clr_completer;
	delete ar_completer;
	delete sam_completer;
	delete mtn_completer;
	delete sty_completer;
	delete dim_completer;


	delete cmb_vStream;
	delete spn_bitrate;
	delete spn_frameRate;
	
	delete edt_vFormat;
	delete edt_vResSize;
	delete edt_vResType;
	delete edt_vScan;
	delete edt_vColorMatrix;
	delete edt_vAspectRatio;
	delete edt_vEncryption;
	delete edt_vSampling;
	delete edt_vDimension;
	delete edt_vMotion;
	delete edt_vStyle;
}

void VideoTab::setReadWrite(const bool editFlag)
{
	if(editFlag != true)
	{
		edt_vFormat->setReadOnly(true);
		spn_bitrate->setReadOnly(true);
		edt_vEncryption->setReadOnly(true);
		edt_vResSize->setReadOnly(true);
		edt_vResType->setReadOnly(true);
		edt_vScan->setReadOnly(true);
		spn_frameRate->setReadOnly(true);
		edt_vColorMatrix->setReadOnly(true);
		edt_vAspectRatio->setReadOnly(true);
		edt_vSampling->setReadOnly(true);
		edt_vDimension->setReadOnly(true);
		edt_vMotion->setReadOnly(true);
		edt_vStyle->setReadOnly(true);
	}
}

void VideoTab::createActions()
{
	connect(cmb_vStream, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboSelect(int)));
}

void VideoTab::onComboSelect(int index)
{
	populateBoxes(stream_nums[index]);
	current_index = stream_nums[index];
}

void VideoTab::getStreamNum()
{
	QStringList valueList = code_int->get_vid_stream_nums();

	int size = valueList.size();

	if(size == 0)
	{
		noStreams();
		return;
	}

	stream_nums = new int[size];					//Array of stream pk ids

	int count = 1;		
	//Map VideoID to combobox
	for(int i = 0; i < size; i++)
	{
		stream_nums[i] = valueList.at(i).toInt();					
		cmb_vStream->addItem(QString::number(count));
		count++;
	}

}

void VideoTab::invalidMessage(QString lineEdit)
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setText(lineEdit + " is invalid");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.setModal(true);
	int ret = msgBox.exec();
}

void VideoTab::setupDisplay()
{

	QGridLayout *gridLayout = new QGridLayout();


	//Labels
	QLabel *lbl_vStream = new QLabel(("Select Stream:"));
	QLabel *lbl_vEncrypt = new QLabel("Encrypted:");
	QLabel *lbl_vFormat = new QLabel(("Format:"));
	QLabel *lbl_vBitRate = new QLabel(("Bit Rate:"));
	QLabel *lbl_vResSize = new QLabel(("Resolution Size:"));
	QLabel *lbl_vResType = new QLabel(("Resolution Type:"));
	QLabel *lbl_vScan = new QLabel(("Scan:"));
	QLabel *lbl_vFrameRate = new QLabel(("Frame Rate"));
	QLabel *lbl_vColorMatrix = new QLabel(("Color Matrix:"));
	QLabel *lbl_vAspectRatio = new QLabel(("Aspect Ratio:"));
	QLabel *lbl_vSamping = new QLabel(("Sampling:"));
	QLabel *lbl_vDimenstion = new QLabel(("Dimenstion:"));
	QLabel *lbl_vMotion = new QLabel(("Motion:"));
	QLabel *lbl_vStyle = new QLabel(("Style:"));

	//Edit boxes
	cmb_vStream = new QComboBox;
	edt_vFormat = new QLineEdit();
	spn_bitrate = new QDoubleSpinBox();
	spn_bitrate->setMaximum(1000000);
	edt_vResSize = new QLineEdit();
	edt_vResType = new QLineEdit();
	edt_vScan = new QLineEdit();
	spn_frameRate = new QDoubleSpinBox();
	edt_vColorMatrix = new QLineEdit();
	edt_vAspectRatio = new QLineEdit();
	edt_vEncryption = new QLineEdit();
	edt_vSampling = new QLineEdit();
	edt_vDimension = new QLineEdit();
	edt_vMotion = new QLineEdit();
	edt_vStyle = new QLineEdit();


	lbl_vStream->setBuddy(cmb_vStream);
	lbl_vFormat->setBuddy(edt_vFormat);
	lbl_vBitRate->setBuddy(spn_bitrate);
	lbl_vResSize->setBuddy(edt_vResSize);
	lbl_vResType->setBuddy(edt_vResType);
	lbl_vScan->setBuddy(edt_vScan);
	lbl_vFrameRate->setBuddy(spn_frameRate);
	lbl_vColorMatrix->setBuddy(edt_vColorMatrix);
	lbl_vAspectRatio->setBuddy(edt_vAspectRatio);

	gridLayout->addWidget(lbl_vStream, 0, 0, 1, 1);
	gridLayout->addWidget(cmb_vStream, 0, 1, 1, 1);

	gridLayout->addWidget(lbl_vFormat, 1, 0, 1, 1);
	gridLayout->addWidget(edt_vFormat, 1, 1, 1, 1);

	gridLayout->addWidget(lbl_vEncrypt, 2, 0, 1, 1);
	gridLayout->addWidget(edt_vEncryption, 2, 1, 1, 1);

	gridLayout->addWidget(lbl_vBitRate, 3, 0, 1, 1);
	gridLayout->addWidget(spn_bitrate, 3, 1, 1, 1);

	gridLayout->addWidget(lbl_vResSize, 4, 0, 1, 1);
	gridLayout->addWidget(edt_vResSize, 4, 1, 1, 1);

	gridLayout->addWidget(lbl_vResType, 5, 0, 1, 1);
	gridLayout->addWidget(edt_vResType, 5, 1, 1, 1);

	gridLayout->addWidget(lbl_vScan, 6, 0, 1, 1);
	gridLayout->addWidget(edt_vScan, 6, 1, 1, 1);

	gridLayout->addWidget(lbl_vFrameRate, 7, 0, 1, 1);
	gridLayout->addWidget(spn_frameRate, 7, 1, 1, 1);

	gridLayout->addWidget(lbl_vColorMatrix, 8, 0, 1, 1);
	gridLayout->addWidget(edt_vColorMatrix, 8, 1, 1, 1);

	gridLayout->addWidget(lbl_vAspectRatio, 9, 0, 1, 1);
	gridLayout->addWidget(edt_vAspectRatio, 9, 1, 1, 1);

	gridLayout->addWidget(lbl_vSamping, 10, 0, 1, 1);
	gridLayout->addWidget(edt_vSampling, 10, 1, 1, 1);

	gridLayout->addWidget(lbl_vDimenstion, 11, 0, 1, 1);
	gridLayout->addWidget(edt_vDimension, 11, 1, 1, 1);

	gridLayout->addWidget(lbl_vMotion, 12, 0, 1, 1);
	gridLayout->addWidget(edt_vMotion, 12, 1, 1, 1);

	gridLayout->addWidget(lbl_vStyle, 13, 0, 1, 1);
	gridLayout->addWidget(edt_vStyle, 13, 1, 1, 1);

	this->setLayout(gridLayout);
}

void VideoTab::populateBoxes(const int streamNum)
{
	if(no_streams == true)
	{
		return;
	}

	QStringList valueList = code_int->populate_vid_boxes(streamNum);

	edt_vAspectRatio->setText(valueList.at(0));
	edt_vColorMatrix->setText(valueList.at(1));
	edt_vDimension->setText(valueList.at(2));
	edt_vMotion->setText(valueList.at(3));
	edt_vStyle->setText(valueList.at(4));
	edt_vEncryption->setText(valueList.at(5));
	edt_vScan->setText(valueList.at(6));
	spn_frameRate->setValue(valueList.at(7).toDouble());
	edt_vResSize->setText(valueList.at(8));
	edt_vResType->setText(valueList.at(9));
	edt_vSampling->setText(valueList.at(10));
	spn_bitrate->setValue(valueList.at(11).toDouble());
	edt_vFormat->setText(valueList.at(12));
}

bool VideoTab::writeNewValues()
{

	if(no_streams == true)
	{
		return true;
	}

	QStringList textBoxVals;
	textBoxVals.push_back(edt_vAspectRatio->text());
	textBoxVals.push_back(edt_vColorMatrix->text());
	textBoxVals.push_back(edt_vDimension->text());
	textBoxVals.push_back(edt_vMotion->text());
	textBoxVals.push_back(edt_vStyle->text());
	textBoxVals.push_back(edt_vEncryption->text());
	textBoxVals.push_back(edt_vScan->text());
	textBoxVals.push_back(QString::number(spn_frameRate->value()));
	textBoxVals.push_back(edt_vResSize->text());
	textBoxVals.push_back(edt_vResType->text());
	textBoxVals.push_back(edt_vSampling->text());
	textBoxVals.push_back(QString::number(spn_bitrate->value()));
	textBoxVals.push_back(edt_vFormat->text());
	textBoxVals.push_back(QString::number(spn_bitrate->value()));

	bool success = code_int->write_vid_values(textBoxVals, current_index);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void VideoTab::noStreams()
{
	no_streams = true;
	stream_nums = new int[1];	
	cmb_vStream->addItem(QString::number(0));
	edt_vFormat->setEnabled(false);
	edt_vEncryption->setEnabled(false);
	spn_bitrate->setEnabled(false);
	edt_vResSize->setEnabled(false);
	edt_vResType->setEnabled(false);
	edt_vScan->setEnabled(false);
	spn_frameRate->setEnabled(false);
	edt_vColorMatrix->setEnabled(false);
	edt_vAspectRatio->setEnabled(false);
	edt_vSampling->setEnabled(false);
	edt_vDimension->setEnabled(false);
	edt_vMotion->setEnabled(false);
	edt_vStyle->setEnabled(false);
}

void VideoTab::setup_autocomplete()
{
	QVector<QStringList> completeList = code_int->get_vid_autocomplete();

	fmt_completer = new QCompleter(completeList.at(0));
	fmt_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vFormat->setCompleter(fmt_completer);


	
	enc_completer = new QCompleter(completeList.at(1));
	enc_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vEncryption->setCompleter(enc_completer);


	
	rs_completer = new QCompleter(completeList.at(2));
	rs_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vResSize->setCompleter(rs_completer);

	
	rt_completer = new QCompleter(completeList.at(3));
	rt_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vResType->setCompleter(rt_completer);

	
	scn_completer = new QCompleter(completeList.at(4));
	scn_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vScan->setCompleter(scn_completer);

	
	
	clr_completer = new QCompleter(completeList.at(5));
	clr_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vColorMatrix->setCompleter(clr_completer);


	
	ar_completer = new QCompleter(completeList.at(6));
	ar_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vAspectRatio->setCompleter(ar_completer);

	
	
	sam_completer = new QCompleter(completeList.at(7));
	sam_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vSampling->setCompleter(sam_completer);

	
	
	dim_completer = new QCompleter(completeList.at(8));
	dim_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vDimension->setCompleter(dim_completer);


	
	mtn_completer = new QCompleter(completeList.at(9));
	mtn_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vMotion->setCompleter(mtn_completer);

	
	sty_completer = new QCompleter(completeList.at(10));
	sty_completer->setCaseSensitivity(Qt::CaseInsensitive);
	edt_vStyle->setCompleter(sty_completer);
}