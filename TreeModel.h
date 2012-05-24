/**************************************************************
 ** An abstract item model that holds the stream detail within
 ** a tree model.
 **************************************************************/
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>
#include <QStringList>
#include "CodeInterface.h"

class TreeItem;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	TreeModel(CodeInterface &, QObject *parent = 0);
	~TreeModel();

	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
											int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
										const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	void fetchMore ( const QModelIndex &parent );
	bool canFetchMore ( const QModelIndex & parent ) const;
	bool hasChildren (const QModelIndex & parent) const;
	
	/****************************************************
	 ** Called when the tree model needs to be updated.
	 ** Retrieves file names and calls to populate tree.
	 ***************************************************/
	void update_tree_items();

private:
	CodeInterface *code_int;			//Interface to the rest of the application code.
	QSqlDatabase _db;					//Database instance.
	TreeItem *rootItem;					//Very top tree item.  All other items are children.
	QList<TreeItem*> rootParent;		//List of tree items


	/****************************************************************************
	 ** Call for the creation of an item's sub-nodes.
	 * @param TreeItem* - Selected item (in the tree structure, it's a file name)
	 * 						that will have its sub-nodes expanded.
	 ****************************************************************************/
	void getTableValues(TreeItem *);
	
	/*************************************************************
	 ** Creates nodes for the corresponding table in the database.
	 * @param TreeItem *& - Parent node.
	 *************************************************************/
	void create_File_Properties_node(TreeItem *&);
	void create_Video_node(TreeItem *&);
	void create_Audio_node(TreeItem *&);
	void create_Signal_Root_node(TreeItem *&);
	void create_Test_Case_node(TreeItem *&);
	void create_Transport_Stream_node(TreeItem *&);
	
	/***********************************************************************************************
	 ** Populates the tree structure only with file names.
	 * @param QList<QStringList>& - List of file names. QStringList contains file id and file name.
	 **********************************************************************************************/
	void populateTree(QList<QStringList> &);
	
	/********************************
	 ** Initial setup.
	 * @param TreeItem * - Root item.
	 ********************************/
	void setupModelData(TreeItem *);
	
};

#endif
