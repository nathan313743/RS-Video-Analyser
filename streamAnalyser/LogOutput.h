#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include <qdialog.h>
#include <qstringlist.h>
#include <qlayout.h>
#include <qtextedit.h>
#include <qdialogbuttonbox.h>
#include <QPushButton>
#include <qfile.h>
#include <qtextstream.h>
#include <qdatetime.h>

class LogOutput : public QDialog
{


public:
    LogOutput(QWidget*, QStringList&, QStringList&, QStringList&);

private:
    QDialogButtonBox *btnBox;
    QTextEdit *textEdit;

    void create_buttons();
    void create_layout();
    void set_text(QStringList&, QStringList&, QStringList&);

};

#endif // LOGOUTPUT_H
