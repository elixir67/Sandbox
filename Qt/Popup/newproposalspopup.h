#ifndef NEWPROPOSALSPOPUP_H
#define NEWPROPOSALSPOPUP_H

#include <QDialog.h>
#include <QWidget.h>

namespace Ui {
class NewProposalsPopup;
}

class NewProposalsPopup : public QWidget
{
    Q_OBJECT
    
public:
    explicit NewProposalsPopup(QWidget *parent = 0);
    ~NewProposalsPopup();

protected Q_SLOTS:
    void OnCreateClicked();
    
private:
    Ui::NewProposalsPopup *ui;
};

#endif // NEWPROPOSALSPOPUP_H
