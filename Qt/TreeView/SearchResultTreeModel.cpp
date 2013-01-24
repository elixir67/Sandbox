#include "SearchResultTreeModel.h"
#include "SearchResultTreeItem.h"

SearchResultTreeModel::SearchResultTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    std::wstring header = L"Serach Result";

    m_root = new SearchResultTreeItem(header);
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

    SearchResultTreeItem * item = getItem(index);
    return QVariant(QString::fromStdWString(item->data()));
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
        SearchResultTreeItem * item = static_cast<SearchResultTreeItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return m_root;
}

QVariant SearchResultTreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant(QString::fromStdWString(m_root->data()));
    return QVariant();
}

QModelIndex SearchResultTreeModel::index(int row, int column, const QModelIndex & parent) const
{
    SearchResultTreeItem * parentItem = getItem(parent);
    SearchResultTreeItem * childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex SearchResultTreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    SearchResultTreeItem * childItem = getItem(child);
    SearchResultTreeItem * parentItem = childItem->parent();

    if(parentItem == m_root)
        return QModelIndex();
    return createIndex(parentItem->childNumber(), 0, parentItem);
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
    SearchResult t1(L"Road");
    t1.children.push_back(SearchResult(L"road1"));
    t1.children.push_back(SearchResult(L"road2"));
    t1.children.push_back(SearchResult(L"road3"));
    searchResults.push_back(t1);

    SearchResult t2(L"Building");
    t2.children.push_back(SearchResult(L"Building1"));
    t2.children.push_back(SearchResult(L"Building2"));
    t2.children.push_back(SearchResult(L"Building3"));
    searchResults.push_back(t2);

    for(auto it = searchResults.begin(); it != searchResults.end(); ++it)
    {
        SearchResult t = *it;
        parent->insertChildren(parent->childCount(), t.children.size());
    }

}

