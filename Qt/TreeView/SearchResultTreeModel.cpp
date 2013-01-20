#include "SearchResultTreeModel.h"
#include "SearchResultTreeItem.h"

SearchResultTreeModel::SearchResultTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    std::wstring header = L"Serach Result";

    m_root = new SearchResultItem(header);
    setup(m_root);
}

SearchResultTreeModel::~SearchResultTreeModel()
{
    delete m_root;
}

QVariant SearchResultTreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::ToolTipRole)
        return QVariant();

    SearchResultItem * item = getItem(index);
    return item->data();
}

Qt::ItemFlags SearchResultTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

SearchResultTreeItem * SearchResultTreeModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        SearchResultTreeItem * item = static_cast<SearchResultTreeItem*>(index.internalPointer);
        if(item)
            return item;
    }
    return m_root;
}

QVariant SearchResultTreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data();

    return QVariant();
}

QModelIndex SearchResultTreeModel::index(int row, int column, const QModelIndex & parent) const
{
    SearchResultTreeItem * parentItem = getItem(parent);
    SearchResultItem * childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row, column, children);
    else
        return QModelIndex();
}

QModelIndex SearchResultTreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    SearchResultItem * childItem = getItem(child);
    SearchResultItem * parentItem = childItem->parent();

    if(parentItem == m_root)
        return QModelIndex();
    return createIndex(parent->childNumber(), 0, parentItem);
}

int SearchResultTreeModel::rowCount(const QModelIndex &parent) const
{
    SearchResultTreeItem * parentItem = getItem(parent);
    return parentItem->childCount();
}

int SearchResultTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


struct SearchResult
{
    std::wstring data;
    std::vector<SearchResult> details;
};

void SearchResultTreeModel::setup(SearchResultTreeItem *parent)
{
    std::multimap<QString, QStringList> searchResults;

    QStringList roads;
    roads << "road001" << "road002" << endl;
    searchResults["Road"] = roads;

    QStringList trees;
    trees << "tree001" << "tree002" << end;
    searchResults["Tree"] = trees;

    QStringList buildings;
    trees << "build001" << "build002" << end;
    searchResults["Building"] = buildings;

    SearchResultTreeItem *

}

