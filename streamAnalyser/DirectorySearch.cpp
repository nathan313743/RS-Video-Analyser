#include "DirectorySearch.h"

DirectorySearch::DirectorySearch(bool *&stopFlag)
{
    stop_flag = stopFlag;
}

void DirectorySearch::compare_existing(QStringList& new_list, DatabaseAccessor *dbAccess)
{
    QStringList old_list = dbAccess->get_existing_list();
    QStringList remove_list;

    for(int i = 0; i < old_list.size(); i++)
    {
        //if a file present in the db is in the new_list, ignore/do not add
        if(new_list.contains(old_list.at(i)) == true)
        {
            new_list.removeOne(old_list.at(i));		//Remove from the new list (not added again)
            skipped_list.push_back(old_list.at(i));
        }
        else
        {
            remove_list.push_back(old_list.at(i));	//old files to be removed from the database
        }
    }

    if(remove_list.size() > 0)
    {
        dbAccess->remove_list(remove_list);
    }
}

QStringList DirectorySearch::get_skipped_list()
{
    return skipped_list;
}

QStringList DirectorySearch::get_file_names(QStringList &selectedPaths, DatabaseAccessor *dbAccess)
{
    QStringList file_names;                             // A list to store all file names.


    for(int i = 0; i < selectedPaths.size(); i++)       // For each directory get files and sub directories.
    {
        if(*stop_flag == true)
        {
            qDebug();
            return file_names;                                 // Stop called by user.  Return nothing.
        }

        traverse(selectedPaths.at(i), file_names);
    }

    compare_existing(file_names, dbAccess);             // If files are already in database, remove them.
    return file_names;
}

void DirectorySearch::traverse(QString path, QStringList& file_names)
{
    if(*stop_flag == true)
    {
        return;
    }

    QDir dir(path);
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files| QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0; i < list.size(); i++)
    {
        if(*stop_flag == true)
        {
            return;
        }

        QFileInfo temp = list.at(i);

        if(temp.isDir())
        {
            traverse(temp.absoluteFilePath(), file_names);
        }
        else
        {
            file_names.push_back(temp.absoluteFilePath());
            emit updateStatus("Reading: " + temp.absoluteFilePath());
        }
    }
}
