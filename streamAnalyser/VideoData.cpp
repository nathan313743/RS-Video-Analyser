#include "VideoData.h"

VideoData::VideoData()
{
}

VideoData::VideoData(const QString &aspect_ratio, const QString &color_matix,
	const QString encrypted, float frame_rate, const QString &frame_scan,
	const QString &res_size, const QString &res_standard, 
	const QString &sampling, float vid_bitrate, const QString &vid_format)
{
	_aspect_ratio = aspect_ratio;
	_color_matix = color_matix;
	_encrypted = encrypted;
	_frame_rate = frame_rate;
	_frame_scan = frame_scan;
	_res_size = res_size;
	_res_standard = res_standard;
	_sampling = sampling;
	_vid_bitrate = vid_bitrate;
	_vid_format = vid_format;
}

QString VideoData::get_aspect_ratio()
{
	return _aspect_ratio; 
}

QString VideoData::get_color()
{
	return _color_matix;
}

QString VideoData::get_encryption()
{
	return _encrypted;
}

float VideoData::get_frame_rate()
{
	return _frame_rate;
}

QString VideoData::get_frame_scan()
{
	return _frame_scan;
}

QString VideoData::get_res_size()
{
	return _res_size;
}

QString VideoData::get_res_standard()
{
	return _res_standard;
}

QString VideoData::get_sampling()
{
	return _sampling;
}

float VideoData::get_vid_bitrate()
{
	return _vid_bitrate;
}

QString VideoData::get_vid_format()
{
	return _vid_format;
}