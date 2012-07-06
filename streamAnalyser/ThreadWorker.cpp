#include "ThreadWorker.h"
#include <qdebug.h>
#include "FileProcessor.h"

ThreadWorker::ThreadWorker()
{
    runningState = true;
}

ThreadWorker::~ThreadWorker(void)
{
    //delete stop_flag;
}

void ThreadWorker::doSetup(QThread *&thread, DatabaseAccessor &dbAccess, const QStringList &paths, bool *&stopFlag)
{
    db_access = &dbAccess;

    paths_ = paths;
    stop_flag = stopFlag;
    connect(thread, SIGNAL(started()), this, SLOT(run()));

    //Qt::DirectConnection used make sure 'Finished' is printed at the end.
    connect(db_access, SIGNAL(updateStatus(QString)), this, SLOT(onStatusUpdate(QString)), Qt::DirectConnection);
}

void ThreadWorker::collect_file_paths(QStringList& file_list)
{
    //Gather file paths
    DirectorySearch ds(stop_flag);
    connect(&ds, SIGNAL(updateStatus(QString)), this, SLOT(onStatusUpdate(QString)));
    file_list = ds.get_file_names(paths_, db_access);
    emit log_update(ds.get_skipped_list(), 0);
}

void ThreadWorker::process_files(QStringList& file_list, QList<FileDetails>& processed_files)
{
    FileProcessor fp;
    connect(&fp, SIGNAL(updateStatus(QString)), this, SLOT(onStatusUpdate(QString)));
    processed_files = fp.process(file_list, stop_flag);
    emit log_update(fp.get_unprocessed(), 1);
}

void ThreadWorker::run()
{
    *stop_flag = false;
    QStringList file_list;
    collect_file_paths(file_list);

    //Check if trying to stop thread
    if(isStopRequested() == true)
    {
        onStatusUpdate("Cancelled");
        return;
    }

    //FileProcessing
    QList<FileDetails> processed_files;
    process_files(file_list, processed_files);

    if(isStopRequested() == true)
    {
        onStatusUpdate("Cancelled");
        return;
    }


    db_access->write_all_data(processed_files, stop_flag);	// Writing to a database
    emit log_update(db_access->get_added(), 2);             //.

    if(isStopRequested() == true)
    {
        onStatusUpdate("Cancelled");
        return;
    }

    onStatusUpdate("Finished");                           //Thread has now finished

    emit(stop());
    *stop_flag = false;

}

bool ThreadWorker::isRunning()
{
    return runningState;
}

void ThreadWorker::onStatusUpdate(QString strStatus)
{
    emit updateStatus(strStatus);
}

bool ThreadWorker::isStopRequested()
{
    if(*stop_flag == true)
    {
        *stop_flag = false;		//Resets stopflag
        return true;
    }
    else
    {
        return false;
    }
}
