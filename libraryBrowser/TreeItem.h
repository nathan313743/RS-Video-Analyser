
#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
/**************************************************************
 ** Tree node.  Holds reference to its parent and has two data
 ** items: field name and value.
 ***************************************************************/
class TreeItem
{
public:
    /****************************************************************************
	 ** @param const QList<QVariant>& - Data to be displayed on the node entry.
	 ** @param TreeItem *parent - Reference to parent node.
	 ** @param int - pk_file_ID from File_Properties Table
	 ** @param bool - Whether it is a leaf node or not.  I.e. has children.
	 ****************************************************************************/
    TreeItem(const QList<QVariant> &, TreeItem *parent = 0, int = -1, bool hasChildren = true);
    ~TreeItem();

    /**********************************
	 ** Adds node to list of children.
	 * @param TreeItem* - Child node.
	 **********************************/
    void appendChild(TreeItem *);

    /***************************************
	 ** Returns TreeItem using given row id.
	 * @param - int - row id.
	 ****************************************/
    TreeItem *child(int);

    /**************************************
	 ** Returns the number of child nodes.
	 **************************************/
    int childCount() const;

    /*******************************************************
	 ** Returns the number of data items the TreeNode has.
	 ** one for each column.
	 *******************************************************/ 
    int columnCount() const;

    /***************************************************
	 ** Returns the pk_file_ID for this tree/file node.
	 ***************************************************/
    int get_file_ID();

    /***************************************
	 ** Returns the data from given column.
	 ****************************************/
    QVariant data(int column) const;
    int row() const;

    /**********************************************
	 ** Returns the reference for the parent node.
	 **********************************************/
    TreeItem *parent();

    /**************************************
	 ** Returns true if node has children.
	 **************************************/
    bool hasChildren();

    /*********************
	 ** Removes children.
	 *********************/
    void removeChildren();


    /******************************************************************
	 ** Returns true if all data has been fetched.
	 ** (Node data is only fetched when the top parent file node has
	 ** been expanded).
	 ******************************************************************/
    bool getTablesFetched();

    /*********************************************************
	 ** Sets whether all data has been fetched for this node.
	 * @param bool - True = yes.
	 *********************************************************/
    void setTablesFetched(bool);

    /******************************************
	 ** Returns true if node is top file node.
	 ******************************************/
    bool isFileNode() const;

    /***************************************
	 ** Sets whether node is top file node.
	 ****************************************/
    void setIsFileNode(bool);

private:
    bool tables_fetched;
    bool has_children;
    bool is_file_node;
    int file_ID;
    QList<TreeItem*> child_items;
    QList<QVariant> item_data;
    TreeItem *parent_item;
};

#endif
