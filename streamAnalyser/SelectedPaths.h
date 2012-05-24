#ifndef SELECTEDPATHS_H
#define SELECTEDPATHS_H

#include <qstringlist.h>

class SelectedPaths
{
public:
  SelectedPaths(QStringList&, QStringList&);

  QStringList get_paths();
  QStringList get_ignore_paths();

private:
  QStringList ignore_paths;
  QStringList selected_paths;

};

#endif // SELECTEDPATHS_H
