#ifndef TESTCASETAB_H_
#define TESTCASETAB_H_
#include <qwidget.h>
#include "DatabaseAccessor.h"
#include <qgridlayout.h>
#include <QTableWidget>
#include <qpushbutton.h>
#include <QInputDialog>
#include <qsqlquerymodel.h>
#include "CodeInterface.h"

class TestCaseTab : public QWidget
{
	Q_OBJECT

public:
	TestCaseTab(QWidget *, CodeInterface &, const bool);
	~TestCaseTab();
	bool writeNewValues();
	
private:
	CodeInterface *code_int;
	QSqlQueryModel *model;;
	QTableView *tableView;
	int test_ID;

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
