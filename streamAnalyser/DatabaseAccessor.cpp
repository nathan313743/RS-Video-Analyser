#include "DatabaseAccessor.h"
#include <qmessagebox.h>


DatabaseAccessor::DatabaseAccessor()
{
    //Set this path for the SQLite databse
    db_path = "../db/video_library.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE", "myConnection1");
    db.setDatabaseName(db_path);
    check_connection();
}

DatabaseAccessor::~DatabaseAccessor()
{
}

bool DatabaseAccessor::check_connection()
{
    bool b = db.open();
    db.close();

    return b;
}

void DatabaseAccessor::write_all_data(QList<FileDetails>& vecList, bool *&stopFlag)
{
    stop_flag = stopFlag;
    added_files.clear();
    insertData(vecList);
}

int DatabaseAccessor::get_foreign_key(const QString &name, const QString &path)
{
    db.open();
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("SELECT pk_file_ID FROM File_Properties where file_name = :name AND file_path = :path");
    query->bindValue(":name", name);
    query->bindValue(":path", path);

    if(query->exec() != true)
    {
        qDebug() << "Error Foreign key";
    }
    else
    {
        while(query->next())
        {
            int key = query->value(0).toInt();
            delete query;
            db.close();
            return key;
        }
    }
    delete query;
    db.close();
}

void DatabaseAccessor::insertData(QList<FileDetails>& fileList)
{
    QString strStatus;

    //Loop through every file
    for(int i = 0; i < fileList.size(); i++)
    {
        FileDetails fd = fileList.at(i);
        QString fileName = fd.get_file_name();
        emit updateStatus(strStatus = "Writing: " + fileName);

        write_file(fd);

        int fk = get_foreign_key(fd.get_file_name(), fd.get_file_path());

        write_audio(fk, fd.get_audio_list());
        write_video(fk, fd.get_video_list());

        added_files.push_back(fd.get_file_path() + "/" + fd.get_file_name());

        if(*stop_flag == true)
        {
            return;
        }

    }
}

QStringList DatabaseAccessor::get_added()
{
    return added_files;
}

QStringList DatabaseAccessor::get_previously_selected_folders()
{
    db.open();

    QStringList results;

    QSqlQuery *query = new QSqlQuery(db);
    QString select = "SELECT DISTINCT file_path FROM File_Properties";
    query->exec(select);

    while(query->next())
    {
        results.push_back(query->value(0).toString());
    }
    delete query;
    db.close();
    return results;
}

void DatabaseAccessor::write_audio(int fk, QList<AudioData> &audList)
{
    db.open();

    QSqlQuery *aQuery = new QSqlQuery(db);

    for(int i = 0; i < audList.size(); i++)
    {
        aQuery->prepare( "INSERT INTO Audio("
                         " fk_file_ID,"
                         " audio_format,"
                         " audio_bitrate_Kb,"
                         " channel,"
                         " content,"
                         " encryption,"
                         " language_code,"
                         " sampling"
                         ")"
                         " VALUES("
                         " :fk_file_ID,"
                         " :audio_format,"
                         " :audio_bitrate_Kb,"
                         " :channel,"
                         " :content,"
                         " :encryption,"
                         " :language_code,"
                         " :sampling)");

        aQuery->bindValue( ":fk_file_ID", fk);
        aQuery->bindValue( ":audio_format", audList[i].get_aud_format());
        aQuery->bindValue( ":audio_bitrate_Kb", audList[i].get_aud_bitrate());
        aQuery->bindValue( ":channel", audList[i].get_channel());
        aQuery->bindValue( ":content", audList[i].get_content());
        aQuery->bindValue( ":encryption", audList[i].get_encryption());
        aQuery->bindValue( ":language_code", audList[i].get_lang_code());
        aQuery->bindValue( ":sampling", audList[i].get_sampling());

        if(aQuery->exec() != true)
        {
            qDebug() << "Error Audio: " << aQuery->lastError();
        }
    }
    delete aQuery;
    db.close();
}

void DatabaseAccessor::write_file(FileDetails &fDetails)
{
    db.open();
    QSqlQuery *fQuery = new QSqlQuery(db);

    fQuery->prepare( "INSERT INTO File_Properties"
                     " (date_added,"
                     " extension,"
                     " file_name,"
                     " file_path,"
                     " size_MB)"
                     " VALUES("
                     " DATETIME(),"
                     " :extension,"
                     " :file_name,"
                     " :file_path,"
                     " :size_MB"
                     " )");

    fQuery->bindValue( ":extension", fDetails.get_extension());
    fQuery->bindValue( ":file_name", fDetails.get_file_name());
    fQuery->bindValue( ":file_path", fDetails.get_file_path());
    fQuery->bindValue( ":size_MB", QString::number(fDetails.get_sizeMB() , 'f', 2));

    if(fQuery->exec() != true)
    {
        qDebug()<< "Error File: " << fQuery->lastError() << " -> " << fDetails.get_file_name();
    }

    delete fQuery;
    db.close();
}

void DatabaseAccessor::write_video(int fk, QList<VideoData> &vd)
{
    db.open();

    QSqlQuery *vQuery = new QSqlQuery(db);

    for(int j = 0; j < vd.size(); j++)
    {
        vQuery->prepare(
                    "INSERT INTO Video"
                    " (fk_file_ID,"
                    " aspect_ratio,"
                    " color_matrix,"
                    " content_dimension,"
                    " content_motion,"
                    " content_style,"
                    " encryption,"
                    " frame_rate_scan,"
                    " frame_rate_value,"
                    " res_size,"
                    " res_standard,"
                    " sampling,"
                    " video_bitrate_Kb,"
                    " video_format)"
                    "VALUES("
                    " :fk_file_ID"
                    ", :aspect_ratio"
                    ", :color_matrix"
                    ", :content_dimension"
                    ", :content_motion"
                    ", :content_style"
                    ", :encryption"
                    ", :frame_rate_scan"
                    ", :frame_rate_value"
                    ", :res_size"
                    ", :res_standard"
                    ", :sampling"
                    ", :video_bitrate_Kb"
                    ", :video_format)");

        vQuery->bindValue( ":fk_file_ID", fk);
        vQuery->bindValue( ":aspect_ratio", vd[j].get_aspect_ratio());
        vQuery->bindValue( ":color_matrix", vd[j].get_color());
        vQuery->bindValue( ":content_dimension", "");
        vQuery->bindValue( ":content_motion", "");
        vQuery->bindValue( ":content_style", "");
        vQuery->bindValue( ":encryption", vd[j].get_encryption());
        vQuery->bindValue( ":frame_rate_scan", vd[j].get_frame_scan());
        vQuery->bindValue( ":frame_rate_value", vd[j].get_frame_rate());
        vQuery->bindValue( ":res_size", vd[j].get_res_size());
        vQuery->bindValue( ":res_standard", vd[j].get_res_standard());
        vQuery->bindValue( ":sampling", vd[j].get_sampling());
        vQuery->bindValue( ":video_bitrate_Kb", vd[j].get_vid_bitrate());
        vQuery->bindValue( ":video_format", vd[j].get_vid_format());

        if(vQuery->exec() != true)
        {
            qDebug()<< "Error Video: " << vQuery->lastError();
        }
    }
    delete vQuery;
    db.close();
}

QStringList DatabaseAccessor::get_existing_list()
{
    db.open();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT file_path, file_name FROM File_Properties");
    QStringList name_list;

    if(query->exec() != true)
    {
        qDebug() << "Error: get_existing_list";
    }
    else
    {
        QString path;
        QString file_name;
        while(query->next())
        {
            path = query->value(0).toString();
            file_name = query->value(1).toString();
            name_list.push_back(path + "/" + file_name);
        }
    }

    delete query;
    db.close();
    return name_list;

}

void DatabaseAccessor::remove_list(QStringList& list)
{
    db.open();
    QSqlQuery *query = new QSqlQuery(db);

    const int arrsize = list.size();
    int *indexes = new int[arrsize];

    //Create where clause.  First file in the list
    QString full_path = list.at(0);
    int str_index = full_path.lastIndexOf("/");
    QString path = full_path.mid(0, str_index);
    QString name = full_path.mid(str_index + 1);
    QString clause;
    clause = " file_name = \'" + name  + "' AND file_path = \'" + path + "\'";

    //the rest of the files in the list
    if(arrsize > 1)
    {
        for(int i = 1; i < arrsize; i++)
        {
            full_path = list.at(i);
            str_index = full_path.lastIndexOf("/");
            path = full_path.mid(0, str_index);
            name = full_path.mid(str_index + 1);
            clause += " OR file_name = \'" + name  + "' AND file_path = \'" + path + "\'";
        }
    }

    query->prepare("SELECT pk_file_ID FROM File_Properties WHERE" + clause);

    if(!query->exec())
    {
        qDebug()<< "Error remove_list: " << query->lastError();
    }

    //key results from query
    int size = 0;
    while(query->next())
    {
        indexes[size] = query->value(0).toInt();
        size++;
    }

    //delete records that have the matching foreign key
    for(int i = 0; i < size; i++)
    {
        qDebug() << QString::number(indexes[i]);
        query->exec("DELETE FROM File_Properties WHERE pk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Audio WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Video WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Transport_Stream WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Test_Case WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Signal_Root WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM TS_Data WHERE fk_file_ID = " + QString::number(indexes[i]));
        query->exec("DELETE FROM Interface fk_file_ID = " + QString::number(indexes[i]));
    }

    if(!query->exec())
    {
        qDebug()<< "Error delete: " << query->lastError();
    }

    delete[] indexes;
    delete query;
    db.close();

}

void DatabaseAccessor::reset_db()
{
    db.open();
    QSqlQuery *query = new QSqlQuery(db);

    query->exec("DELETE FROM Audio");
    query->exec("DELETE FROM File_Properties");
    query->exec("DELETE FROM Video");

    delete query;
    db.close();


}
