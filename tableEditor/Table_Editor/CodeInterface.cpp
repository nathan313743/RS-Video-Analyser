#include "CodeInterface.h"


CodeInterface::CodeInterface()
{

}

CodeInterface::~CodeInterface(void)
{
}

void CodeInterface::set_file_ID(const int id)
{
	file_ID = id;
}

QStringList CodeInterface::populate_file_boxes()
{
	QStringList valueList;

	for(int i = 0; i < 5; i++)
	{
		valueList.push_back("");
	}

		QString strSelect = "SELECT" 
		" file_name, extension, size_MB, file_path, date_added"
		" FROM" 
		" File_Properties"
		" WHERE" 
		" pk_file_ID = " + QString::number(file_ID);

		db_access.executeQuery(strSelect, valueList);

		return valueList;
}

QStringList CodeInterface::populate_aud_boxes(int streamNum)
{
	//create list to size 7
	QStringList valueList;
	for(int i = 0; i < 7; i++)
	{
		valueList.push_back("");
	}

	QString strSelect = "SELECT" 
		" audio_format, audio_bitrate_Kb, sampling, channel, content, encryption, language_code"
		" FROM" 
		" Audio"
		" WHERE" 
		" pk_audio_ID = " + QString::number(streamNum) ;

	db_access.executeQuery(strSelect, valueList);

	return valueList;
}

QStringList CodeInterface::populate_sig_boxes()
{
	QStringList valueList;
	for(int i = 0; i < 3; i++)
	{
		valueList.push_back("");
	}

	QString strSelect = "SELECT" 
		" region"
		", producer"
		", source"
		" FROM" 
		" Signal_Root"
		" WHERE" 
		" pk_signal_ID = " + QString::number(file_ID);

	db_access.executeQuery(strSelect, valueList);

	return valueList;
}

QStringList CodeInterface::populate_trans_boxes()
{
	QStringList valueList;
	for(int i = 0; i < 7; i++)
	{
		valueList.push_back("");
	}

	QString strSelect = "SELECT" 
		" audio_only"
		", num_aud_services"
		", num_vid_services"
		", loop_length_ms"
		", standard"
		", ts_bitrate_Kb"
		", ts_packet_size"
		" FROM" 
		" Transport_Stream"
		" WHERE" 
		" pk_transport_ID = " + QString::number(file_ID);

	db_access.executeQuery(strSelect, valueList);

	return valueList;

}
 
QStringList CodeInterface::populate_vid_boxes(int streamNum)
{
	QStringList valueList;
	for(int i = 0; i < 13; i++)
	{
		valueList.push_back("");
	}

	QString strSelect = "SELECT" 
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
		" video_format"
		" FROM" 
		" Video"
		" WHERE" 
		" pk_video_ID = " + QString::number(streamNum);

	db_access.executeQuery(strSelect, valueList);

	return valueList;
}

QStringList CodeInterface::get_aud_stream_nums()
{
	QStringList valueList;	

	QString strSelect = "SELECT" 
		" pk_audio_ID"
		" FROM"
		" Audio"
		" WHERE"
		" fk_file_ID = " + QString::number(file_ID);

	db_access.executeQuery(strSelect, valueList);
	return valueList;
}

QStringList CodeInterface::get_vid_stream_nums()
{		
	QStringList valueList;	
	QString strSelect = "SELECT" 
		" pk_video_ID"
		" FROM"
		" Video"
		" WHERE"
		" fk_file_ID = " + QString::number(file_ID);

	db_access.executeQuery(strSelect, valueList);
	return valueList;
}

bool CodeInterface::write_aud_values(QStringList &list, int pk)
{
	QString strUpdate = "UPDATE Audio"
		" SET"
		" audio_format = '" + list.at(0)  +
		"', audio_bitrate_Kb = " + list.at(1)  +
		", channel = '" + list.at(2)  +
		"', content = '" + list.at(3)  +
		"', encryption = '" + list.at(4)  +
		"', language_code = '" + list.at(5)  +
		"', sampling = '" + list.at(6)  + 
		"' WHERE pk_audio_ID = " + QString::number(pk);
	
	bool success = db_access.executeUpdate(strUpdate);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CodeInterface::write_sig_values(QStringList &list)
{
	QString strUpdate = "UPDATE Signal_Root"
		" SET"
		" region = '" + list.at(0) +
		"', producer = '" +list.at(1) + 
		"', source = '" + list.at(2) + 
		"' WHERE pk_signal_ID = " + QString::number(file_ID);

	return db_access.executeUpdate(strUpdate);
}

bool CodeInterface::write_trans_values(QStringList &list)
{
	QString strUpdate = "UPDATE Transport_Stream"
		" SET"
		" audio_only = " + list.at(0) +
		", num_aud_services = " +list.at(1) + 
		", num_vid_services = " + list.at(2) + 
		", loop_length_ms = " +list.at(3) +
		", standard = '" + list.at(4) + 
		"', ts_bitrate_Kb = " + list.at(5) + 
		", ts_packet_size = '" + list.at(6) +
		"' WHERE pk_transport_ID = " + QString::number(file_ID);

	return db_access.executeUpdate(strUpdate);
}

bool CodeInterface::write_vid_values(QStringList &textBoxVals, int pk)
{
	
	QString strUpdate = "UPDATE Video"
		" SET"
		" aspect_ratio = '" + textBoxVals.at(0) +
		"', color_matrix = '" + textBoxVals.at(1) + 
		"', content_dimension = '" + textBoxVals.at(2) + 
		"', content_motion = '" + textBoxVals.at(3) + 
		"', content_style  = '" + textBoxVals.at(4) + 
		"', encryption = '" + textBoxVals.at(5) + 
		"', frame_rate_scan = '" + textBoxVals.at(6) + 
		"', frame_rate_value = " + textBoxVals.at(7) + 
		", res_size = '" + textBoxVals.at(8) + 
		"', res_standard = '" + textBoxVals.at(9) + 
		"', sampling = '" + textBoxVals.at(10) + 
		"', video_bitrate_Kb = " + textBoxVals.at(11) +
		", video_format = '" + textBoxVals.at(12) +
		"' WHERE pk_video_ID = " + QString::number(pk);

	bool success = db_access.executeUpdate(strUpdate);

	if(success)
	{
		return true;
	}
	else
	{
		return false;
	}
}

QVector<QStringList> CodeInterface::get_aud_autocomplete()
{
	QVector<QStringList> vecList;
	QStringList values;

	QString query = "SELECT DISTINCT audio_format FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT sampling FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT channel FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT content FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT encryption FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT language_code FROM Audio";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	return vecList;
}

QVector<QStringList> CodeInterface::get_sig_autocomplete()
{
	QVector<QStringList> vecList;
	QStringList values;

	QString query = "SELECT DISTINCT region FROM Signal_Root";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT producer FROM Signal_Root";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT source FROM Signal_Root";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	return vecList;
}

QVector<QStringList> CodeInterface::get_trans_autocomplete()
{
	QVector<QStringList> vecList;
	QStringList values;

	QString query = "SELECT DISTINCT standard FROM Transport_Stream";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT ts_packet_size FROM Transport_Stream";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	return vecList;
}

QVector<QStringList> CodeInterface::get_vid_autocomplete()
{
	QVector<QStringList> vecList;
	QStringList values;

	QString query = "SELECT DISTINCT video_format FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT encryption FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT res_size FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT res_standard FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT frame_rate_scan FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT color_matrix FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT aspect_ratio FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT sampling FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT content_dimension FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT content_motion FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	values.clear();
	query = "SELECT DISTINCT content_style FROM Video";
	db_access.executeQuery(query, values);
	vecList.push_back(values);

	return vecList;
}

void CodeInterface::add_case(QString &text)
{
	QString query = "INSERT INTO Test_Case(fk_file_ID, test_case)" 
			" VALUES( " + QString::number(file_ID) + ", '" + text + "')";
	db_access.executeUpdate(query);
	
	//remove default blank case
	query = "DELETE FROM Test_Case WHERE test_case = '' AND fk_file_ID = " + QString::number(file_ID);
	db_access.executeUpdate(query);
}

void CodeInterface::add_interface(QString &text)
{
	QString query = "INSERT INTO Interface(fk_file_ID, interface)" 
			" VALUES( " + QString::number(file_ID) + ", '" + text + "')";
	db_access.executeUpdate(query);
	
	//remove default blank case
	query = "DELETE FROM Interface WHERE interface = '' AND fk_file_ID = " + QString::number(file_ID);
	db_access.executeUpdate(query);
}

void CodeInterface::delete_case(int test_ID)
{
	QString query = "DELETE FROM Test_Case WHERE pk_test_ID = " + QString::number(test_ID);
	db_access.executeUpdate(query);

	QStringList results;
	
	query = "SELECT * FROM Test_Case WHERE fk_file_ID = "+ QString::number(file_ID);
	db_access.executeQuery(query, results);
	
	if(results.size() == 0)
	{
		query = "INSERT INTO Test_Case(fk_file_ID, test_case) VALUES (" + QString::number(file_ID) + ", '')";
	}
	db_access.executeUpdate(query);

}

void CodeInterface::delete_interface(int interface_id)
{
	QString query = "DELETE FROM Interface WHERE pk_interface_ID = " + QString::number(interface_id);
	db_access.executeUpdate(query);

	QStringList results;
	
  query = "SELECT * FROM Interface WHERE fk_file_ID = "+ QString::number(file_ID);
	db_access.executeQuery(query, results);
	
	if(results.size() == 0)
	{
    query = "INSERT INTO Interface(fk_file_ID, interface) VALUES (" + QString::number(file_ID) + ", '')";
	}
	db_access.executeUpdate(query);
}

void CodeInterface::add_TS_data(QString &text)
{
	QString query = "INSERT INTO TS_Data(fk_file_ID, data_type)" 
			" VALUES( " + QString::number(file_ID) + ", '" + text + "')";
	db_access.executeUpdate(query);
	
	//remove default blank case
	query = "DELETE FROM TS_Data WHERE data_type = '' AND fk_file_ID = " + QString::number(file_ID);
	db_access.executeUpdate(query);
}

void CodeInterface::delete_TS_data(int tsID)
{
	QString query = "DELETE FROM TS_Data WHERE pk_TSdata_ID = " + QString::number(tsID);
	db_access.executeUpdate(query);

	QStringList results;
	
	query = "SELECT * FROM TS_Data WHERE fk_file_ID = "+ QString::number(file_ID);
	db_access.executeQuery(query, results);
	
	if(results.size() == 0)
	{
		query = "INSERT INTO TS_Data(fk_file_ID, data_type) VALUES (" + QString::number(file_ID) + ", '')";
	}
	db_access.executeUpdate(query);

}


void CodeInterface::update_model(QSqlQueryModel *&model, QString query)
{
	db_access.update_model(model, (query + QString::number(file_ID)));
}

void CodeInterface::update_model_main(QSqlQueryModel *&model, QString query)
{
	db_access.update_model(model, query);
}

bool CodeInterface::delete_file(int fileID)
{
		return db_access.deleteFile(fileID);
}
