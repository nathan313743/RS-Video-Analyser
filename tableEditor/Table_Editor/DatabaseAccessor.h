#ifndef DATABASEACCESSOR_H_
#define DATABASEACCESSOR_H_
#include <qsqldatabase.h>
#include <qdebug.h>
#include <qsqlquerymodel.h>

class DatabaseAccessor
{
public:
	DatabaseAccessor();
	~DatabaseAccessor();

	/****************************************************************************
	 ** Exexutes SQL query.  Results are added to QStringList.
	 * @param QString& - SQL query.
	 * @param QStringList& - Query results are saved to the list. Passed list 
	 *     									varies in size according to what fucntion called it.
	 ****************************************************************************/
	void executeQuery(QString&, QStringList&);

	/*********************************
	 ** Updates the database.
	 * @param QString& - Update query.
	 * @return - True if successful.
	 *********************************/
	bool executeUpdate(QString &);

	/******************************************
	 ** Deletes file from the database.
	 * @param const int - File ID.
	 * @return - True if delete was successful.
	 ******************************************/
	bool deleteFile(const int);

	/************************************************
	 ** Updates query model.
	 * @param QSqlQueryModel *& - Model to update.
	 * @param QString - Query to update with.
	 *************************************************/
	void update_model(QSqlQueryModel *&, QString);

private:
	QSqlDatabase db;
};

#endif