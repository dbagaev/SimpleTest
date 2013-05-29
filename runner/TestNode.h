#pragma once

#include <QList>
#include <QMap>
#include <QString>

struct TestNode
  {
  public:
    enum {
      StatusOK,
      StatusFail,
      StatusException,
      StatusUnknown,
      };

    QString Name;
    bool Active;
    QMap<QString, TestNode *> Children;

    TestNode();

    TestNode * Parent;

    TestNode * addChild(QString name);
    TestNode * findChild(QString name, bool force_add = false);
    TestNode * getChildByIndex(int index);

    int countChildren();
    int indexInParent();

    virtual int getStatus() { return Status; };
    virtual void setStatus(int i_status) { Status = i_status; };

    virtual void Run();

  private:
    int Status;
  };
