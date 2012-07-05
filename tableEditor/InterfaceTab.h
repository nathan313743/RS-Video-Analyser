#ifndef INTERFACE_TAB_H_
#define INTERFACE_TAB_H_
#include <QWidget>
#include "DatabaseAccessor.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QSqlQueryModel>
#include "CodeInterface.h"

class InterfaceTab : public QWidget
{
	Q_OBJECT

public:
	InterfaceTab(QWidget *, CodeInterface &, const bool);
	~InterfaceTab();
	bool writeNewValues();
	
private:
	CodeInterface *code_int;
	QSqlQueryModel *model;;
	QTableView *tableView;
	int interface_id;

	void setupLayout();
	void setupTable();
	void setReadWrite(const bool);
	void setupButtons();
	QPushButton *btnAdd;
	QPushButton *btnDelete;



private slots:
	void on_delete();
	void on_add();
	void on_recevied_index(const QModelIndex &index);

};
#endif
