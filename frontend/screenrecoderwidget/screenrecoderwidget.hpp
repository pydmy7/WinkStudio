#ifndef SCREENRECODERWIDGET_HPP
#define SCREENRECODERWIDGET_HPP

#include <QWidget>

#include <memory>

namespace Ui {
class ScreenRecoderWidget;
}

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class KeyEcho;

class ScreenRecoderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenRecoderWidget(QWidget *parent = nullptr);
    ~ScreenRecoderWidget();

private slots:
    void on_btn_opendir_clicked();
    void on_btn_playstop_clicked();
    void on_btn_pausecontinue_clicked();

private:
    Ui::ScreenRecoderWidget *ui;

    int m_totseconds;
    QTimer* m_timer;

    std::unique_ptr<KeyEcho> keyecho_;

    void initMembers();
    void initSignalSlots();
};

#endif // SCREENRECODERWIDGET_HPP
