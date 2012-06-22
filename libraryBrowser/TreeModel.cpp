#include <QtGui>
#include "TreeItem.h"
#include "TreeModel.h"
#include <QSqlQuery>
#include <QVector>


TreeModel::TreeModel(CodeInterface &codeInt, QObject *parent) : QAbstractItemModel(parent)
{
    code_int = &codeInt;

    QList<QVariant> rootData;
    rootData << "File" << "Value";
    rootItem = new TreeItem(rootData);
    setupModelData(rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if(parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if(parent.column() > 0)
        return 0;

    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupModelData(TreeItem *parent)
{
    rootParent << parent;

    QList<QStringList> fileNames = code_int->get_file_names();  //Retieves all file names

    populateTree(fileNames);
}

void TreeModel::populateTree(QList<QStringList> &fileNames)
{
    QList<QVariant> columnData;
    rootItem->removeChildren();
    int fileID;

    for(int i = 0; i < fileNames.size(); i++)
    {
        columnData.clear();
        fileID = fileNames.at(i).at(0).toInt();			//File ID
        columnData << fileNames.at(i).at(1) << "";	//File Name
        TreeItem *fileNode = new TreeItem(columnData, rootParent.last(), fileID);
        fileNode->setIsFileNode(true);
        rootParent.last()->appendChild(fileNode);
    }
    emit layoutChanged();
}

void TreeModel::fetchMore(const QModelIndex &parent)
{
    if(parent.isValid())
    {
        int i = parent.row();
        TreeItem *ptrSelectedItem = rootParent[0]->child(i);
        getTableValues(ptrSelectedItem);
    }
}

void TreeModel::create_File_Properties_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "File Properties" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QStringList> tabelValues = code_int->get_File_Properties_vals(fileID);

    for(int j = 0; j < tabelValues.size(); j++)												//Loop through all columns
    {
        QList<QVariant> columnData;
        columnData.clear();
        columnData << tabelValues.at(j).at(0) << tabelValues.at(j).at(1);
        tableRoot->appendChild(new TreeItem(columnData, tableRoot, fileID, false));
    }
}

void TreeModel::create_Video_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "Video" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QList<QStringList> > streamList = code_int->get_Video_vals(fileID);

    // Through all streamList
    for(int i = 0; i < streamList.size(); i++)
    {
        QList<QVariant> streamData;
        streamData << "Stream " + QString::number(i+1) << "";

        TreeItem *streamRoot = new TreeItem(streamData, tableRoot, fileID);

        tableRoot->appendChild(streamRoot);
        ptrRootItem->setTablesFetched(true);
        streamRoot->setTablesFetched(true);

        QList<QStringList> singleStream = streamList.at(i);

        for(int j = 0; j < singleStream.size(); j++)												//Loop through all columns
        {
            QList<QVariant> columnData;
            columnData.clear();
            columnData << singleStream.at(j).at(0) << singleStream.at(j).at(1);
            streamRoot->appendChild(new TreeItem(columnData, streamRoot, fileID, false));
        }
    }
}

void TreeModel::create_Audio_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "Audio" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QList<QStringList> > streamList = code_int->get_Audio_vals(fileID);

    //through all streamList
    for(int i = 0; i < streamList.size(); i++)
    {
        QList<QVariant> streamData;
        streamData << "Stream " + QString::number(i+1) << "";

        TreeItem *streamRoot = new TreeItem(streamData, tableRoot, fileID);

        tableRoot->appendChild(streamRoot);
        ptrRootItem->setTablesFetched(true);
        streamRoot->setTablesFetched(true);

        QList<QStringList> singleStream = streamList.at(i);

        for(int j = 0; j < singleStream.size(); j++)												//Loop through all columns
        {
            QList<QVariant> columnData;
            columnData.clear();
            columnData << singleStream.at(j).at(0) << singleStream.at(j).at(1);
            streamRoot->appendChild(new TreeItem(columnData, streamRoot, fileID, false));
        }
    }
}

void TreeModel::create_Signal_Root_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "Signal Root" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QStringList> tabelValues = code_int->get_Signal_Root_vals(fileID);

    for(int j = 0; j < tabelValues.size(); j++)												//Loop through all columns
    {
        QList<QVariant> columnData;
        columnData.clear();
        columnData << tabelValues.at(j).at(0) << tabelValues.at(j).at(1);
        tableRoot->appendChild(new TreeItem(columnData, tableRoot, fileID, false));
    }
}

void TreeModel::create_Test_Case_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "Test Case" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QStringList> tabelValues = code_int->get_Test_Case_vals(fileID);

    for(int j = 0; j < tabelValues.size(); j++)												//Loop through all columns
    {
        QList<QVariant> columnData;
        columnData.clear();
        columnData << tabelValues.at(j).at(0) << tabelValues.at(j).at(1);
        tableRoot->appendChild(new TreeItem(columnData, tableRoot, fileID, false));
    }
}

void TreeModel::create_Transport_Stream_node(TreeItem *&ptrRootItem)
{
    int fileID = ptrRootItem->get_file_ID();
    QList<QVariant> tableData;
    tableData << "Transport Stream" << "";

    TreeItem *tableRoot = new TreeItem(tableData, ptrRootItem, fileID);

    ptrRootItem->appendChild(tableRoot);
    ptrRootItem->setTablesFetched(true);
    tableRoot->setTablesFetched(true);

    QList<QStringList> tabelValues = code_int->get_Transport_Stream_vals(fileID);

    for(int j = 0; j < tabelValues.size(); j++)												//Loop through all columns
    {
        QList<QVariant> columnData;
        columnData.clear();
        columnData << tabelValues.at(j).at(0) << tabelValues.at(j).at(1);
        tableRoot->appendChild(new TreeItem(columnData, tableRoot, fileID, false));
    }

    //make TS_Data branch
    QList<QStringList> ts_dataVals = code_int->get_TS_Data_vals(fileID);

    if(ts_dataVals.size() > 0)
    {
        QList<QVariant> columnData;
        columnData << "Data" << "";
        TreeItem *dataRoot= new TreeItem(columnData, tableRoot, fileID);
        dataRoot->setTablesFetched(true);

        for(int j = 0; j < ts_dataVals.size(); j++)
        {
            QList<QVariant> columnData;
            columnData.clear();
            columnData << ts_dataVals.at(j).at(0) + " " + QString::number(j+1) << ts_dataVals.at(j).at(1);
            dataRoot->appendChild(new TreeItem(columnData, dataRoot, fileID, false));
        }

        tableRoot->appendChild(dataRoot);
    }
}

void TreeModel::getTableValues(TreeItem *ptrRootItem)
{
    create_File_Properties_node(ptrRootItem);
    create_Audio_node(ptrRootItem);
    create_Video_node(ptrRootItem);
    create_Signal_Root_node(ptrRootItem);
    create_Test_Case_node(ptrRootItem);
    create_Transport_Stream_node(ptrRootItem);
}

bool TreeModel::canFetchMore(const QModelIndex &parent )const
{
    if(parent.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(parent.internalPointer());

        if(item->getTablesFetched() == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool TreeModel::hasChildren (const QModelIndex &parent = QModelIndex()) const
{
    if(parent.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(parent.internalPointer());

        if(item->hasChildren() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void TreeModel::update_tree_items()
{
    QList<QStringList> fileNames = code_int->get_file_names();  //Retieves all file names
    populateTree(fileNames);
}
