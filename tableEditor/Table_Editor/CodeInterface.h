/**
 ** Provides and interface on the GUI and the rest of the code;
 ** keeping the two parts separate.
 */

#ifndef CODEINTERFACE_H_
#define CODEINTERFACE_H_
#include <qstringlist.h>
#include "DatabaseAccessor.h"
#include <qsqlquerymodel.h>

class CodeInterface
{
public:
	CodeInterface();
	~CodeInterface();

	/********************************************************
	 ** Sets the chosen file id to be used by all database
	 ** writing actions within the class.
	 * @param const int - Chosen file ID.
   *******************************************************/
	void set_file_ID(const int);

	/*****************************************************
	 ** Retrieves names and values of fields in the table.
	 *****************************************************/
	QStringList populate_file_boxes();
	
	/****************************
	 * @param int - Stream number.
	 *****************************/
	QStringList populate_aud_boxes(int);
	QStringList populate_sig_boxes();
	QStringList populate_trans_boxes();
	QStringList populate_vid_boxes(int);
	
	/************************************************************
	 ** Gets the number of aud/vid streams for the selected file.
	 ************************************************************/
	QStringList get_aud_stream_nums();
	QStringList get_vid_stream_nums();
	
	/*******************************************
	 ** Deletes selected file from the database.
	 * @param int - File ID.
	 *******************************************/
	bool delete_file(int);

	/**************************************************************
	 ** Creates SQL query to write values to the database.
	 * @param QStringList& - List of values from text/comboboxes.
	 * @param int - Stream number.
	 * @return - True if write operation was successful.
	 *************************************************************/
	bool write_aud_values(QStringList &, int);
	bool write_sig_values(QStringList&);
	bool write_trans_values(QStringList&);
	bool write_vid_values(QStringList &, int);
	
	/*************************************************************************
	 ** Get all distinct values for the autocomplete boxes.
	 * @return - List of values for a field, altogether wrapped in a QVector.
	 *************************************************************************/
	QVector<QStringList> get_aud_autocomplete();
	QVector<QStringList> get_sig_autocomplete();
	QVector<QStringList> get_trans_autocomplete();
	QVector<QStringList> get_vid_autocomplete();

	/*************************************
	 ** Add test case to database.
	 * @param QString& - Test case value.
	 *************************************/
	void add_case(QString &);
	void add_interface(QString &);

	/*****************************
	 ** Deletes test case.
	 * @param int - test case ID.
	 *****************************/
	void delete_case(int);
	void delete_interface(int);

	void add_TS_data(QString &);
	void delete_TS_data(int);

	/******************************************************
	 ** Updates the QSqlQueryModel.  Used by Test Case and
	 ** TS Data.
	 * @param QSqlQueryModel *& - Model to be updated.
	 * @param QString - Query for updating.
	 ******************************************************/
	void update_model(QSqlQueryModel *&, QString);

	/****************************
	 ** Used for the main table.
	 *****************************/
	void update_model_main(QSqlQueryModel *&, QString);

private:
	DatabaseAccessor db_access;	//access to the database
	int file_ID;									//the selected file's database ID
};
#endif
