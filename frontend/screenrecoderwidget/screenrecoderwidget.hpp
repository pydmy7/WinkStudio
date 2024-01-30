#ifndef SCREENRECODERWIDGET_HPP
#define SCREENRECODERWIDGET_HPP

#include <QWidget>

#include "Record/Recorder.h"

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
    void on_checkbox_keyecho_stateChanged(int state);

private:
    Ui::ScreenRecoderWidget *ui;

    int m_totseconds;
    QTimer* m_timer;

    Recorder* m_recorder;

    void initMembers();
    void initSignalSlots();
};

#endif // SCREENRECODERWIDGET_HPP
