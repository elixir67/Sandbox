#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlineedit.h>

#include "newproposalspopup.h"

#include <iostream>

#define OFFSET 5
namespace
{
    void OutputPos(const QPoint & pos)
    {
        std::wcout << "pos:" << pos.x() << ";"<< pos.y() << std::endl;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handleClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActiveDescription()
{
    ui->textEdit->clear();
    // QObject::disconnect(ui->textEdit, SIGNAL(clicked()), this, SLOT(ActiveDescription()));
}

void MainWindow::handleClick()
{
    NewProposalsPopup * popup = new NewProposalsPopup(ui->pushButton);

    QPoint pos = ui->pushButton->pos();
    OutputPos(pos);

    QPoint pg, pp, ppg;
    pg = ui->pushButton->mapToGlobal(pos);
    OutputPos(pg);

    int pHeight = popup->height();
    int pWidth = popup->width();

    QPoint p = QPoint(OFFSET, - pHeight-OFFSET);
    pp = popup->mapToParent(p);
    OutputPos(pp);
    ppg = ui->pushButton->mapToGlobal(pp);
    OutputPos(ppg);

    QPoint pos0 = popup->pos();
    QPoint pos1 = popup->pos();
    OutputPos(pos1);

    popup->setFocus();
    popup->show();
    popup->move(ppg);

    QPoint pos2 = popup->pos();
    OutputPos(pos2);
}
