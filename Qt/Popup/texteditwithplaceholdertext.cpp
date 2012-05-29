#include "texteditwithplaceholdertext.h"

TextEditWithPlaceHolderText::TextEditWithPlaceHolderText(QWidget *parent)
    : QTextEdit(parent)
    , m_hasActived(false)
    //, m_placeHolderText("Description")
{
}

void
TextEditWithPlaceHolderText::focusInEvent(QFocusEvent * e)
{
    if(!m_hasActived)
    {
        m_placeHolderText = this->toHtml();
        this->clear();
        QTextEdit::focusInEvent(e);
    }
}

void
TextEditWithPlaceHolderText::focusOutEvent(QFocusEvent * e)
{
    if(!m_hasActived)
        this->setText(m_placeHolderText);
    QTextEdit::focusOutEvent(e);
}

void
TextEditWithPlaceHolderText::keyPressEvent ( QKeyEvent * e )
{
    m_hasActived = true;
    QTextEdit::keyPressEvent(e);
}
