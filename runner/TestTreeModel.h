#pragma once

#include <QAbstractItemView>

class TestProject;

class TestTreeModel : public QAbstractItemModel
{
  public:
    TestTreeModel(TestProject * project);
    ~TestTreeModel();

    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

    Qt::ItemFlags TestTreeModel::flags ( const QModelIndex & index ) const;

    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

  private:
    TestProject * Project;
};