#include "PathsHolder.h"
#include <qdebug.h>

PathsHolder::PathsHolder()
{
}

void PathsHolder::set_paths(QStringList &paths, QStringList &ignore)
{
  selected_paths = paths;
  ignore_paths = ignore;
}

QStringList PathsHolder::get_paths()
{
  QStringList refinedPaths(selected_paths);         // Make a copy of the selected paths

  for(QStringList::const_iterator itr1 = selected_paths.begin(); selected_paths.end() != itr1 ; ++itr1)
  {

    for(QStringList::const_iterator itr2 = selected_paths.begin(); selected_paths.end() != itr2 ; ++itr2)
    {
      if(*itr1 == *itr2)
      {
        continue;
      }

      if(itr2->startsWith(*itr1))
      {
        refinedPaths.removeAll(*itr2);
      }
    }
  }










//  for(int i = 0; i < size; i++)
//  {
//    QString str1 = selected_paths.at(i);

//    for(int j = 0; j < size; j++)
//    {
//      QString str2 = selected_paths.at(j);
//      if(str2 == str1)
//      {
//        continue;
//      }

//      if(str2.startsWith(str1))
//      {
//        refinedPaths.removeAll(str2);
//      }
//    }
//  }

//  for(int j = 0; j < refinedPaths.size();j++)
//  {
//    qDebug() << refinedPaths.at(j);
//  }

  qDebug();
  return refinedPaths;
}

QStringList PathsHolder::get_ignore_paths()
{
  return ignore_paths;
}

int PathsHolder::get_size()
{
  return selected_paths.size();
}
