#ifndef DIALOGSET_H
#define DIALOGSET_H

#include <QDialog>

namespace Ui {
class DialogSet;
}

class DialogSet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSet(QWidget *parent = nullptr);
    ~DialogSet();

private:
    Ui::DialogSet *ui;

    void initMembers();
    void initSignalSlots();
};

#endif // DIALOGSET_H
