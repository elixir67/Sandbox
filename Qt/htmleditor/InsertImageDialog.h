#ifndef INSERTIMAGEDIALOG_H
#define INSERTIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class InsertImageDialog;
}

class InsertImageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InsertImageDialog(QWidget *parent = 0);
    ~InsertImageDialog();
    QString url() const;

protected Q_SLOTS:
    void GoToBrowser();
    void ChooseLocalImage();
    void ActivateOKButton();
    void URLEdit(const QString&);
    
private:
    Ui::InsertImageDialog * m_ui;
    QString m_url;
};

#endif // INSERTIMAGEDIALOG_H
