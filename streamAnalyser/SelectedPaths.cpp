#include "SelectedPaths.h"

SelectedPaths::SelectedPaths(QStringList &paths, QStringList &ignore)
{
  selected_paths = paths;
  ignore_paths = ignore;
}

QStringList SelectedPaths::get_paths()
{
  return selected_paths;
}

QStringList SelectedPaths::get_ignore_paths()
{
  return ignore_paths;
}
