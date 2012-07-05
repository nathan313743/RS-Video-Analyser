#ifndef TABLEVIEWER_H_
#define TABLEVIEWER_H_

#include <QObject>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QMessageBox>
#include "DatabaseAccessor.h"
#include "DetailsWindow.h"
#include "CodeInterface.h"

class TableViewer : public QDialog
{
	Q_OBJECT

public:
	TableViewer(QWidget *parent = 0);
	~TableViewer();
	QSqlQueryModel *model;

public slots:
	void onReceviedIndex(const QModelIndex &);
	void onView();
	void onEdit();
	void onDelete();
	void onCancel();

private:
	void errorMessage(QString);
	void setupTable();
	void setupButtons();
	void show_details_window(bool);
	DatabaseAccessor db_access;
	CodeInterface code_int;

	int file_ID;

	QTableView *tableView;
	QPushButton *btnView;
	QPushButton *btnEdit;
	QPushButton *btnDelete;
	QPushButton *btnCancel;

};

#endif
