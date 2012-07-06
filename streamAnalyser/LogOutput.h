#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include <QDialog>
#include <QStringList>
#include <QLayout>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

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
