#include "SearchResultTreeItem.h"
#include "algorithm"
SearchResultTreeItem::SearchResultTreeItem(const std::wstring & data, SearchResultTreeItem * parent)
{
    m_parent = parent;
    m_data = data;
}

SearchResultTreeItem::~SearchResultTreeItem()
{
    for(auto it = m_children.begin(); it != m_children.end(); ++it)
    {
        delete *it;
    }
}

SearchResultTreeItem * SearchResultTreeItem::parent()
{
    return m_parent;
}

const std::wstring & SearchResultTreeItem::data() const
{
    return m_data;
}

SearchResultTreeItem * SearchResultTreeItem::child(int number)
{
    return m_children[number];
}

int SearchResultTreeItem::childCount() const
{
    return m_children.size();
}

bool SearchResultTreeItem::setData(const std::wstring & data)
{
    m_data = data;
    return true;
}

bool SearchResultTreeItem::insertChildren(int position, int count)
{
    if(position < 0 || position > (int)m_children.size())
        return false;

    for(int i = 0; i < count; ++i)
    {
        std::wstring empty(L"");
        SearchResultTreeItem * item = new SearchResultTreeItem(empty, this);
        m_children.insert(m_children.begin() + position, item);
    }
    return true;
}

int SearchResultTreeItem::childNumber() const
{
    if (m_parent)
    {
        auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(),this);

        if(it != m_parent->m_children.end())
            return it - m_children.begin();
        else
            return 0;
    }
    return 0;
}
