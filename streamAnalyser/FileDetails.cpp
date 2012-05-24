#include "FileDetails.h"

void FileDetails::set(const QString &ext, const QString &name, const QString &path, 
	float size)
{
	_extension = ext;
	_file_name = name;
	_file_path = path;
	_sizeMB = size;
}

QList<AudioData>& FileDetails::get_audio_list()
{
	return _aud_list;
}

QString FileDetails::get_extension()
{
	return _extension;
}

QString FileDetails::get_file_name()
{
	return _file_name;
}

QString FileDetails::get_file_path()
{
	return _file_path;
}

float FileDetails::get_sizeMB()
{
	return _sizeMB;
}

TransportDetails& FileDetails::get_trans_details()
{
	return _trans_details;
}

QList<VideoData>& FileDetails::get_video_list()
{
	return _vid_list;
}

void FileDetails::set_audio_list(const QList<AudioData> &list)
{
	_aud_list = list;
}

void FileDetails::set_trans_list(const TransportDetails &list)
{
	_trans_details = list;
}

void FileDetails::set_video_list(const QList<VideoData> &list)
{

	_vid_list = list;
}
