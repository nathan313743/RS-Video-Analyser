#ifndef VIDEOTAB_H_
#define VIDEOTAB_H_

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>

#include "CodeInterface.h"


class VideoTab : public QWidget 
{ 
	Q_OBJECT

public:
	VideoTab(QWidget *parent, CodeInterface &);

	
private:
	void createDisplay();
	void createActions();
	void populateBoxes();

	CodeInterface *code_int;

	QGroupBox *groupCodec();
	QGroupBox *contentGroup();
	QGroupBox *groupFrameRate();
	QGroupBox *groupOther();
	QGroupBox *groupResolustion();


	QComboBox *cmb_encryption;
	QComboBox *cmb_video_bitrate;
	QComboBox *cmb_color_matrix;
	QComboBox *cmb_video_format;
	QComboBox *cmb_frame_rate_max;
	QComboBox *cmb_frame_rate_min;
	QComboBox *cmb_aspect_ratio;
	QComboBox *cmb_sampling;
	QComboBox *cmb_frame_rate_scan;
	QComboBox *cmb_res_size;
	QComboBox *cmb_res_standard;

signals:
	void comboChange(QString, QString, QString);


public slots:
	void on_repopulate();
	void on_reset();

private slots:
		void on_aspect_change(QString);
		void on_color_change(QString);
		void on_encryption_change(QString);
		void on_scan_change(QString);
		void on_framerate_change_min(QString);
		void on_framerate_change_max(QString);
		void on_resSize_change(QString);
		void on_resStandard_change(QString);
		void on_sampling_change(QString);
		void on_vidBitrate_change(QString);
		void on_vidFormat_change(QString);

};
#endif
