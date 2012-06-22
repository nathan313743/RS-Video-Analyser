/***************************************************
 ** Main app window that houses tabs and tree view.
 ***************************************************/
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QDialog>
#include <QGroupBox>
#include <QSqlQueryModel>
#include <QTabWidget>
#include <QMenu>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>
#include "TreeItem.h"

#include "TreeModel.h"
#include "CodeInterface.h"
#include "VideoTab.h"
#include "AudioTab.h"


class StartWindow;

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);


public slots:
    void on_ok_clicked();
    void on_combo_update(QString, QString, QString);
    void on_recevied_index(const QModelIndex &);

    /**
      * Resets any drop-down filters that have been applied.
      */
    void on_reset();

signals:

    /***********************************************************
   ** Whenever a combobox is selected a call to this is made.
   ** Notifies all tabs of change in autocomplete.
   ***********************************************************/
    void repopulate_combos();

    /**
   * Informs all tabs to clear fields.
   */
    void reset_fields();

    /********************************************
   ** Passes file path of selected video to a
   ** parent window.
   * @param QString& - File path
   *********************************************/
    void pass_file(QString &);

private:
    CodeInterface code_int;  		//Interface to other parts of the app that are not GUI

    QString chosen_file;					//seletect file path
    QTabWidget *tabWidget;
    VideoTab *video_tab;
    AudioTab *audio_tab;


    TreeModel *tree_model;		//holds tree data
    QTreeView *view;            //holds the tree model

    QAction *newAct;
    QLineEdit *lineEdit;
    QMenu *settingsMenu;
    QPushButton *buttonCancel;
    QPushButton *buttonOK;
    QPushButton *button_reset;

    void create_layout();
    void create_actions();
    void create_buttons();
    void create_tabs();

};
#endif

