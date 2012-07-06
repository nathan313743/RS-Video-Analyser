
#include "QueryData.h"


QueryData::QueryData()
{
	setup_tables();
	setup_File_Properties_fields();
	setup_Video_fields();
	setup_Audio_fields();
}

QueryData::~QueryData()
{
}

void QueryData::setup_tables()
{
	QStringList values;

	values << "File_Properties" << "File Properties";
	tables.push_back(values);

	values.clear();
	values << "Video" << "Video";
	tables.push_back(values);

	values.clear();
	values << "Audio" << "Audio";
	tables.push_back(values);

}

void QueryData::setup_File_Properties_fields()
{
	QStringList values;

	values << "date_added" << "Date Added";
	file_fields.push_back(values);

	values.clear();
	values << ", extension" << "Extension";
	file_fields.push_back(values);

	values.clear();
	values << ", file_name" << "File Name";
	file_fields.push_back(values);

	values.clear();
	values << ", file_path" << "File Path";
	file_fields.push_back(values);

	values.clear();
	values << ", size_MB" << "Size (MB)";
	file_fields.push_back(values);
}

void QueryData::setup_Video_fields()
{
	QStringList values;

	values << "aspect_ratio" << "Aspect Ratio";
	video_fields.push_back(values);

	values.clear();
	values << ", color_matrix" << "Color Matrix";
	video_fields.push_back(values);

	values.clear();
	values << ", content_dimension" << "Dimension";
	video_fields.push_back(values);

	values.clear();
	values << ", content_motion" << "Motion";
	video_fields.push_back(values);

	values.clear();
	values << ", content_style" << "Style";
	video_fields.push_back(values);

	values.clear();
	values << ", encryption" << "Encryption";
	video_fields.push_back(values);

	values.clear();
	values << ", frame_rate_scan" << "Scan";
	video_fields.push_back(values);

	values.clear();
	values << ", frame_rate_value" << "Frame Rate";
	video_fields.push_back(values);

	values.clear();
	values << ", res_size" << "Resolution Size";
	video_fields.push_back(values);

	values.clear();
	values << ", res_standard" << "Standard";
	video_fields.push_back(values);

	values.clear();
	values << ", sampling" << "Sampling";
	video_fields.push_back(values);

	values.clear();
	values << ", video_bitrate_Kb" << "Video Bitrate (Kb)";
	video_fields.push_back(values);

	values.clear();
	values << ", video_format" << "Video Format";
	video_fields.push_back(values);
}

void QueryData::setup_Audio_fields()
{
	QStringList values;

	values << "audio_format" << "Audio Format";
	audio_fields.push_back(values);

	values.clear();
	values << ", audio_bitrate_Kb" << "Audio Bitrate (Kb)";
	audio_fields.push_back(values);

	values.clear();
	values << ", channel" << "Channel";
	audio_fields.push_back(values);

	values.clear();
	values << ", content" << "Content";
	audio_fields.push_back(values);

	values.clear();
	values << ", encryption" << "Encryption";
	audio_fields.push_back(values);

	values.clear();
	values << ", language_code" << "Language Code";
	audio_fields.push_back(values);

	values.clear();
	values << ", sampling" << "Sampling";
	audio_fields.push_back(values);
}


QList<QStringList> QueryData::get_tables()
{
	return tables;
}

QList<QStringList> QueryData::get_File_Properties_fields()
{
	return file_fields;
}

QList<QStringList> QueryData::get_Video_fields()
{
	return video_fields;
}

QList<QStringList> QueryData::get_Audio_fields()
{
	return audio_fields;
}
