#ifndef SELECTFOLDERSDIALOG_H
#define SELECTFOLDERSDIALOG_H

#include <qdialog.h>
#include <qdialogbuttonbox.h>
#include <qpushbutton.h>
#include <qtreeview.h>
#include <qlayout.h>

#include <QDebug>


#include "MyFileSystemModel.h"
#include "CodeInterface.h"

class MyFolderDialog : public QDialog
{
  Q_OBJECT

public:
    MyFolderDialog(QWidget *, CodeInterface *&);
	
	/**
	 * @return Selected folder paths.
	 */
    QStringList get_selected_paths();

private slots:
    void on_ok();
    void on_cancel();

private:
    QTreeView tree;
    MyFileSystemModel *model_;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QStringList paths_;

    void create_actions();
    void setup_display();
    void setup_buttons();
    void setup_tree();
    void setup_model(CodeInterface *&);

};

#endif // SELECTFOLDERSDIALOG_H
