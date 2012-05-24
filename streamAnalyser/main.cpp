#include "StartWindow.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StartWindow w;
	w.show();
	return a.exec();
}
