#pragma once
#include <qobject.h>
#include <qthread.h>
#include <QString>

#include "DatabaseAccessor.h"
#include "DirectorySearch.h"

/**
  * This object does the processing while leaving the main thread free.
  */
class ThreadWorker : public QObject
{
    Q_OBJECT

public:
    ThreadWorker();
    ~ThreadWorker();

    /****************************************************
     * Checks whether worker thread/analyses is running.
     * @return - True if thread is running.
     ****************************************************/
    bool isRunning();

    /******************************************************************
    * Setup the worker thread.
    * @param QThread *& - Acually thread that will access the object.
    * @param DatabaseAccessor & - Reference for database access.
    * @param const QStringList & - List of file paths to process.
    * @param bool *& - stop flag to stop any processing if requested.
    *******************************************************************/
    void doSetup(QThread *&, DatabaseAccessor &, const QStringList &, bool *&);

public slots:
    /*****************************************
     ** Called when the thread is started.
     *****************************************/
    void run();

    /**************************************
     ** Emits status message.
     ** @param QString - Status message.
     ***************************************/
    void onStatusUpdate(QString);

signals:
    /**
 * Singals string list data containing what files have been added to the database etc.
 * @param QStringList - File paths.
 * @param int - type of message: 0 = files added, 1 = files unprocessed, 2 = files skipped because already exist.
 */
    void log_update(QStringList, int);
    /**
   * Emits message to be displayed on screen.
   * @param QString - Message to be displayed.
   */
    void updateStatus(QString);

    /**
     * Emitted when the thread run() process has finished.
     */
    void stop();

private:
    DatabaseAccessor *db_access;
    QStringList unprocessed_files;
    QStringList get_unprocessed_files();

    void collect_file_paths(QStringList&);
    void process_files(QStringList&, QList<FileDetails>&);
    bool isStopRequested();
    QStringList paths_;
    bool runningState;
    bool *stop_flag;
};

