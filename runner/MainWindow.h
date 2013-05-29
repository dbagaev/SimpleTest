#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "TestProject.h"
#include "TestTreeModel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void runTests();

  private:
    Ui::MainWindow *ui;

    TestProject Document;

    TestTreeModel * TestModel;
};

#endif // MAINWINDOW_H
