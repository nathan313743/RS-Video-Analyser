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
    AudioData()
    {
    }

    AudioData(float aud_bitrate, const QString &aud_format,
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

    float get_aud_bitrate()
    {
        return _aud_bitrate;
    }

    QString get_aud_format()
    {
        return _aud_format;
    }

    QString get_channel()
    {
        return _channel;
    }

    QString get_content()
    {
        return _content;
    }

    QString get_encryption()
    {
        return _encryption;
    }

    QString get_lang_code()
    {
        return _lang_code;
    }

    QString get_sampling()
    {
        return _sampling;
    }

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
