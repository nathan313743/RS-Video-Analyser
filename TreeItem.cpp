#include <QStringList>
#include "TreeItem.h"


TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent, int fileID, bool hasChildren)
{
	parent_item = parent;
	item_data = data;
	file_ID = fileID;
	has_children = hasChildren;
	tables_fetched = false;
	is_file_node = false;
}


bool TreeItem::hasChildren()
{
	return has_children;
}

bool TreeItem::isFileNode() const
{
	return is_file_node;
}

void TreeItem::setIsFileNode(bool p)
{
	is_file_node = p;
}


TreeItem::~TreeItem()
{
	qDeleteAll(child_items);
}

void TreeItem::appendChild(TreeItem *item)
{
	child_items.append(item);
}


TreeItem *TreeItem::child(int row)
{
	return child_items.value(row);
}

int TreeItem::childCount() const
{
	return child_items.count();
}

int TreeItem::columnCount() const
{
	return item_data.count();
}

QVariant TreeItem::data(int column) const
{
	return item_data.value(column);
}

TreeItem *TreeItem::parent()
{
	return parent_item;
}

int TreeItem::row() const
{
	if (parent_item)
		return parent_item->child_items.indexOf(const_cast<TreeItem*>(this));

	return 0;
}

void TreeItem::removeChildren()
{
	child_items.clear();
}

bool TreeItem::getTablesFetched()
{
	return tables_fetched;
}

void TreeItem::setTablesFetched(bool p)
{
	tables_fetched = p;
}

int TreeItem::get_file_ID()
{
	return file_ID;
}