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

    // 0:单曲循环/1:列表循环/2:随机播放
    int m_playmodetype;
    const QVector<QString> m_playmodetext;

    QMediaPlayer* m_mediaplayer;
    QAction* m_actiondeletecurrentitem;
    QAction* m_actionclearlistwidget;

    void initMembers();
    void initSignalSlots();

    void listWidgetCurrentRowIncrement(int increment);

private slots:
    void generateContextMenu(const QPoint& pos);
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_btn_playmode_clicked();
};

#endif // AUDIOPLAYERWIDGET_HPP
