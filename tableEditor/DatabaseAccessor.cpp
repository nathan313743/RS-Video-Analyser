#include "DatabaseAccessor.h"
#include "qsqlquery.h"
#include "qvector.h"
#include <QtSql>

DatabaseAccessor::DatabaseAccessor()
{
	db = QSqlDatabase::addDatabase("QSQLITE", "myConnection");
    db.setDatabaseName("../db/video_library.sqlite");
}

DatabaseAccessor::~DatabaseAccessor()
{
}

void DatabaseAccessor::executeQuery(QString &strQuery, QStringList& valueList)
{

	if(!db.open())
	{
		qDebug() << "Database could not be opened";
	}

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(!query->exec())
	{
		qDebug() << "Error query: " << query->lastError();
	}


	//Tab values
	if(valueList.size() > 0)
	{
		query->next();

		for(int i = 0; i < valueList.size(); i++)
		{
			valueList.replace(i, query->value(i).toString());
		}
	}
	else	//Stream count, and autocomplete values
	{
		while(query->next())
		{
			valueList.push_back(query->value(0).toString());
		}
	}

	delete query;
	db.close();
}

bool DatabaseAccessor::executeUpdate(QString &strQuery)
{
	if(!db.open())
	{
		qDebug() << "Database could not be opened: " << db.lastError();
		db.close();
		return false;
	}

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(!query->exec())
	{
		qDebug() << "Error Update: " << query->lastError();
		delete query;
		db.close();
		return false;
	}

	delete query;
	db.close();
	return true;
}

bool DatabaseAccessor::deleteFile(const int file_ID)
{
	db.open();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("DELETE FROM File_Properties WHERE pk_file_ID = " + QString::number(file_ID));
	
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}

	query->prepare("DELETE FROM Video WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}


	query->prepare("DELETE FROM Audio WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}

	query->prepare("DELETE FROM Transport_Stream WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}

	query->prepare("DELETE FROM TS_Data WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}

	query->prepare("DELETE FROM Test_Case WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			delete query;
		db.close();
		return false;
	}

	query->prepare("DELETE FROM Signal_Root WHERE fk_file_ID = " + QString::number(file_ID));
	if(!query->exec())
	{
		qDebug() << query->lastError();
			
		delete query;
		db.close();
		return false;
	}
		
	delete query;
	db.close();
	return true;
}

void DatabaseAccessor::update_model(QSqlQueryModel *&model, QString query)
{
	db.open();
	model->setQuery(query, db);
	db.close();
}
