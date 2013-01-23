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
    std::vector<SearchResult> children;

    SearchResult(std::wstring data)
    {
        this->data = data;
    }
};

void SearchResultTreeModel::setup(SearchResultTreeItem *parent)
{
    std::vector<SearchResult> searchResults;
    SearchResult t1;
    t1.data = "Road";
    t1.children.push_back(SearchResult("road1"));
    t1.children.push_back(SearchResult("road2"));
    t1.children.push_back(SearchResult("road3"));
    searchResults.push_back(t1);

    SearchResult t2;
    t2.data = "Building";
    t2.children.push_back(SearchResult("Building1"));
    t2.children.push_back(SearchResult("Building2"));
    t2.children.push_back(SearchResult("Building3"));
    searchResults.push_back(t2);

    for(auto it = searchResults.begin(); it != SearchResult.end; ++it)
    {
        SearchResult t = *it;
        parent->insertChildren(parent->childCount(), t.children.size());
    }

}

