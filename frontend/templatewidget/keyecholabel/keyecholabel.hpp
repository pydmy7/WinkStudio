#ifndef KEYECHOLABEL_HPP
#define KEYECHOLABEL_HPP

#include <QLabel>

class KeyEchoLabel : public QLabel
{
    Q_OBJECT

public:
    explicit KeyEchoLabel(QLabel* parent = nullptr);

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // KEYECHOLABEL_HPP
