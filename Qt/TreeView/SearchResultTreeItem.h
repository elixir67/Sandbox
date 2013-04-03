#ifndef SEARCHRESULTITEM_H
#define SEARCHRESULTITEM_H


#include <vector>
//SeachItem sturcture
//-FC
//--FeatureClass
//---Element



// only has one column
class SearchResultTreeItem
{
public:
    explicit SearchResultTreeItem(const std::wstring & data, SearchResultTreeItem * parent = 0);
    ~SearchResultTreeItem();

    SearchResultTreeItem * parent();
    const std::wstring & data() const;

    SearchResultTreeItem * child(int number);
    int childCount() const;
    bool insertChildren(int position, int count);
    bool setData(const std::wstring & data);

    int childNumber() const;

private:
    SearchResultTreeItem * m_parent;
    std::vector<SearchResultTreeItem*> m_children;
    std::wstring m_data;
};

#endif // SEARCHRESULTITEM_H
