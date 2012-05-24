#include "DatabaseAccessor.h"


DatabaseAccessor::DatabaseAccessor()
{

	db = QSqlDatabase::addDatabase("QSQLITE", "myConnection");
  db.setDatabaseName("../../database/video_library.sqlite");
}

DatabaseAccessor::~DatabaseAccessor()
{
}

QStringList DatabaseAccessor::get_list_query(QString &strQuery)
{

	if(!db.open())
	{
		qDebug() << "Database could not be opened: ";
	}

	QStringList fileNames;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			fileNames.push_back(query->value(0).toString());
		}
	}
	
	delete query;
	db.close();

	return fileNames;
}

QList<QStringList> DatabaseAccessor::get_file_names(QString &strQuery)
{
	QList<QStringList> fileValues;

  // All file names
	if(strQuery == "")
	{
		strQuery = "SELECT pk_file_ID, file_name FROM File_Properties";
	}

	if(!db.open())
	{
		qDebug() << "Database could not be opened: ";
	}

  QStringList id_name;                                  // Holds both File_ID and file name

	QSqlQuery *query = new QSqlQuery(strQuery, db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
      id_name.push_back(query->value(0).toString());    // Get ID.
      id_name.push_back(query->value(1).toString());    // Get name.
      fileValues.push_back(id_name);                    //Store in variable.
			id_name.clear();
		}
	}
	else
	{
		//error
	}
		
	delete query;
	db.close();
	return fileValues;
}

QStringList DatabaseAccessor::get_combo_vals(QString &table, QString &field,  QList<QStringList> &fileIDs)
{
	db.open();
	QString str = "";

	if(fileIDs.size() > 0)
	{
		str = " WHERE fk_file_ID = " + fileIDs.at(0).at(0);

		for(int i = 1; i < fileIDs.size(); i++)
		{
			str += " OR fk_file_ID = " + fileIDs.at(i).at(0);
		}

	}


	QStringList values;

	QString strQuery = "SELECT DISTINCT " + field + " FROM " + table + str;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			values.push_back(query->value(0).toString());
		}
	}

	delete query;
	db.close();
	return values;
}

QList<QStringList> DatabaseAccessor::get_File_Properties_vals(int fileID)
{
	if(!db.open())
	{
		qDebug() << "Database could not be opened: ";
	}

	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_File_Properties_fields();

	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}

	strQuery += " FROM File_Properties WHERE pk_file_ID = " + QString::number(fileID);


	QList<QStringList> resultValues;
	QStringList values;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			//date
			values.push_back(fields.at(0).at(1));					//field name
			values.push_back(query->value(0).toString());	//field value
			resultValues.push_back(values);											
			values.clear();

			//extension
			values.push_back(fields.at(1).at(1));					//field name
			values.push_back(query->value(1).toString());	//field value
			resultValues.push_back(values);											
			values.clear();

			//file name
			values.push_back(fields.at(2).at(1));					//field name
			values.push_back(query->value(2).toString());	//field value
			resultValues.push_back(values);											
			values.clear();

			//file path
			values.push_back(fields.at(3).at(1));					//field name
			values.push_back(query->value(3).toString());	//field value
			resultValues.push_back(values);											
			values.clear();

			//size
			values.push_back(fields.at(4).at(1));					//field name
			values.push_back(query->value(4).toString());	//field value
			resultValues.push_back(values);											
			values.clear();
		}
	}
	delete query;
	db.close();
	return resultValues;
}

QList<QList<QStringList> > DatabaseAccessor::get_Video_vals(int fileID)
{
	db.open();

	QStringList streamsIDs;

	//get video ids
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("SELECT pk_video_ID FROM Video WHERE fk_file_ID = " + QString::number(fileID));

	if(query->exec() == true)
	{
		while(query->next())
		{
			streamsIDs.push_back(query->value(0).toString());
		}
	}

  QList<QList<QStringList> > vidFileList;

	//build query
	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_Video_fields();
	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}


	//get stream data
	for(int i = 0; i < streamsIDs.size(); i++)
	{
		QStringList valuePairs;
		QList<QStringList> stream;

		query->prepare(strQuery + " FROM Video WHERE pk_video_ID = " + streamsIDs.at(i));

		if(query->exec() == true)
		{

			while(query->next())
			{
				int index = 0;
				//aspect
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);											

				//color
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//dimension
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//motion
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	


				//style
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	


				//encryption
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//scan
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//frame rate
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//res size
				index++;
				valuePairs.clear();
        valuePairs.push_back(fields.at(index).at(1));					//field name
        valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//res standard
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//sampling
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//video bitrate
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

				//video format
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				stream.push_back(valuePairs);	

			}
		}
		vidFileList.push_back(stream);
	}

	delete query;
	db.close();
	return vidFileList ;
}

QList<QList<QStringList> > DatabaseAccessor::get_Audio_vals(int fileID)
{
	db.open();

  QStringList streamsIDs;   // Stores ID(s) from Audio table.

  // Get audio ID(s).
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("SELECT pk_audio_ID FROM Audio WHERE fk_file_ID = " + QString::number(fileID));

	if(query->exec() == true)
	{
		while(query->next())
		{
			streamsIDs.push_back(query->value(0).toString());
		}
	}

  // Build query.
	QString strQuery = "SELECT ";
  QList<QStringList> fields = query_data.get_Audio_fields();    // Gets all audio fields.

  for(int i = 0; i < fields.size(); i++)
	{	
    strQuery += fields.at(i).at(0);
	}

  QList<QList<QStringList> > streamList;  // Holds all the stream data.

  // Get stream data
	for(int i = 0; i < streamsIDs.size(); i++)
	{
    QStringList valuePairs;               // Attribute name and value.
    QList<QStringList> singleStream;      // Holds all data from a single Audio stream.

		query->prepare(strQuery + " FROM Audio WHERE pk_audio_ID = " + streamsIDs.at(i));

		if(query->exec() == true)
		{

			while(query->next())
			{
				int index = 0;

				//audio format
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);

				//audio bitrate
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	

				//channel
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	

				//content
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	

				//encryption
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	

				//language code
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	

				//sampling
				index++;
				valuePairs.clear();
				valuePairs.push_back(fields.at(index).at(1));					//field name
				valuePairs.push_back(query->value(index).toString());	//field value
				singleStream.push_back(valuePairs);	
			}
		}

		streamList.push_back(singleStream);
	}

	delete query;
	db.close();
	return streamList ;
}

QList<QStringList> DatabaseAccessor::get_Signal_Root_vals(int fileID)
{
	db.open();

	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_Signal_Root_fields();

	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}

	strQuery += " FROM Signal_Root WHERE fk_file_ID = " + QString::number(fileID);


	QList<QStringList> resultValues;
	QStringList pairedVals;
	

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			int index = 0;
			//region
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//producer
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//source
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

		}
	}
	
	delete query;
	db.close();
	return resultValues;
}

QList<QStringList> DatabaseAccessor::get_Test_Case_vals(int fileID)
{
	db.open();
	
	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_Test_Case_fields();

	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}

	strQuery += " FROM Test_Case WHERE fk_file_ID = " + QString::number(fileID);


	QList<QStringList> resultValues;
	QStringList pairedVals;


	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			//test case
			pairedVals.push_back(fields.at(0).at(1));					//field name
			pairedVals.push_back(query->value(0).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();
		}
	}
	
	delete query;
	db.close();
	return resultValues;
}

QList<QStringList> DatabaseAccessor::get_Transport_Stream_vals(int fileID)
{
	db.open();

	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_Transport_Stream_fields();
	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}

	strQuery += " FROM Transport_Stream WHERE fk_file_ID = " + QString::number(fileID);


	QList<QStringList> resultValues;
	QStringList pairedVals;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			int index = 0;
			//audio only
			pairedVals.push_back(fields.at(index).at(1));					//field name
			if(query->value(index).toString() == "1")
			{
				pairedVals.push_back("True");
			}
			else
			{
				pairedVals.push_back("False");
			}
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//aud services
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//vid services
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//loop length
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//standard
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//bit rate
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

			//packet size
			index++;
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

		}
	}
	
	delete query;
	db.close();
	return resultValues;
}

QList<QStringList> DatabaseAccessor::get_TS_Data_vals(int fileID)
{
		db.open();

	QString strQuery = "SELECT ";
	QList<QStringList> fields = query_data.get_TS_Data_fields();
	for(int i = 0; i < fields.size(); i++)
	{	
		strQuery += fields.at(i).at(0);
	}

	strQuery += " FROM TS_Data WHERE fk_file_ID = " + QString::number(fileID);


	QList<QStringList> resultValues;
	QStringList pairedVals;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			int index = 0;

			//data_type
			pairedVals.push_back(fields.at(index).at(1));					//field name
			pairedVals.push_back(query->value(index).toString());	//field value
			resultValues.push_back(pairedVals);											
			pairedVals.clear();

		}
	}
	
	delete query;
	db.close();
	return resultValues;
}

QString DatabaseAccessor::execute_query(QString strQuery)
{
	db.open();
	QString result;

	QSqlQuery *query = new QSqlQuery(db);
	query->prepare(strQuery);

	if(query->exec() == true)
	{
		while(query->next())
		{
			result = query->value(0).toString();
		}
	}
	
	delete query;
	db.close();
	return result;
}
