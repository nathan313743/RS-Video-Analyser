#include "FileProcessor.h"
#include <qdebug.h>
#include <qbytearray.h>

String FileProcessor::convertToMediaString(QString str)
{
    QByteArray str1 = str.toAscii();
    String str2;										//MediaInfo String

    for(int i = 0; i < str.size(); i++)
    {
        str2.push_back(str1[i]);
    }

    return str2;
}

QList<FileDetails> FileProcessor::process(const QStringList& filePaths, bool *&stop_flag)
{
    QList<FileDetails> processed_list;
    MediaInfo MI;
    MI.Option(_T("ParseSpeed"), _T("0.3"));
    QString strStatus;

    for(int i = 0; i < filePaths.size(); i++)
    {
        //If the thread has been asked to prematurely stop
        if(*stop_flag == true)
        {
            processed_list.clear();
            return processed_list;
        }

        //Status Message
        strStatus = "Processing: (";
        strStatus += QString::number(i+1);
        strStatus += " of ";
        strStatus += QString::number(filePaths.size());
        strStatus += ")";
        emit updateStatus(strStatus);

        //Convert std string to MediaInfoString
        String str = convertToMediaString(filePaths.at(i));

        //Open file
        size_t opened = MI.Open(str);

        if(opened == 0)
        {
            unprocessed.push_back(filePaths.at(i));
            qDebug() << "Cannot open: " << filePaths.at(i);
            continue;	//File cannot be opened
        }

        //Get num of video streams
        String result;
        result = MI.Get(Stream_General, 0, _T("VideoCount"), Info_Text, Info_Name).c_str();
        QString num = convertToQString(result);
        int numVidStreams = num.toInt();

        //Get num of audio streams
        result = MI.Get(Stream_General, 0, _T("AudioCount"), Info_Text, Info_Name).c_str();
        num = convertToQString(result);
        int numAudStreams = num.toInt();

        if(numVidStreams == 0 && numAudStreams == 0)
        {
            unprocessed.push_back(filePaths.at(i));
            qDebug() << "Cannot open: " << filePaths.at(i);
            continue;	//File not valid video/audio
        }

        //Assign file details
        FileDetails fd;
        fileProcess(MI, fd);

        //Assign video details
        QList<VideoData> vecVD;
        videoProcess(MI, numVidStreams, vecVD);
        fd.set_video_list(vecVD);

        //Assign audio details
        QList<AudioData> vecAD;
        audioProcess(MI, numAudStreams, vecAD);
        fd.set_audio_list(vecAD);



        processed_list.push_back(fd);
    }

    MI.Close();
    return processed_list;
}

void FileProcessor::fileProcess(MediaInfo &MI, FileDetails &fileDetails)
{
    String result;

    //File path
    result = MI.Get(Stream_General, 0, _T("FileName"), Info_Text, Info_Name).c_str();
    QString absolute_path = convertToQString(result);

    int index = 0;

    //file name
    index = absolute_path.lastIndexOf("/");
    QString file_name = absolute_path.mid(index + 1);

    //folder path
    QString folder_path = absolute_path.left(index);

    //file extension
    index = absolute_path.lastIndexOf(".");
    QString ext;

    //some files may not have an extension
    if(index < 0)
    {
        ext = "";
    }
    else
    {
        ext = absolute_path.mid(index + 1);
    }

    //File size
    result = MI.Get(Stream_General, 0, _T("FileSize"), Info_Text, Info_Name).c_str();
    float sizeMB = convertToQString(result).toFloat()/1024.0;	//convert to KiB
    sizeMB /= 1024.0;	//convert to MiB
    int temp = (sizeMB + 0.005)*100;
    sizeMB = static_cast<float>(temp) / 100;


    fileDetails.set(ext, file_name, folder_path, sizeMB);
}

void FileProcessor::videoProcess(MediaInfo &MI, int vid_streams, QList<VideoData> &vec_vid_data)
{
    for(int i = 0; i < vid_streams; i++)
    {
        String result;

        result = MI.Get(Stream_Video, 0, _T("Encryption"), Info_Text, Info_Name).c_str();
        QString encryption = convertToQString(result);

        //If encrypted, no values can be found
        if(encryption == "Encrypted")
        {
            VideoData vd("Encrypted", "Encrypted", "Encrypted", 0.0f, "Encrypted",
                         "Encrypted", "Encrypted", "Encrypted", 0.0f, "Encrypted");
            vec_vid_data.push_back(vd);
            return;
        }

        //Aspect ratio
        result = MI.Get(Stream_Video, i, _T("DisplayAspectRatio/String"), Info_Text, Info_Name).c_str();
        QString aspect = convertToQString(result);

        //Color matrix
        result = MI.Get(Stream_Video, i, _T("ColorSpace"), Info_Text, Info_Name).c_str();
        QString color = convertToQString(result);

        //Frame rate value
        result = MI.Get(Stream_Video, i, _T("FrameRate"), Info_Text, Info_Name).c_str();

        if(result.size() == 0)
        {
            result = MI.Get(Stream_Video, i, _T("FrameRate_Nominal"), Info_Text, Info_Name).c_str();
        }
        float frate = convertToQString(result).toFloat();

        //Frame rate Scan type
        result = MI.Get(Stream_Video, i, _T("ScanType"), Info_Text, Info_Name).c_str();
        QString fram_scan = convertToQString(result);

        //Resolution size
        String width = MI.Get(Stream_Video, i, _T("Width"), Info_Text, Info_Name).c_str();
        String height = MI.Get(Stream_Video, i, _T("Height"), Info_Text, Info_Name).c_str();
        result = width + _T("x") + height;
        QString resSize = convertToQString(result);

        //Resolution standard
        result = MI.Get(Stream_Video, i, _T("Standard"), Info_Text, Info_Name).c_str();
        QString resType = convertToQString(result);

        //Sampling
        result = MI.Get(Stream_Video, i, _T("ChromaSubsampling"), Info_Text, Info_Name).c_str();
        QString sampling = convertToQString(result);

        //Video Bitrate
        result = MI.Get(Stream_Video, i, _T("BitRate"), Info_Text, Info_Name).c_str();

        if(result.size() == 0)	//If no bitrate retreived, find nominal bitrate
        {
            result = MI.Get(Stream_Video, i, _T("BitRate_Nominal"), Info_Text, Info_Name).c_str();
        }
        float vid_brate = convertToQString(result).toFloat()/1000.0f;	//kbps

        //Video Format
        result = MI.Get(Stream_Video, i, _T("Format"), Info_Text, Info_Name).c_str();
        QString vid_format = convertToQString(result);


        //Add stream details to list
        VideoData vid_data (aspect, color, "none", frate, fram_scan,
                            resSize, resType, sampling, vid_brate, vid_format);
        vec_vid_data.push_back(vid_data);
    }
}

void FileProcessor::audioProcess(MediaInfo &MI, int numAudStreams, QList<AudioData> &vec_aud_data)
{
    if(numAudStreams == 0)
    {
        AudioData aud_data(0, "", "", "",  "",  "", "");
        vec_aud_data.push_back(aud_data);
    }
    else
    {
        for(int i = 0; i < numAudStreams; i++)
        {
            String result;

            result = MI.Get(Stream_Audio, 0, _T("Encryption"), Info_Text, Info_Name).c_str();
            QString encryption = convertToQString(result);

            //If encrypted, no values can be found
            if(encryption == "Encrypted")
            {
                AudioData aud_data(0.0f, "Encrypted", "Encrypted", "Encrypted", "Encrypted", "Encrypted", "Encrypted");
                vec_aud_data.push_back(aud_data);
                return;
            }

            //Audio Bitrate
            result = MI.Get(Stream_Audio, i, _T("BitRate"), Info_Text, Info_Name).c_str();
            float bRate = convertToQString(result).toFloat()/1000.0f;

            //Audio Format
            result = MI.Get(Stream_Audio, i, _T("Codec/String"), Info_Text, Info_Name).c_str();
            QString format = convertToQString(result);

            //Channel
            result = MI.Get(Stream_Audio, i, _T("ChannelPositions"), Info_Text, Info_Name).c_str();
            QString channel = convertToQString(result);

            //Content
            result = MI.Get(Stream_Audio, i, _T("Language_More"), Info_Text, Info_Name).c_str();
            QString content = convertToQString(result);

            //Language Code - can be implemented?
            QString lang_code = "";

            //Sampling
            result = MI.Get(Stream_Audio, i, _T("SamplingRate/String"), Info_Text, Info_Name).c_str();
            QString sampling = convertToQString(result);

            AudioData aud_data(bRate, format, channel, content,  "none",  lang_code, sampling);
            vec_aud_data.push_back(aud_data);
        }
    }
}


QString FileProcessor::convertToQString(String &str)
{

    QString str2;

    for(int i = 0; i < str.size(); i++)
    {
        str2.push_back(str[i]);
    }

    if(str2 == "")
    {
        return "";
    }
    else
    {
        return str2;
    }
}


QStringList FileProcessor::get_unprocessed()
{
    return unprocessed;
}
