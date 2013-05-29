#include "TestTreeModel.h"

#include "TestProject.h"

TestTreeModel::TestTreeModel(TestProject * project)
  {
  Project = project;
  }

TestTreeModel::~TestTreeModel()
  {

  }

QModelIndex TestTreeModel::index(int row, int column, const QModelIndex & parent) const
  {
  //if(!hasIndex(row, column, parent))
  //  return QModelIndex();

  TestProject::TestNode * p_parent_node;
  if(!parent.isValid())
    p_parent_node = Project->getRoot();
  else
    p_parent_node = static_cast<TestProject::TestNode *>(parent.internalPointer());

  TestProject::TestNode * p_node = p_parent_node->getChildByIndex(row);
  if(p_node != nullptr)
    return createIndex(row, column, p_node);
  else
    return QModelIndex();
  }

QModelIndex TestTreeModel::parent( const QModelIndex & index ) const
  {
  TestProject::TestNode * p_node = static_cast<TestProject::TestNode *>(index.internalPointer());
  TestProject::TestNode * p_parent_node = p_node->Parent;

  if(p_parent_node == Project->getRoot())
    return QModelIndex();

  return createIndex(p_parent_node->indexInParent(), 0, p_parent_node);
  }

int TestTreeModel::rowCount( const QModelIndex & parent ) const
  {
  if(parent.column() > 0)
    return 0;

  TestProject::TestNode * p_parent_node;
  if(!parent.isValid())
    p_parent_node = Project->getRoot();
  else
    p_parent_node = static_cast<TestProject::TestNode *>(parent.internalPointer());

  return p_parent_node->countChildren();
  }

int TestTreeModel::columnCount( const QModelIndex & parent ) const
  {
  return 3;
  }

QVariant TestTreeModel::data( const QModelIndex & index, int role ) const
  {
  TestProject::TestNode * p_node;

  if(!index.isValid())
    return QVariant();
  else
    p_node = static_cast<TestProject::TestNode *>(index.internalPointer());
    
  if (role == Qt::DisplayRole)
    {
    if(index.column() == 0)
      return QVariant(p_node->Name);
    else if(index.column() == 1)
      {
      switch(p_node->getStatus())
        {
        case TestNode::StatusOK: return QVariant("OK");
        case TestNode::StatusFail: return QVariant("Fail");
        case TestNode::StatusException: return QVariant("Exception");
        default: return QVariant("");
        }
      }
    else
      return QVariant();
    }
  if(role == Qt::CheckStateRole && index.column() == 0)
    {
    if(p_node->Active)
      return Qt::Checked;
    else
      return Qt::Unchecked;
    }
  if(role == Qt::TextColorRole)
    {
    if(p_node->getStatus() == TestNode::StatusFail || p_node->getStatus() == TestNode::StatusException)
      return QVariant(Qt::red);
    }

  return QVariant();
  }

Qt::ItemFlags TestTreeModel::flags(const QModelIndex & index) const
  {
  if(!index.isValid())
    return Qt::NoItemFlags;

  Qt::ItemFlags flag = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

  if(index.column() == 0)
    flag |= Qt::ItemIsUserCheckable;

  return flag;
/*
Qt::ItemIsTristate	64	The item is checkable with three separate states.
*/
  }

bool TestTreeModel::setData ( const QModelIndex & index, const QVariant & value, int role )
  {
  if(!index.isValid())
    return false;

  TestProject::TestNode * p_node = static_cast<TestProject::TestNode *>(index.internalPointer());
  if(p_node == nullptr)
    return false;

  if(role == Qt::CheckStateRole && index.column() == 0)
    {
    int val = value.toInt();
    if(val == Qt::Checked)
      p_node->Active = true;
    else if(val == Qt::Unchecked)
      p_node->Active = false;
    else
      return false;

    dataChanged(index, index);
    return true;
    }

  return false;
  }

QVariant TestTreeModel::headerData (int section, Qt::Orientation orientation, int role) const
  {
  if(orientation == Qt::Horizontal)
    {
    if(role == Qt::DisplayRole)
      {
      if(section == 0)
        return QString("Test name");
      else if(section == 1)
        return QString("Status");
      else
        return QString("");
      }
    }
  return QVariant();
  }
