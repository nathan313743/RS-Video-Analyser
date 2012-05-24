#ifndef PATHSHOLDER
#define PATHSHOLDER

#include <qstringlist.h>

class PathsHolder
{
public:
  PathsHolder();

  QStringList get_paths();
  QStringList get_ignore_paths();
  void set_paths(QStringList&, QStringList&);
  int get_size();

private:
  QStringList ignore_paths;
  QStringList selected_paths;

};

#endif // PATHSHOLDER
