#include "AudioData.h"

AudioData::AudioData()
{
}

AudioData::AudioData(float aud_bitrate, const QString &aud_format, 
										const QString &channel, const QString &content, QString const encryption, 
										const QString &lang_code, const QString &sampling)
{
	_aud_bitrate = aud_bitrate;
	_aud_format = aud_format;
	_channel = channel;
	_content = content;
	_encryption = encryption;
	_lang_code = lang_code;
	_sampling = sampling;
}

	float AudioData::get_aud_bitrate()
	{
		return _aud_bitrate;
	}

	QString AudioData::get_aud_format()
	{
		return _aud_format;
	}

	QString AudioData::get_channel()
	{
		return _channel;
	}
	
	QString AudioData::get_content()
	{
		return _content;
	}

	QString AudioData::get_encryption()
	{
		return _encryption;
	}

	QString AudioData::get_lang_code()
	{
		return _lang_code; 
	}

	QString AudioData::get_sampling()
	{
		return _sampling;
	}