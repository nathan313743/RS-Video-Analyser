/******************************************
 ** Extracts the video file's stream data.
 ** Uses MediaInfo to achieve this.
 *******************************************/
#ifndef FILEPROCESSOR_H_
#define FILEPROCESSOR_H_

#include "FileDetails.h"
#include "AudioData.h"
#include "TransportDetails.h"
#include "VideoData.h"
#include "StreamAnalyser.h"

#include <qobject.h>

#ifdef MEDIAINFO_LIBRARY
#include "MediaInfo/MediaInfo.h" //Staticly-loaded library (.lib or .a or .so)
#define MediaInfoNameSpace MediaInfoLib;
#else //MEDIAINFO_LIBRARY
#include "MediaInfoDLL.h" //Dynamicly-loaded library (.dll or .so)
#define MediaInfoNameSpace MediaInfoDLL;
#endif //MEDIAINFO_LIBRARY
using namespace MediaInfoNameSpace;
using namespace std;

class FileProcessor : public QObject
{
	Q_OBJECT

public:
    QStringList get_unprocessed();

	/**********************************************************************
	 ** Loops through files and processes streams.
	 * @param const QStringList& - List of file paths.
	 * @param bool *& - Stop flag.  If cancelled is click, flag is raised.
	 * @return - A list of streams values extracted, one entry per file.
	 **********************************************************************/
	QList<FileDetails> process(const QStringList&, bool*&);

signals:
	/************************************************
	 ** Used to communicate status messages with the
	 ** main GUI.
	 * @param QString - Message content.
	 ************************************************/
	void updateStatus(QString);

private:

  QStringList unprocessed;    //Files that cannot be opened and/or porcessed.



	/*****************************************
	 ** Converts MediaInfo string to QString.
	 * @param String& - MediaInfo String.
	 *****************************************/
	QString convertToQString(String &);

	/*****************************************
	 ** Converts QString to MediaInfo String.
	 * @param QString - QString to convert.
	 ******************************************/
	String convertToMediaString(QString);

	/**********************************************
	 ** Extracts file details from video file.
	 * @param MediaInfo& - MediaInfo instance.
	 * @param FileDetails& - Holds the file data.
	 *********************************************/
	void fileProcess(MediaInfo &, FileDetails &);

	/*****************************************************
	 ** Extracts video stream data from video file.
	 * @param MediaInfo& - MediaInfo instance.
	 * @param int - Number of video streams in the file.
	 * @param QList<VideoData> & - Holds the video stream data.
	 ****************************************************/
	void videoProcess(MediaInfo &, int, QList<VideoData> &);
	
	/******************************************************
	 ** Extracts the audio stream data.
	 * @param MediaInfo& - MediaInfo instance.
	 * @param int - Number of audio streams in the file.
	 * @param List<AudioData> & - Holds audio stream data.
	 ******************************************************/
	void audioProcess(MediaInfo &, int, QList<AudioData> &);
	
	/************************************************************
	 ** Extracts the transport stream data.
	 * @param MediaInfo& - MediaInfo instance.
	 * @param TransportDetails & - Holds transport stream data.
	 ***********************************************************/
	void transportProcess(MediaInfo &, TransportDetails &);
};

#endif
