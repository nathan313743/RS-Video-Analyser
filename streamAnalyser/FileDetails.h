/**************************************************************
 ** Holds all the file details extracted from the video file.
 **************************************************************/

#ifndef FILEDETAILS_H_
#define FILEDETAILS_H_

#include <QString>
#include <QList>

#include "FileDetails.h"
#include "AudioData.h"
#include "TransportDetails.h"
#include "TransData.h"
#include "VideoData.h"

class TransportDetails;

class FileDetails 
{
public:
	QList<AudioData>& get_audio_list();
	QString get_extension();
	QString get_file_name();
	QString get_file_path();
	float get_sizeMB();
	TransportDetails& get_trans_details();
	QList<VideoData>& get_video_list();

	void set(const QString &, const QString &, const QString &, float);
	void set_audio_list(const QList<AudioData> &);
	void set_trans_list(const TransportDetails &);
	void set_video_list(const QList<VideoData> &);

private:
	QList<AudioData> _aud_list;
	QString _extension;
	QString _file_name;
	QString _file_path;
	float _sizeMB;
	TransportDetails _trans_details;
	QList<VideoData> _vid_list;


};

#endif /* FILEDETAILS_H_ */
