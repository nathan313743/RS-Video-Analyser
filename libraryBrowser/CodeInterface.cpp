#include "CodeInterface.h"

CodeInterface::CodeInterface()
{

}

CodeInterface::~CodeInterface()
{
}

void CodeInterface::updateTable(QString table, QString field, QString value)
{
	if(table == "Video")
	{
		vid_code.updateValues(field, value);
	}
	else if(table == "Audio")
	{
		aud_code.updateValues(field, value);
	}

}

QStringList CodeInterface::get_combo_vals(QString table, QString field)
{
	return db_access.get_combo_vals(table, field, current_file_names);
}

QList<QStringList> CodeInterface::get_file_names()
{	
	current_file_names.clear();
	QString clause = "";
	QStringList vidClause = vid_code.get_clauses();

	for(int i = 0; i < vidClause.size(); i++)
	{ 
		clause += " AND " + vidClause.at(i);
	}

	QStringList audClause = aud_code.get_clauses();
	for(int i = 0; i < audClause.size(); i++)
	{
		clause += " AND " + audClause.at(i);
	}


	if(clause != "")
	{
		//Remove " AND " from front
		clause = clause.mid(4);
		
		//push to front of string
		clause.push_front(" WHERE");
	}

	QString str1 = "SELECT DISTINCT f.pk_file_ID, f.file_name"
		" FROM"
		" File_Properties f"
		" LEFT JOIN Video v ON v.fk_file_ID = f.pk_file_ID"
		" LEFT JOIN Audio a ON a.fk_file_ID = f.pk_file_ID"+ clause;

	current_file_names = db_access.get_file_names(str1);

	return current_file_names;
}

QList<QStringList> CodeInterface::get_File_Properties_vals(int fileID)
{
	return db_access.get_File_Properties_vals(fileID);
}

QList<QList<QStringList> > CodeInterface::get_Video_vals(int fileID)
{
	return db_access.get_Video_vals(fileID);
}

QList<QList<QStringList> > CodeInterface::get_Audio_vals(int fileID)
{
	return db_access.get_Audio_vals(fileID);
}

QStringList CodeInterface::get_list_query(QString &query)
{
	return db_access.get_list_query(query);
}


QString CodeInterface::execute_query(QString query)
{
	return db_access.execute_query(query);
}

void CodeInterface::reset()
{
	vid_code.reset();
	aud_code.reset();
}
