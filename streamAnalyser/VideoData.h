#ifndef VIDEODATA_H_
#define VIDEODATA_H_
#include <qstring.h>
/********************************************
 ** Storage class.  Holds video stream data.
 ********************************************/
class VideoData 
{
public:
	VideoData();
	VideoData(const QString &, const QString &,	const QString, float, 
						const QString &,const QString &, const QString &, 
						const QString &, float , const QString &);
	
	QString get_aspect_ratio();
	QString get_color();
	QString get_encryption();
	float get_frame_rate();
	QString get_frame_scan();
	QString get_res_size();
	QString get_res_standard();
	QString get_sampling();
	float get_vid_bitrate();
	QString get_vid_format();


private:
	QString _aspect_ratio;
	QString _color_matix;
	QString _encrypted;
	QString _frame_scan;
	float _frame_rate;
	QString _res_size;
	QString _res_standard;
	QString _sampling;
	float _vid_bitrate;
	QString _vid_format;
};

#endif /* VIDEODATA_H_ */
