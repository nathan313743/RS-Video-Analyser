/**
 ** Holds data for the SQL queries.
 ** Field names for each table.
 */
#ifndef QUERYDATA_H_
#define QUERYDATA_H_
#include <QStringList>
#include <QVector>

class QueryData
{
public:
	QueryData();
	~QueryData();

	/*******************************************
	 ** Returns tables in the database.
	 * @return - Returns tables in the database.
	 ********************************************/
	QList<QStringList> get_tables();
	
	/**************************************************
	 ** Returns field names and SQL field names.
	 * @param Returns field names and SQL field names.
	 **************************************************/
	QList<QStringList> get_File_Properties_fields();
	QList<QStringList> get_Video_fields();
	QList<QStringList> get_Audio_fields();
	QList<QStringList> get_Signal_Root_fields();
	QList<QStringList> get_Transport_Stream_fields();
	QList<QStringList> get_TS_Data_fields();
	QList<QStringList> get_Test_Case_fields();

private:
	QList<QStringList> tables;
	QList<QStringList> file_fields;
	QList<QStringList> video_fields;
	QList<QStringList> audio_fields;
	QList<QStringList> signal_fields;
	QList<QStringList> trans_fields;
	QList<QStringList> ts_data_fields;
	QList<QStringList> test_case_fields;

	/*********************************
	 ** Assigns the data to the lists.
	 *********************************/
	void setup_tables();
	void setup_File_Properties_fields();
	void setup_Video_fields();
	void setup_Audio_fields();
	void setup_Signal_Root_fields();
	void setup_Transport_Stream_fields();
	void setup_TS_Data_fields();
	void setup_Test_Case_fields();

};



#endif

