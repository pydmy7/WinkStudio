#include "tlineedit.hpp"

#include <QFocusEvent>

TLineEdit::TLineEdit(QWidget* parent)
    :QLineEdit(parent)
{}

void TLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit TLineEdit::getFocus();
}

void TLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit TLineEdit::loseFocus();
}
