#ifndef MYFILESYSTEMMODEL_H
#define MYFILESYSTEMMODEL_H

#include <qfilesystemmodel.h>
#include <qset.h>
#include <qvariant.h>
#include <qstringlist.h>

#include "CodeInterface.h"

/**
 * This class is a little messy and somewhat incomplete.  However, it does work.
 * Unfortunately, due to time constraints, I was unable to optimise it and make it 
 * cleaner.  The problem with the class is that when a checkbox is checked information
 * about the nodes children is then fetched so that they are checked too (if they haven't
 * been fetched already).  The operation that fetches the child node data is setRootPath(index). 
 * Once fetched the slot on_fetched() is called.  The problem is that node fetching processes are 
 * not fast enough (it uses another thread to do the work).  Therefore, there are a number of method calls
 * to the same set of methods in different places in the class: one for the checked node, and another 
 * for the children nodes once fetched.
 */
class MyFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
  MyFileSystemModel(QObject *parent, CodeInterface *&);
  
  QVariant data(const QModelIndex&, int) const;
  Qt::ItemFlags flags(const QModelIndex&) const;
  bool setData(const QModelIndex& index, const QVariant&, int );
  QStringList get_paths();

signals:

public slots:
  /**
   * Called when node is expanded.
   * @param const QModelIndex& - Index of expanded node.
   */
  void on_expand(const QModelIndex&);
  
  /**
   * Called when node data has been fetched.
   * @param const QString& - Folder path of fetched node.
   */
  void on_fetched(const QString&);

private:

  /** List of checked nodes. */
  QSet<QPersistentModelIndex> check_list;
  
  /** List of partially checked nodes */
  QSet<QPersistentModelIndex> partial_list;
  
  /** Used when class is constructed.  Used to check nodes for folders that are already in the database. */
  bool on_load;

  /**
   * Checks child nodes when parent node is checked.
   * @param const QModelIndex & - Parent node.
   */
  void check_children(const QModelIndex &);
  
  /**
   * Unchecks child nodes when parent node is unchecked.
   * @param const QModelIndex & - Parent node.
   */
  void uncheck_children(const QModelIndex &);

  /**
   * Same as above but missing a call to check_partial in the body.
   * const QModelIndex & - Parent node.
   */
  void check_children_auto(const QModelIndex &);
  void uncheck_children_auto(const QModelIndex &);


  QModelIndex current_index;
  QString last_operation ;

  /**
   * Determines whether parent nodes need to be checked,
   * partially checked or unchecked.
   */
  void check_partial(const QModelIndex& index);
  void check_partial_parents(const QModelIndex&);

  /**
   * Used to check the boxes of nodes/folders that are 
   * currently present in the database.
   */
  void check_partial_parents_on_load();
};

#endif // MyFileSystemModel_H
