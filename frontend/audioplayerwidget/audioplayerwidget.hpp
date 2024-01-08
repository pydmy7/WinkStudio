#ifndef AUDIOPLAYERWIDGET_HPP
#define AUDIOPLAYERWIDGET_HPP

#include <QWidget>

namespace Ui {
class AudioPlayerWidget;
}
QT_BEGIN_NAMESPACE
class QMediaPlayer;
QT_END_NAMESPACE

class AudioPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPlayerWidget(QWidget *parent = nullptr);
    ~AudioPlayerWidget();

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::AudioPlayerWidget *ui;

    QMediaPlayer* m_mediaplayer;

    void initMembers();
    void initSignalSlots();
};

#endif // AUDIOPLAYERWIDGET_HPP
