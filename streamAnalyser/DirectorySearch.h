#ifndef DIRECTORYSEARCH_H_
#define DIRECTORYSEARCH_H_
#include <QString>
#include <QStringList>
#include <QDir>
#include "DatabaseAccessor.h"

/***********************************************
 * Retrieves a file list from a given directory.
 ***********************************************/
class DirectorySearch : public QObject
{
    Q_OBJECT

public:
    DirectorySearch(bool *&);

    /************************************************
     * Retrieves a file list from a given directory.
     *
     * @param QString - Directory path.
     * @return - List of files.  Absolute file paths
     ************************************************/
    QStringList get_file_names(QStringList&, DatabaseAccessor *dbAccess);
    QStringList get_skipped_list();

signals:
    /****************************************
     * Informs GUI what file is being added.
     ****************************************/
    void updateStatus(QString);

private:
    bool *stop_flag;
    QStringList ignore_paths;
    QStringList skipped_list;
    /*********************************************************
     * Compares new file list with existing DB file list.
     * If database list already contains file in new list,
     * this file is not added. If database list is not in the
     * new list it is removed from the database.
     *
     * @param QStringList* - List of new file paths.
     *********************************************************/
    void compare_existing(QStringList& , DatabaseAccessor *dbAccess);


    /************************************************************
     * Recursively goes through directories.  Adds
     * file paths to list.
     *
     * @param QString - Directory path.
     * @param QStringList - Collection of files in the directory.
     *************************************************************/
    void traverse(QString path, QStringList& file_names);
};

#endif
