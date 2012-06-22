/*********************************************************************
 ** Used to separate the GUI and the main working code.
 ** Provides access to the main window and tab to other code/database
 *********************************************************************/
#ifndef CODEINTERFACE_H_
#define CODEINTERFACE_H_

#include <QSqlQueryModel>
#include <QString>
#include "VideoCode.h"
#include "AudioCode.h"
#include "DatabaseAccessor.h"
#include "QueryData.h"

class TreeModel;

class CodeInterface
{
public:
    CodeInterface();
    ~CodeInterface();

    /******************************************
	 ** Used for executing generica SQL query.
	 * @param QString - SQL query.
	 * @return - SQL query result.
	 *******************************************/
    QString execute_query(QString);

    /****************************************************
	 ** Gets list of distict combo values from DB.
	 * @param QString - table name.
	 * @param QString - field name.
	 * @return - List of of values to populate combobox.
	 *****************************************************/
    QStringList get_combo_vals(QString, QString);

    /******************************************
	 ** Used for executing generica SQL query.
	 * @param QString - SQL query.
	 * @return - SQL query result list.
	 ******************************************/
    QStringList get_list_query(QString&);

    /***********************************************************
	 ** Gets file names that fit the current selection criteria.
	 * @return List of file names and their values.
	 ***********************************************************/
    QList<QStringList> get_file_names();
    QList<QList<QStringList> > get_Audio_vals(int fileID);
    QList<QStringList> get_File_Properties_vals(int);
    QList<QStringList> get_Signal_Root_vals(int);
    QList<QStringList> get_Test_Case_vals(int);
    QList<QStringList> get_Transport_Stream_vals(int);
    QList<QStringList> get_TS_Data_vals(int);
    QList<QList<QStringList> > get_Video_vals(int);

    /**
    * Resets all where SQL WHERE clauses in the Code classes.
    */
    void reset();

    /*****************************************
	 ** Update the table's SQL WHERE clauses.
	 * @param QString - Table name.
	 * @param QString - Field name.
	 * @param QString - Value.
	 ******************************************/
    void updateTable(QString, QString, QString);


private:

    VideoCode vid_code;
    AudioCode aud_code;


    DatabaseAccessor db_access;
    QueryData query_data;
    QList<QStringList> current_file_names;      // File names returned to the a query.
};

#endif
