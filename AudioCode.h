/*************************************************************
 ** Used to hold the current audio related SQL WHERE clauses.
 ** Modified by the comboboxes from the AudioTab
 **************************************************************/
#ifndef AudioCode_H_
#define AudioCode_H_
#include <QVector>
#include <QString>
#include <QWidget>
#include <QStringList>

class AudioCode : public QWidget{
    Q_OBJECT

public:
    AudioCode();

    /**************************************
	 ** Retrieves user criteria for the
	 ** Audio tab.
	 ** @return List of SQL WHERE clauses.
	 ***************************************/
    QStringList get_clauses();

    /***************************************
   ** Resets the Audio selection filters.
   ***************************************/
    void reset();

    /****************************************
   ** Sets audio where clause string to
	 ** the selected combobox criteria.
	 ** @param QString& - field value.
	 ****************************************/
    void set_audio_format(QString &);
    void set_audio_bitrate_Kb(QString &);
    void set_channel(QString &);
    void set_content(QString &);
    void set_encryption(QString &);
    void set_language_code(QString &);
    void set_sampling(QString &);

    /******************************************
	 ** Receives field name and value.  Calls
	 ** corresponding method.
	 ** QString& - field name.
	 ** QString& - field value.
	 ********************************************/
    void updateValues(QString&, QString&);

private:

    QStringList clause_list;      // Concatenated SQL WHERE clause.

    // SQL WHERE clauses
    QString audio_format_clause;
    QString audio_bitrate_Kb_clause;
    QString channel_clause;
    QString content_clause;
    QString encryption_clause;
    QString language_code_clause;
    QString sampling_clause;

    /**********************************************
	 ** Adds current SQL WHERE clauses to the list.
	 ***********************************************/
    void append_clauses();



};
#endif /* AudioCode_H_ */
