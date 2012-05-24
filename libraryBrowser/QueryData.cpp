
#include "QueryData.h"


QueryData::QueryData()
{
	setup_tables();
	setup_File_Properties_fields();
	setup_Video_fields();
	setup_Audio_fields();
	setup_Signal_Root_fields();
	setup_Transport_Stream_fields();
	setup_TS_Data_fields();
	setup_Test_Case_fields();
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

	values.clear();
	values << "Signal Root" << "Signal Root";
	tables.push_back(values);

	values.clear();
	values << "Transport Stream" << "Transport Stream";
	tables.push_back(values);

	values.clear();
	values << "Test Case" << "Test Case";
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

void QueryData::setup_Signal_Root_fields()
{
	QStringList values;

	values << "region" << "Region";
	signal_fields.push_back(values);

	values.clear();
	values << ", producer" << "Producer";
	signal_fields.push_back(values);

	values.clear();
	values << ", source" << "Source";
	signal_fields.push_back(values);
}

void QueryData::setup_Transport_Stream_fields()
{
	QStringList values;

	values << "audio_only" << "Audio Only";
	trans_fields.push_back(values);

	values.clear();
	values << ", num_aud_services" << "Audio Services";
	trans_fields.push_back(values);

	values.clear();
	values << ", num_vid_services" << "Video Services";
	trans_fields.push_back(values);

	values.clear();
	values << ", loop_length_ms" << "Loop Length (ms)";
	trans_fields.push_back(values);

	values.clear();
	values << ", standard" << "Standard";
	trans_fields.push_back(values);

	values.clear();
	values << ", ts_bitrate_Kb" << "TS Bitrate (Kb)";
	trans_fields.push_back(values);

	values.clear();
	values << ", ts_packet_size" << "TS Packet Size";
	trans_fields.push_back(values);
}

void QueryData::setup_TS_Data_fields()
{
	QStringList values;

	values << "data_type" << "Data Type";
	ts_data_fields.push_back(values);

}

void QueryData::setup_Test_Case_fields()
{
	QStringList values;

	values << "test_case" << "Test Case";
	test_case_fields.push_back(values);
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

QList<QStringList> QueryData::get_Signal_Root_fields()
{
	return signal_fields;
}

QList<QStringList> QueryData::get_Transport_Stream_fields()
{
	return trans_fields;
}

QList<QStringList> QueryData::get_TS_Data_fields()
{
	return ts_data_fields;
}

QList<QStringList> QueryData::get_Test_Case_fields()
{
	return test_case_fields;
}