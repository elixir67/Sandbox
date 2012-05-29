#ifndef TEXTEDITWITHPLACEHOLDERTEXT_H
#define TEXTEDITWITHPLACEHOLDERTEXT_H

#include <QTextEdit>

class TextEditWithPlaceHolderText : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditWithPlaceHolderText(QWidget *parent = 0);
    
signals:

public slots:

protected:
    virtual void focusInEvent ( QFocusEvent * e);
    virtual void focusOutEvent ( QFocusEvent * e);
    virtual void keyPressEvent ( QKeyEvent * e );
    bool m_hasActived;
    QString m_placeHolderText;
};

#endif // TEXTEDITWITHPLACEHOLDERTEXT_H
