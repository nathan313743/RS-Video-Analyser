#include "VideoCode.h"

VideoCode::VideoCode()
{

}

void VideoCode::updateValues(QString &field, QString &value)
{
	if(field == "aspect_ratio")
	{
		set_aspect_ratio(value);
	}

	else if(field == "color_matrix")
	{
		set_color_matrix(value);
	}

	else if(field == "content_dimension")
	{
		set_content_dimension(value);
	}

	else if(field == "content_motion")
	{
		set_content_motion(value);
	}

	else if(field == "content_style")
	{
		set_content_style(value);
	}

	else if(field == "encryption")
	{
		set_encryption(value);
	}

	else if(field == "frame_rate_scan")
	{
		set_frame_rate_scan(value);
	}

	else if(field == "frame_rate_value_max")
	{
		set_frame_rate_value_max(value);
	}

	else if(field == "frame_rate_value_min")
	{
		set_frame_rate_value_min(value);
	}

	else if(field == "res_size")
	{
		set_res_size(value);
	}

	else if(field == "res_standard")
	{
		set_res_standard(value);
	}

	else if(field == "sampling")
	{
		set_sampling(value);
	}

	else if(field == "video_bitrate_Kb")
	{
		set_video_bitrate_kb(value);
	}

	else if(field == "video_format")
	{
		set_video_format(value);
	}
}

QStringList VideoCode::get_clauses()
{
	append_clauses();
	return clause_list;
}

void VideoCode::append_clauses()
{
	clause_list.clear();
	if(aspect_ratio_clause != "")
	{
		clause_list.push_back(aspect_ratio_clause);
	}

	if(color_matrix_clause != "")
	{
		clause_list.push_back(color_matrix_clause);
	}

	if(content_dimension_clause != "")
	{
		clause_list.push_back(content_dimension_clause);
	}

	if(content_motion_clause != "")
	{
		clause_list.push_back(content_motion_clause);
	}

	if(content_style_clause != "")
	{
		clause_list.push_back(content_style_clause);
	}

	if(encryption_clause != "")
	{
		clause_list.push_back(encryption_clause);
	}

	if(frame_rate_scan_clause != "")
	{
		clause_list.push_back(frame_rate_scan_clause);
	}

	if(frame_rate_value_max_clause != "")
	{
		clause_list.push_back(frame_rate_value_max_clause);
	}

	if(frame_rate_value_min_clause != "")
	{
		clause_list.push_back(frame_rate_value_min_clause);
	}

	if(res_size_clause != "")
	{
		clause_list.push_back(res_size_clause);
	}

	if(res_standard_clause != "")
	{
		clause_list.push_back(res_standard_clause);
	}

	if(sampling_clause != "")
	{
		clause_list.push_back(sampling_clause);
	}

	if(video_bitrate_kb_clause != "")
	{
		clause_list.push_back(video_bitrate_kb_clause);
	}

	if(video_format_clause != "")
	{
		clause_list.push_back(video_format_clause);
	}
}

void VideoCode::reset()
{
	aspect_ratio_clause = "";
	color_matrix_clause = "";
	content_dimension_clause = "";
	content_motion_clause = "";
	content_style_clause = "";
	encryption_clause = "";
	frame_rate_scan_clause = "";
	frame_rate_value_max_clause = "";
	frame_rate_value_min_clause = "";
	res_size_clause = "";
	res_standard_clause = "";
	sampling_clause = "";
	video_bitrate_kb_clause = "";
	video_format_clause = "";
}

void VideoCode::set_aspect_ratio(QString &value)
{
	if(value == "")
	{
		aspect_ratio_clause = "";
	}
	else
	{
		aspect_ratio_clause = " v.aspect_ratio = '" + value  + "'";
	}
}

void VideoCode::set_color_matrix(QString &value)
{
	if(value == "")
	{
		color_matrix_clause = "";
	}
	else
	{
		color_matrix_clause = " v.color_matrix = '" + value  + "'";
	}
}

void VideoCode::set_content_dimension(QString &value)
{
	if(value == "")
	{
		content_dimension_clause = "";
	}
	else
	{
		content_dimension_clause = " v.content_dimension = '" + value  + "'";
	}
}

void VideoCode::set_content_motion(QString &value)
{
	if(value == "")
	{
		content_motion_clause = "";
	}
	else
	{
		content_motion_clause = " v.content_motion = '" + value  + "'";
	}
}

void VideoCode::set_content_style(QString &value)
{
	if(value == "")
	{
		content_style_clause = "";
	}
	else
	{
		content_style_clause = " v.content_style = '" + value  + "'";
	}
}

void VideoCode::set_encryption(QString &value)
{
	if(value == "")
	{
		encryption_clause = "";
	}
	else
	{
		encryption_clause = " v.encryption = '" + value  + "'";
	}
}

void VideoCode::set_frame_rate_scan(QString &value)
{
	if(value == "")
	{
		frame_rate_scan_clause = "";
	}
	else
	{
		frame_rate_scan_clause = " v.frame_rate_scan = '" + value  + "'";
	}
}

void VideoCode::set_frame_rate_value_max(QString &value)
{
	if(value == "")
	{
		frame_rate_value_max_clause = "";
	}
	else
	{
		frame_rate_value_max_clause = " v.frame_rate_value <= " + value;
	}
}

void VideoCode::set_frame_rate_value_min(QString &value)
{
	if(value == "")
	{
		frame_rate_value_min_clause = "";
	}
	else
	{
		frame_rate_value_min_clause = " v.frame_rate_value >= " + value;
	}
}

void VideoCode::set_res_size(QString &value)
{
	if(value == "")
	{
		res_size_clause = "";
	}
	else
	{
		res_size_clause = " v.res_size = '" + value  + "'";
	}
}

void VideoCode::set_res_standard(QString &value)
{
	if(value == "")
	{
		res_standard_clause = "";
	}
	else
	{
		res_standard_clause = " v.res_standard = '" + value  + "'";
	}
}

void VideoCode::set_sampling(QString &value)
{
	if(value == "")
	{
		sampling_clause = "";
	}
	else
	{
		sampling_clause = " v.sampling = '" + value  + "'";
	}
}

void VideoCode::set_video_bitrate_kb(QString &value)
{
	if(value == "")
	{
		video_bitrate_kb_clause = "";
	}
	else
	{
		video_bitrate_kb_clause = " v.video_bitrate_Kb = " + value;
	}
}

void VideoCode::set_video_format(QString &value)
{
	if(value == "")
	{
		video_format_clause = "";
	}
	else
	{
		video_format_clause = " v.video_format = '" + value  + "'";
	}
}