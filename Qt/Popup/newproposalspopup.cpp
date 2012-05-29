#include "newproposalspopup.h"
#include "ui_newproposalspopup.h"

NewProposalsPopup::NewProposalsPopup(QWidget *parent) :
    QWidget(parent, Qt::Popup),
    ui(new Ui::NewProposalsPopup)
{
    ui->setupUi(this);
}

NewProposalsPopup::~NewProposalsPopup()
{
    delete ui;
}




