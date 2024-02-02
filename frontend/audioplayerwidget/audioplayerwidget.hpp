#ifndef AUDIOPLAYERWIDGET_HPP
#define AUDIOPLAYERWIDGET_HPP

#include <QWidget>

namespace Ui {
class AudioPlayerWidget;
}
QT_BEGIN_NAMESPACE
class QMediaPlayer;
class QListWidgetItem;
QT_END_NAMESPACE

class StrHash;

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

    int m_playmodetype;
    enum class PlayModeType {
        ListLoop = 0,
        RandomPlayback = 1,
    };
    const QVector<QString> m_playmodetext;

    QMediaPlayer* m_mediaplayer;
    QAction* m_actiondeletecurrentitem;
    QAction* m_actionclearlistwidget;

    std::unique_ptr<QSet<QListWidgetItem*>> m_listitems;
    // 如果数据无限增加，会爆内存，解决办法是LRU，或者直接使用kmp
    std::unique_ptr<QHash<QString, StrHash>> m_strhashvalues;

    void initMembers();
    void initSignalSlots();

    void listWidgetCurrentRowIncrement(int playstate = -1, int increment = 0);

private slots:
    void generateContextMenu(const QPoint& pos);
    void onPlaybackStateChanged(int state);
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_btn_playmode_clicked();
    void on_lineedit_search_textChanged(const QString& text);
    void on_btn_volume_clicked();
};

#endif // AUDIOPLAYERWIDGET_HPP
