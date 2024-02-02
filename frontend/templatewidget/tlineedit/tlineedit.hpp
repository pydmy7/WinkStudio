#ifndef TLINEEDIT_HPP
#define TLINEEDIT_HPP

#include <QLineEdit>

class TLineEdit : public QLineEdit
{
    Q_OBJECT

    using QLineEdit::QLineEdit;

public:
    TLineEdit(QWidget* parent = nullptr);

protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

signals:
    void getFocus();
    void loseFocus();
};

#endif // TLINEEDIT_HPP
