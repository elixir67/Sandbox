#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

static int g_i = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(g_i));
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),SLOT(OnIntervals()));
    timer->start(1000*2);
}

void MainWindow::OnIntervals()
{
    ++g_i;
    ui->lineEdit->setText(QString::number(g_i));
}

MainWindow::~MainWindow()
{
    delete ui;
}
