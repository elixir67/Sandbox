#include "TextEditWithPlaceHolderText.h"
#include <QAction>

TextEditWithPlaceHolderText::TextEditWithPlaceHolderText(QWidget *parent)
    : QTextEdit(parent)
    , m_isLoaded(false)
    , m_hasPlaceHolderText(true)
    , m_placeHolderText("")
{
    connect(this, SIGNAL(textChanged ()), this, SLOT(OnTextChanged()));
}

void
TextEditWithPlaceHolderText::focusInEvent(QFocusEvent * e)
{
    m_isLoaded = true;
    if(m_hasPlaceHolderText)
    {
        m_placeHolderText = this->toHtml();
        this->blockSignals(true);
        this->clear();
        this->blockSignals(false);
    }
    QTextEdit::focusInEvent(e);
}

void
TextEditWithPlaceHolderText::focusOutEvent(QFocusEvent * e)
{
    if(m_hasPlaceHolderText)
    {
        this->blockSignals(true);
        this->setText(m_placeHolderText);
        this->blockSignals(false);
    }
    QTextEdit::focusOutEvent(e);
}

void
TextEditWithPlaceHolderText::OnTextChanged()
{
    if(m_isLoaded)
        m_hasPlaceHolderText = false;
}

