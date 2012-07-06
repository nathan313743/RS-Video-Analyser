/**************************************************************
 ** Holds all the file details extracted from the video file.
 **************************************************************/

#ifndef FILEDETAILS_H_
#define FILEDETAILS_H_

#include <QString>
#include <QList>

#include "FileDetails.h"
#include "AudioData.h"
#include "VideoData.h"

class FileDetails 
{
public:
    void set(const QString &ext, const QString &name, const QString &path,
             float size)
    {
        _extension = ext;
        _file_name = name;
        _file_path = path;
        _sizeMB = size;
    }

    QList<AudioData>& get_audio_list()
    {
        return _aud_list;
    }

    QString get_extension()
    {
        return _extension;
    }

    QString get_file_name()
    {
        return _file_name;
    }

    QString get_file_path()
    {
        return _file_path;
    }

    float get_sizeMB()
    {
        return _sizeMB;
    }


    QList<VideoData>& get_video_list()
    {
        return _vid_list;
    }

    void set_audio_list(const QList<AudioData> &list)
    {
        _aud_list = list;
    }

    void set_video_list(const QList<VideoData> &list)
    {

        _vid_list = list;
    }

private:
    QList<AudioData> _aud_list;
    QString _extension;
    QString _file_name;
    QString _file_path;
    float _sizeMB;
    QList<VideoData> _vid_list;
};

#endif /* FILEDETAILS_H_ */
