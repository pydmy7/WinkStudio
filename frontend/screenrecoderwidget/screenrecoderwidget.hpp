#ifndef SCREENRECODERWIDGET_HPP
#define SCREENRECODERWIDGET_HPP

#include <QWidget>

namespace Ui {
class ScreenRecoderWidget;
}

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class ScreenRecoderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenRecoderWidget(QWidget *parent = nullptr);
    ~ScreenRecoderWidget();

private slots:
    void on_btn_opendir_clicked();

private:
    Ui::ScreenRecoderWidget *ui;

    int m_totseconds;
    QTimer* m_timer;

    void initMembers();
    void initSignalSlots();
};

#endif // SCREENRECODERWIDGET_HPP
