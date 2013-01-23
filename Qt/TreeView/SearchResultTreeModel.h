#ifndef SEARCHRESULTTREEMODEL_H
#define SEARCHRESULTTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>

class SearchResultTreeItem;

class SearchResultTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SearchResultTreeModel(QObject *parent = 0);
    ~SearchResultTreeModel();

    virtual QVariant data(const QModelIndex & index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    void setup(SearchResultTreeItem * parent);
    SearchResultTreeItem * getItem(const QModelIndex & index) const;
    SearchResultTreeItem * m_root;
};

#endif // SEARCHRESULTTREEMODEL_H
