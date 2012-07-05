#include <QtGui/QApplication>
#include "TableViewer.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  TableViewer tViewer;
  tViewer.show();
  return app.exec();
}
