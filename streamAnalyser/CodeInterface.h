
/**********************************************
 ** Priovides an interface between the GUI and 
 ** the working code.
 *********************************************/
#ifndef CodeInterface_H
#define CodeInterface_H
#include <QObject>
#include <QThread>
#include "ThreadWorker.h"
#include "DatabaseAccessor.h"

class CodeInterface : public QObject
{
	Q_OBJECT

public:
	CodeInterface();
	~CodeInterface();
	void reset_db();

	/******************************************
	 * Starts the worker thread for analysing.
	 * Connects the necessary signals/slots.
	 *
	 * @param QString& - Directory path.
	 ******************************************/
  void startProcess(const QStringList &);

	/***********************************************
	 * Stops the worker thread by setting a pointer 
	 * flag to true.
	 ***********************************************/
	void stopThread();

  /***************************************
	 ** Checks whether database is present.
	 ***************************************/
	bool check_database();

  QStringList get_skipped_list();
  QStringList get_unprocessed_list();
  QStringList get_added_list();
  QStringList get_previously_selected_folders();

public slots:


  void on_log_update(QStringList, int);
	
	/************************************
	 * Emits stop status message.
	 *
	 * @param QString - status message.
	 ************************************/
	void onStatusUpdate(QString);

	/********************************************
	 * Called when the worker thread has stopped.
	 ********************************************/
	void onStop();

signals:
	void finished();
	void updateProgBar(int);
	void updateStatus(QString);

private:
	DatabaseAccessor db_access;
	QThread *thread;			
	ThreadWorker *tw;								// Worker thread object.
	bool *ptr_StopFlag;	
	bool threadRunning;		

  QStringList skipped_list;				// List of files not added beacause they already exist.
  QStringList unprocessed_list;		// List of files that could not be opened.
  QStringList added_list;					// List of files added to the database.
};

#endif
