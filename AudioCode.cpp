#include "AudioCode.h"
AudioCode::AudioCode()
{

}

void AudioCode::append_clauses()
{
	clause_list.clear();
	if(audio_format_clause != "")
	{
		clause_list.push_back(audio_format_clause);
	}

	if(audio_bitrate_Kb_clause != "")
	{
		clause_list.push_back(audio_bitrate_Kb_clause);
	}

	if(channel_clause != "")
	{
		clause_list.push_back(channel_clause);
	}
		
	if(content_clause != "")
	{
		clause_list.push_back(content_clause);
	}

	if(encryption_clause != "")
	{
		clause_list.push_back(encryption_clause);
	}

	if(language_code_clause != "")
	{
		clause_list.push_back(language_code_clause);
	}

	if(encryption_clause != "")
	{
		clause_list.push_back(encryption_clause);
	}

	if(sampling_clause != "")
	{
		clause_list.push_back(sampling_clause);
	}

}

QStringList AudioCode::get_clauses()
{
	append_clauses();
	return clause_list;
}

void AudioCode::reset()
{
	audio_format_clause = "";
	audio_bitrate_Kb_clause = "";
	channel_clause = "";
	content_clause = "";
	encryption_clause = "";
	language_code_clause = "";
	sampling_clause = "";
}

void AudioCode::set_audio_format(QString &value)
{
	if(value == "")
	{
		audio_format_clause = "";
	}
	else
	{
		audio_format_clause = " a.audio_format = '" + value  + "'";
	}
}

void AudioCode::set_audio_bitrate_Kb(QString &value)
{
	if(value == "")
	{
		audio_bitrate_Kb_clause = "";
	}
	else
	{
		audio_bitrate_Kb_clause = " a.audio_bitrate_Kb = " + value;
	}
}

void AudioCode::set_channel(QString &value)
{
	if(value == "")
	{
		channel_clause = "";
	}
	else
	{
		channel_clause = " a.channel = '" + value  + "'";
	}
}

void AudioCode::set_content(QString &value)
{
	if(value == "")
	{
		content_clause = "";
	}
	else
	{
		content_clause = " a.content = '" + value  + "'";
	}
}

void AudioCode::set_encryption(QString &value)
{
	if(value == "")
	{
		encryption_clause = "";
	}
	else
	{
		encryption_clause = " a.encryption = '" + value  + "'";
	}
}

void AudioCode::set_language_code(QString &value)
{
	if(value == "")
	{
		language_code_clause = "";
	}
	else
	{
		language_code_clause = " a.language_code = '" + value  + "'";
	}
}

void AudioCode::set_sampling(QString &value)
{
	if(value == "")
	{
		sampling_clause = "";
	}
	else
	{
		sampling_clause = " a.sampling = '" + value  + "'";
	}
}

void AudioCode::updateValues(QString &field, QString &value)
{
	if(field == "audio_format")
	{
		set_audio_format(value);
	}

	else if(field == "audio_bitrate_Kb")
	{
		set_audio_bitrate_Kb(value);
	}

	else if(field == "channel")
	{
		set_channel(value);
	}

	else if(field == "content")
	{
		set_content(value);
	}

	else if(field == "encryption")
	{
		set_encryption(value);
	}

	else if(field == "language_code")
	{
		set_language_code(value);
	}

	else if(field == "sampling")
	{
		set_sampling(value);
	}

}