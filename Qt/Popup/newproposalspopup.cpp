#include "NewProposalsPopup.h"
#include "ui_NewProposalsPopup.h"
#include "qmessagebox.h"

NewProposalsPopup::NewProposalsPopup(QWidget *parent) :
    QWidget(parent, Qt::Popup),
    ui(new Ui::NewProposalsPopup)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnCreateClicked()));
}

NewProposalsPopup::~NewProposalsPopup()
{
    delete ui;
}

void
NewProposalsPopup::OnCreateClicked()
{

    QString s = ui->descTextEdit->toPlainText();
        if(ui->descTextEdit->HasPlaceHolderText())
            s = tr("HasPlaceHolderText");
    QMessageBox::warning(
                        this,
                        tr("Add Proposal"),
                        s
                    );
}




