#include "TestNode.h"

TestNode::TestNode()
  {
  Active = true;
  Status = StatusUnknown;
  }

TestNode * TestNode::addChild(QString name)
  {
  auto it_node = Children.find(name);
  if(it_node == Children.end())
    {
    TestNode * p_new_node = new TestNode;
    p_new_node->Name = name;
    p_new_node->Parent = this;
    Children[name] = p_new_node;
    return p_new_node;
    }
  else
    return *it_node;    // throw???
  }

TestNode * TestNode::findChild(QString name, bool force_add)
  {
  auto it_node = Children.find(name);

  if(it_node != Children.end())
    return *it_node;
  else if(force_add)
    return addChild(name);
  else
    return nullptr;     
  }

TestNode * TestNode::getChildByIndex(int index)
  {
  if(index < 0 || index > Children.size())
    return nullptr;

  int i = 0;
  for(auto p = Children.begin(); p!= Children.end(); ++p, ++i)
    {
    if(i == index)
      return p.value();
    }
  return nullptr;
  }

int TestNode::countChildren()
  {
  return Children.size();
  }

int TestNode::indexInParent()
  {
  if(Parent == nullptr)
    return -1;

  int index = 0;
  for(auto p = Parent->Children.begin(); p != Parent->Children.end(); ++p, ++index)
    {
    if(p.value() == this)
      return index;
    }

  return -1;
  }

void TestNode::Run()
  {
  if(!Active)
    return;

  for(auto p = Children.begin(); p != Children.end(); ++p)
    {
    p.value()->Run();
    }
  }
