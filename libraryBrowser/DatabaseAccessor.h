#ifndef DATABASE_ACCESSOR_H_
#define DATABASE_ACCESSOR_H_
#include <QString>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "QueryData.h"

class TreeModel;

/**
  * Class provides a single point of communication to the database.
  */
class DatabaseAccessor
{
public:
    DatabaseAccessor(void);
    ~DatabaseAccessor(void);

    /***************************************************************
     ** Gets file names from database.  If there is a WHERE clause,
     ** fetches matching files.
     * @param QString& - SQL query.
   * @return - File id and name (pair).
     ****************************************************************/
    QList<QStringList> get_file_names(QString &);

    /*************************************************************
   * Gets Audio attribute's name and value for each Audio stream.  Each Audio stream represented my the outer QList,
   * this QLists holds another QList which holds the attribute name and pair in a QStringList.
   * These values are displayed in the TreeView
   * @param int - Audio table primary key.
   * @return - Audio stream data.  Stream attribute's name and value.
     *************************************************************/
    QList<QList<QStringList> > get_Audio_vals(int);

    /*************************************************************
   * Gets File Properties attribute's name and value.
   * These values are displayed in the TreeView
   * @param int - File Properties table primary key.
   * @return - File Properties attribute's name and value.
   *************************************************************/
    QList<QStringList> get_File_Properties_vals(int);

    /*************************************************************
   * Gets Transport Stream attribute's name and value.
   * These values are displayed in the TreeView
   * @param int - Transport Stream table primary key.
   * @return - Transport Stream attribute's name and value.
   *************************************************************/
    QList<QStringList> get_Transport_Stream_vals(int);

    /*************************************************************
   * Gets Transport Stream Data attribute's name and value.
   * These values are displayed in the TreeView
   * @param int - Transport Stream Data table primary key.
   * @return - Transport Stream Data attribute's name and value.
   *************************************************************/
    QList<QStringList> get_TS_Data_vals(int);

    /*************************************************************
   * Gets Signal Root attribute's name and value.
   * These values are displayed in the TreeView
   * @param int - Signal Root table primary key.
   * @return - Signal Root attribute's name and value.
   *************************************************************/
    QList<QStringList> get_Signal_Root_vals(int);

    /*************************************************************
   * Gets Test Case attribute's name and value.
   * These values are displayed in the TreeView
   * @param int - Test Case table primary key.
   * @return - Test Case attribute's name and value.
   *************************************************************/
    QList<QStringList> get_Test_Case_vals(int);

    /*************************************************************
   * Gets Video attribute's name and value for each Video stream.  Each Video stream represented my the outer QList,
   * this QLists holds another QList which holds the attribute name and pair in a QStringList.
   * These values are displayed in the TreeView
   * @param int - Video table primary key.
   * @return - Video stream data. Stream data attribute's name and value.
   *************************************************************/
    QList<QList<QStringList> > get_Video_vals(int);

    /*************************************************************
     ** Generic method for executing a query and retriving a list.
     * @param QString& - query.
     * @return - List of results.
     *************************************************************/
    QStringList get_list_query(QString &);

    /****************************************************
     ** Gets list of distict combo values from DB.
     * @param QString - table name.
     * @param QString - field name.
     * @param QList<QStringList> - list of file ids.
     * @return - List of of values to populate combobox.
     *****************************************************/
    QStringList get_combo_vals(QString &, QString &, QList<QStringList> &);


    /**
    * Generic function for executing a string and
    * retrieving a String result.
    */
    QString execute_query(QString);

private:
    QSqlDatabase db;
    QueryData query_data;   // Stores string data that are use for queries.

};

#endif
