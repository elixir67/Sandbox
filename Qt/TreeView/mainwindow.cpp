#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SearchResultTreeModel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tv = new QTreeView(this);
    SearchResultTreeModel * model = new SearchResultTreeModel(this);
    m_tv->setModel(model);

    //SearchResultTreeModel model();

}

MainWindow::~MainWindow()
{
    delete ui;
}
