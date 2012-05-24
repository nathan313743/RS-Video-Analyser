/*************************************
 ** Storage class.  Holds audio data.
 *************************************/
#ifndef AudioData_H_
#define AudioData_H_
#include <QString>

using namespace std;

class AudioData 
{
public:
	AudioData();

	AudioData( float, const QString &, const QString &, 
						const QString &, const QString, const QString &,
						const QString &);
	
	float get_aud_bitrate();
	QString get_aud_format();
	QString get_channel();
	QString get_content();
	QString get_encryption();
	QString get_lang_code();
	QString get_sampling();

private:
	float _aud_bitrate;
	QString _aud_format;
	QString _channel;
	QString _content;
	QString _encryption;
	QString _lang_code;
	QString _sampling;
};

#endif /* AudioData_H_ */
