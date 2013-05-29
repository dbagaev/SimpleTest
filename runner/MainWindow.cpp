#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <sstream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Redirect cout.
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    Document.LoadDll("tests.dll");

    QString text(strCout.str().c_str());
    ui->OutputEdit->setText(text);

    // Restore old cout.
    std::cout.rdbuf( oldCoutStreamBuf );

    TestModel = new TestTreeModel(&Document);
    ui->TestTree->setModel(TestModel);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete TestModel;
}

void MainWindow::runTests()
  {
  // Redirect cout.
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf( strCout.rdbuf() );

  Document.getRoot()->Run();

  QString text(strCout.str().c_str());
  ui->OutputEdit->setText(text);

  ui->TestTree->update();

  // Restore old cout.
  std::cout.rdbuf( oldCoutStreamBuf );
  }
