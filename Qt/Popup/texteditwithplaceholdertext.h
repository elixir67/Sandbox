#ifndef TEXTEDITWITHPLACEHOLDERTEXT_H
#define TEXTEDITWITHPLACEHOLDERTEXT_H

#include <QTextEdit>

class TextEditWithPlaceHolderText : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditWithPlaceHolderText(QWidget *parent = 0);
    bool HasPlaceHolderText(){return m_hasPlaceHolderText;}
protected Q_SLOTS:
    void OnTextChanged();

protected:
    virtual void focusInEvent ( QFocusEvent * e);
    virtual void focusOutEvent ( QFocusEvent * e);
    bool m_isLoaded;
    bool m_hasPlaceHolderText;
    QString m_placeHolderText;
};

#endif // TEXTEDITWITHPLACEHOLDERTEXT_H
