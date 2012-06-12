#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlineedit.h>

#include "newproposalspopup.h"

#include <iostream>


namespace
{
    void OutputPos(const QPoint & pos)
    {
        std::wcout << "pos:" << pos.x() << ";"<< pos.y() << std::endl;
    }

    QMainWindow * FindWindow(QWidget *pWidget)
    {
        if(!pWidget)
            return NULL;
        QMainWindow *pWindow= qobject_cast<QMainWindow*>(pWidget);
        if(pWindow)
            return pWindow;
        else
            return FindWindow(pWidget->parentWidget());
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
    QWidget * parent = ui->pushButton;
    NewProposalsPopup * popup = new NewProposalsPopup(parent);

    int height = popup->height();
    int width = popup->width();

    const int HORIZONTAL_OFFSET = 5;
    const int VERTICAL_OFFSET = 50;

    QPoint relativePos = QPoint(0, - height-VERTICAL_OFFSET);
    relativePos = popup->mapToParent(relativePos);
    QPoint globalPos = parent->mapToGlobal(relativePos);

    QMainWindow * pWindow = FindWindow(parent);
    QRect rect = pWindow->geometry();
    if(globalPos.x() + width > rect.bottomRight().x())
    {
        int x = rect.bottomRight().x() - width - HORIZONTAL_OFFSET ;
        globalPos = QPoint(x, globalPos.y());
    }

    popup->move(globalPos);
    popup->setFocus();
    popup->show();
}
