#include "CodeInterface.h"
#include <qthread.h>

CodeInterface::CodeInterface()
{
	threadRunning = false;
	ptr_StopFlag = new bool;

	
}

CodeInterface::~CodeInterface(void)
{
}

QStringList CodeInterface::get_previously_selected_folders()
{
  return db_access.get_previously_selected_folders();
}

bool CodeInterface::check_database()
{
  return db_access.check_connection();
}

void CodeInterface::startProcess(const QStringList &paths)
{
	stopThread();
	threadRunning = true;
	emit updateProgBar(0);

	tw = new ThreadWorker;
	thread = new QThread;

	connect(tw, SIGNAL(updateStatus(QString)), this, SLOT(onStatusUpdate(QString)));
	connect(tw, SIGNAL(stop()), this, SLOT(onStop()));
  connect(tw, SIGNAL(log_update(QStringList, int)), this, SLOT(on_log_update(QStringList, int)), Qt::DirectConnection);

  tw->doSetup(thread, db_access, paths, ptr_StopFlag);
	tw->moveToThread(thread);
	thread->start();
}

void CodeInterface::stopThread()
{
	if(threadRunning == true)
	{
		*ptr_StopFlag = true;

		while(*ptr_StopFlag == true);
		onStop();
		
    //thread->terminate();
    //delete tw;
    //delete thread;
	}
}

void CodeInterface::reset_db()
{
	db_access.reset_db();
}

void CodeInterface::onStop()
{
	threadRunning = false;
	emit(updateProgBar(1));
	emit finished();
	emit(updateStatus("Finished"));
}

void CodeInterface::onStatusUpdate(QString msg)
{
	emit(updateStatus(msg));
}

void CodeInterface::on_log_update(QStringList list, int type)
{
  //Exist - skipped
  if(type == 0)
  {
    skipped_list = list;
    qDebug() << QString::number(list.size());
  }

  //Not processed
  else if(type == 1)
  {
    unprocessed_list = list;
        qDebug() << QString::number(list.size());
  }

  //Added to DB
  else if(type == 2)
  {
    added_list = list;
        qDebug() << QString::number(list.size());
  }
}

QStringList CodeInterface::get_skipped_list()
{
  return skipped_list;
}

QStringList CodeInterface::get_unprocessed_list()
{
  return unprocessed_list;
}

QStringList CodeInterface::get_added_list()
{
  return added_list;
}

