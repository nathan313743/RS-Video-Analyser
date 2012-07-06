#ifndef DatabaseAccessor_H_
#define DatabaseAccessor_H_
#include <QObject>
#include <QList>
#include <QtSql>
#include <QSqlQuery>

#include "FileDetails.h"
#include "AudioData.h"
#include "VideoData.h"


class DatabaseAccessor : public QObject
{
    Q_OBJECT
public:
    DatabaseAccessor();
    ~DatabaseAccessor();

    bool check_connection();

    /**************************************************************
  ** Returns a list of the file paths that have been succesfully
  ** added to the database.
  * @return - List of file paths in the database.
  ***************************************************************/
    QStringList get_added();

    /*******************************************************
    ** Returns a list of the file paths that already exist
    ** in the database.
    **
    @return - List of file paths in the database.
    *******************************************************/
    QStringList get_existing_list();

    /*****************************************************
    ** Removes entries from the database that are
    ** not in the new file list.
    ** @param QStringList& - List of file names and paths
    **			to remove.
    *******************************************************/
    void remove_list(QStringList&);

    void reset_db();

    /*******************************************************************************
    ** Calls insertData() to start writing process.
    ** @param QList<FileDetails>& - Collection of Video file details.
    ** @param bool* - Stop flag used to stop processing if requested by the user.
    ******************************************************************************/
    void write_all_data(QList<FileDetails>&, bool *&);

    QStringList get_previously_selected_folders();

signals:
    void updateStatus(QString);

private:
    QSqlDatabase db;
    bool *stop_flag;	//Stop flag.
    QString db_path;
    QStringList added_files;

    /*************************************************************
    ** Iterates through the list of files and calls the writing
    ** methods.
    ** @param QList<FileDetails>& - List of files details.
    ************************************************************/
    void insertData(QList<FileDetails>&);

    /******************************************************************
    ** Retrieves the foreign key of the newly written File_Properties
    ** record.
    ** @param QString& - File name.
    ** @parma QString& - File path.
    *******************************************************************/
    int get_foreign_key(const QString &, const QString &);

    /******************************************
    ** Writes audio data to database.
    ** @param int - Foreign key.
    ** @param QList<AudioData>& - AudioData.
    *******************************************/
    void write_audio(int, QList<AudioData> &);

    /************************************
    ** Writes file data to database.
    ** @parma FileDetails& - File data.
    ************************************/
    void write_file(FileDetails&);


    /******************************************
    ** Writes video data to database.
    ** @param int - foreign key.
    ** @param QList<VideoData>& Video data.
    *******************************************/
    void write_video(int, QList<VideoData> &);

};
#endif
