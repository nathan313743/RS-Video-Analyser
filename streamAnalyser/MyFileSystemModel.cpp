#include "MyFileSystemModel.h"
#include <qdebug.h>
#include <qfileinfo.h>
#include <qthread.h>
#include "CodeInterface.h"

/**
  * The following constructor tries to mark the checkboxs of the folders already in the database.
  * Using this->setRootPath() tells the FileSystemModel to fetch the info from that directory path.
  * However, the information fetching is not very fast/instant as it uses a seperate thread for the
  * processing.  When the thread has finished fetching it calls the slot on_fetched.
  */
MyFileSystemModel::MyFileSystemModel(QObject *parent, CodeInterface *&codeInt) :QFileSystemModel(parent)
{
  on_load = true;                                                   // Used in a later method
  QStringList list = codeInt->get_previously_selected_folders();    // Get folders in DB

  for(int i = 0; i < list.size(); i++)
  {
    check_list.insert(this->setRootPath(list.at(i)));               // Add to check list and request file info.
  }

  emit layoutChanged();
}

Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex& index) const
{
  return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant MyFileSystemModel::data(const QModelIndex& index, int role) const
{
  if (role == Qt::CheckStateRole)
  {
    if(index.column() < 1)                        // Only first column
    {
      if(check_list.contains(index))
      {
        return Qt::Checked;
      }
      else if(partial_list.contains(index))
      {
        return Qt::PartiallyChecked;
      }
      else
      {
        return Qt::Unchecked;
      }

    }

  }
  return QFileSystemModel::data(index, role);
}


bool MyFileSystemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  on_load = false;                                // Turn off variable
  current_index = index;
  this->setRootPath(this->filePath(index));       //Fetch file info for current index

  if (role == Qt::CheckStateRole)
  {
    if(value == Qt::Checked)
    {
      check_list.insert(index);                  // Add index to checked list.
      check_children(index);                    // Check it's children (if children have not been fetched then only root/parent will be checked)
      check_partial(index);                 // Looks at parents checkbox to see whether it should be checked or partial checked.
      last_operation = "CHECK";                 // Used for on_fetched as fetching the child nodes is slow.

    }
    else
    {
      uncheck_children(index);                // Removes check box of children.
      last_operation = "UNCHECK";             // Used for on_fetched as fetching the child nodes is slow.
    }

    emit dataChanged(index, index);
    return true;
  }

  return QFileSystemModel::setData(index, value, role);
}


void MyFileSystemModel::check_children(const QModelIndex &index)
{
  int rowCount = this->rowCount(index);         // Finds the number of children nodes

  if(check_list.contains(index.parent()))       // If parent is checked, check current (child).
  {
    check_list.insert(index);
  }

  if(rowCount > 0)                              // If this child has children, check them also.
  {
    for(int i = 0; i < rowCount; i++)
    {
      check_children(index.child(i, 0));
    }
    check_list.insert(index);
    partial_list.remove(index);
  }

  emit layoutChanged();
}

void MyFileSystemModel::check_children_auto(const QModelIndex &index)
{
  int rowCount = this->rowCount(index);

  if(check_list.contains(index.parent()))
  {
    check_list.insert(index);
    removed_list.remove(index);
  }

  if(rowCount > 0)
  {
    for(int i = 0; i < rowCount; i++)
    {
      check_children_auto(index.child(i, 0));
    }
    check_list.insert(index);
    partial_list.remove(index);
    removed_list.remove(index);
  }

  emit layoutChanged();
}

void MyFileSystemModel::uncheck_children(const QModelIndex &index)
{
  int rowCount = this->rowCount(index);

  if(rowCount > 0)
  {
    for(int i = 0; i < rowCount; i++)
    {
      uncheck_children(index.child(i,0));
    }
  }

  check_list.remove(index);
  removed_list.insert(index);

  check_partial(index);

  emit layoutChanged();
}

/**
  * Removed check_partial_add(index) as this is called from on_fetched numerous times.
  */
void MyFileSystemModel::uncheck_children_auto(const QModelIndex &index)
{
  int rowCount = this->rowCount(index);

  if(rowCount > 0)
  {
    for(int i = 0; i < rowCount; i++)
    {
      uncheck_children_auto(index.child(i,0));
    }
  }

  check_list.remove(index);
  removed_list.insert(index);

  emit layoutChanged();
}

void MyFileSystemModel::on_expand(const QModelIndex& index)
{
  current_index = index;    //Index that has just been expanded.
}

/**
  * Becuase the fetching the children nodes from the setData call is slow,
  * checking and unchecking process need to be performed again.
  */
void MyFileSystemModel::on_fetched(const QString &str)
{
  if(on_load == true)
  {
    check_partial_parents_on_load();
  }
  if((last_operation == "CHECK") || (check_list.contains(current_index)))
  {
    check_children_auto(current_index);
    last_operation = "";
  }
  else if(last_operation == "UNCHECK")
  {
    uncheck_children_auto(current_index);
    last_operation = "";                    // Prevent uncheck on next expand.

  }

  emit layoutChanged();
}

QStringList MyFileSystemModel::get_paths()
{
  QStringList selected;

  foreach (QPersistentModelIndex value, check_list)
  {
    selected.push_back(this->filePath(value));
  }


  QStringList refinedPaths(selected);         // Make a copy of the selected paths

  for(QStringList::const_iterator itr1 = selected.begin(); selected.end() != itr1 ; ++itr1)
  {

    for(QStringList::const_iterator itr2 = selected.begin(); selected.end() != itr2 ; ++itr2)
    {
      if(*itr1 == *itr2)
      {
        continue;
      }

      if(itr2->contains(*itr1))
      { QString temp1 = *itr2;
        QString temp2 = *itr1;
        temp1.remove(temp2);

        if(temp1.contains("/"))
        {
          refinedPaths.removeAll(*itr2);
        }
      }
    }
  }

  qDebug();
  return refinedPaths;
}


void MyFileSystemModel::check_partial(const QModelIndex& index)
{

//  QSetIterator<QPersistentModelIndex > i(check_list);
//  while (i.hasNext())
//  {

  if(index.parent().isValid())
  {
    check_partial_parents(index.parent());
  }

   emit layoutChanged();
}

void MyFileSystemModel::check_partial_parents_on_load()
{
  QSetIterator<QPersistentModelIndex > i(check_list);
  while (i.hasNext())
  {
    check_partial_parents(i.next());
  }
  emit layoutChanged();
}

void MyFileSystemModel::check_partial_parents(const QModelIndex& index)
{
  int rowCount = this->rowCount(index);
  int childCheckCount = 0;
  int partialCheckCount = 0;

  if(rowCount > 0)
  {
    for(int i = 0; i < rowCount; i++)
    {
      if(check_list.contains(index.child(i,0)))
      {
        childCheckCount++;
      }
      else if(partial_list.contains(index.child(i,0)))
      {
        partialCheckCount++;
      }
    }

    if(rowCount == childCheckCount)
    {
      check_list.insert(index);
    }
    else if(childCheckCount > 0 || partialCheckCount > 0 )
    {
      check_list.remove(index);
      partial_list.insert(index);
    }
    else
    {
      check_list.remove(index);
      partial_list.remove(index);
    }
  }

  if(index.parent().isValid())
  {
    check_partial_parents(index.parent());
  }
}






