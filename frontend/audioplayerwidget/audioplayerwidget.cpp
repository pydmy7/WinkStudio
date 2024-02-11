#include "audioplayerwidget.hpp"
#include "ui_audioplayerwidget.h"

#include "utils/algorithm/strhash/strhash.hpp"
#include "utils/algorithm/kmp/kmp.hpp"

#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QRandomGenerator>

#include <memory>

AudioPlayerWidget::AudioPlayerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AudioPlayerWidget)
    , m_playmodetext({"列表循环", "随机播放"})
{
    ui->setupUi(this);

    initMembers();
    initSignalSlots();
}

AudioPlayerWidget::~AudioPlayerWidget()
{
    delete ui;

    if (m_mediaplayer != nullptr) {
        delete m_mediaplayer;
        m_mediaplayer = nullptr;
    }
}

bool AudioPlayerWidget::eventFilter(QObject *watched, QEvent *event)
{
    // p.s. slider_play 定点播放, slider_sound 实时渲染
    // slider_play: MouseButtonRelease + tracking(false)
    // slider_sound: MouseButtonPress + tracking(true)
    if ((watched == ui->slider_play && event->type() == QEvent::MouseButtonRelease) || \
        (watched == ui->slider_sound && event->type() == QEvent::MouseButtonPress))
    {
        QSlider* slider = qobject_cast<QSlider*>(watched);
        QMouseEvent* mouseevent = static_cast<QMouseEvent*>(event);
        if (mouseevent->button() == Qt::LeftButton) {
            int value = QStyle::sliderValueFromPosition(slider->minimum(), slider->maximum(), mouseevent->pos().x(), slider->width());
            slider->setValue(value);
        }
    } else if (watched == ui->listwidget && event->type() == QEvent::KeyPress) {
        QListWidget* listwidget = ui->listwidget;
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if (keyevent->key() == Qt::Key_Delete) {
            QListWidgetItem* item = listwidget->takeItem(listwidget->currentRow());
            m_listitems->remove(item);
            delete item;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void AudioPlayerWidget::initMembers()
{
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    ui->slider_play->installEventFilter(this);
    ui->slider_sound->installEventFilter(this);
    ui->listwidget->installEventFilter(this);

    m_playmodetype = 0;

    m_mediaplayer = new QMediaPlayer(this);
    m_mediaplayer->setAudioOutput(new QAudioOutput(this));

    m_actiondeletecurrentitem = new QAction{"删除选中项", this};
    m_actionclearlistwidget = new QAction{"清空列表", this};

    m_listitems = std::make_unique<QSet<QListWidgetItem*>>();
    m_strhashvalues = std::make_unique<QHash<QString, StrHash>>();
}

void AudioPlayerWidget::initSignalSlots()
{
    connect(ui->listwidget, &QListWidget::customContextMenuRequested, this, &AudioPlayerWidget::generateContextMenu);
    connect(m_mediaplayer, &QMediaPlayer::durationChanged, this, [this](int duration) {
        ui->slider_play->setMaximum(duration);
        int milliseconds = duration;
        int minutes = milliseconds / (1000 * 60);
        int seconds = milliseconds % (1000 * 60) / 1000;
        QString timetext = ui->label_time->text();
        timetext.replace(6, 5, QString::asprintf("%02d:%02d", minutes, seconds));
        ui->label_time->setText(timetext);
    });
    connect(m_mediaplayer, &QMediaPlayer::positionChanged, this, [this](int position) {
        ui->slider_play->blockSignals(true);
        ui->slider_play->setValue(position);
        ui->slider_play->blockSignals(false);
        int milliseconds = position;
        int minutes = milliseconds / (1000 * 60);
        int seconds = milliseconds % (1000 * 60) / 1000;
        QString timetext = ui->label_time->text();
        timetext.replace(0, 5, QString::asprintf("%02d:%02d", minutes, seconds));
        ui->label_time->setText(timetext);
    });
    connect(m_mediaplayer, &QMediaPlayer::playbackStateChanged, this, &AudioPlayerWidget::onPlaybackStateChanged);
    connect(ui->slider_play, &QSlider::valueChanged, this, [this](int value) {
        m_mediaplayer->setPosition(value);
    });
    connect(ui->slider_sound, &QSlider::valueChanged, this, [this](int value) {
        m_mediaplayer->audioOutput()->setVolume(value / 100.0);
    });
    connect(ui->btn_playpause, &QPushButton::clicked, this, [this]() {
        if (m_mediaplayer->playbackState() == QMediaPlayer::PlayingState) {
            m_mediaplayer->pause();
        } else {
            m_mediaplayer->play();
        }
    });
    connect(ui->btn_add, &QPushButton::clicked, this, [this]() {
        ui->lineedit_search->clear();
        QStringList fileaddresss = QFileDialog::getOpenFileNames(this, \
            "选择音频文件", QDir::homePath(), "音频文件(*.mp3 *.wav *.wma);;所有文件(*.*)");
        for (QString filename; const auto& fileaddress : fileaddresss) {
            filename = QFileInfo{fileaddress}.fileName();
            QListWidgetItem* item = new QListWidgetItem(filename);
            ui->listwidget->addItem(item);
            item->setData(Qt::UserRole, QUrl::fromLocalFile(fileaddress));
            m_listitems->insert(item);
        }
    });
    connect(ui->listwidget, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        disconnect(m_mediaplayer, &QMediaPlayer::playbackStateChanged, this, &AudioPlayerWidget::onPlaybackStateChanged);
        m_mediaplayer->setSource(item->data(Qt::UserRole).value<QUrl>());
        connect(m_mediaplayer, &QMediaPlayer::playbackStateChanged, this, &AudioPlayerWidget::onPlaybackStateChanged);
        m_mediaplayer->play();
    });
    connect(m_actiondeletecurrentitem, &QAction::triggered, this, [this]() {
        if (int currentrow = ui->listwidget->currentRow(); currentrow != -1) {
            QListWidgetItem* item = ui->listwidget->takeItem(currentrow);
            m_listitems->remove(item);
            delete item;
        }
    });
    connect(m_actionclearlistwidget, &QAction::triggered, this, [this]() {
        for (int i = 0; i < ui->listwidget->count(); ++i) {
            m_listitems->remove(ui->listwidget->item(i));
        }
        ui->listwidget->clear();
    });
}

void AudioPlayerWidget::generateContextMenu(const QPoint &pos)
{
    Q_UNUSED(pos)
    std::unique_ptr<QMenu> menu = std::make_unique<QMenu>(new QMenu(this));
    menu->addActions(QList<QAction*>{m_actiondeletecurrentitem, m_actionclearlistwidget});
    menu->exec(QCursor::pos());
}

void AudioPlayerWidget::onPlaybackStateChanged(int state)
{
    if (state == QMediaPlayer::PlayingState) {
        ui->btn_playpause->setIcon(QIcon{":/images/play.svg"});
    } else if (state == QMediaPlayer::PausedState) {
        ui->btn_playpause->setIcon(QIcon{":/images/pause.svg"});
    } else if (state == QMediaPlayer::StoppedState) {
        listWidgetCurrentRowIncrement(m_playmodetype, 0);
    }
}

void AudioPlayerWidget::listWidgetCurrentRowIncrement(int playstate, int increment)
{
    int cnt = ui->listwidget->count();
    if (cnt == 0) {
        return;
    }

    int currow = ui->listwidget->currentRow();
    if (currow == -1) {
        currow = 0;
    } else {
        if (playstate == -1) {
            currow = (currow + increment + cnt) % cnt;
        } else {
            if (playstate == static_cast<int>(PlayModeType::ListLoop)) {
                currow = (currow + 1) % cnt;
            } else {
                currow = QRandomGenerator::global()->bounded(0, cnt);
            }
        }
    }

    ui->listwidget->setCurrentRow(currow);
    QListWidgetItem* item = ui->listwidget->currentItem();
    emit ui->listwidget->itemDoubleClicked(item);
}

void AudioPlayerWidget::on_btn_up_clicked()
{
    if (m_playmodetype == static_cast<int>(PlayModeType::RandomPlayback)) {
        listWidgetCurrentRowIncrement(1, 0);
    } else {
        listWidgetCurrentRowIncrement(-1, -1);
    }
}

void AudioPlayerWidget::on_btn_down_clicked()
{
    if (m_playmodetype == static_cast<int>(PlayModeType::RandomPlayback)) {
        listWidgetCurrentRowIncrement(1, 0);
    } else {
        listWidgetCurrentRowIncrement(-1, 1);
    }
}

void AudioPlayerWidget::on_btn_playmode_clicked()
{
    m_playmodetype = (m_playmodetype + 1) % 2;
    ui->btn_playmode->setText(m_playmodetext.at(m_playmodetype));
}

void AudioPlayerWidget::on_lineedit_search_textChanged(const QString& text)
{
    [[maybe_unused]]
    auto strHashMatch = [this](const QString& text1, const QString& text2) -> bool {
        if (text2.isEmpty()) {
            return true;
        }
        if (!m_strhashvalues->contains(text1)) {
            m_strhashvalues->insert(text1, StrHash{text1});
        }
        if (!m_strhashvalues->contains(text2)) {
            m_strhashvalues->insert(text2, StrHash{text2});
        }
        const StrHash strhash1 = m_strhashvalues->take(text1);
        const i64 val2 = m_strhashvalues->take(text2).getHashValueObverse(0, text2.size() - 1);
        for (int i = 0; i < text1.size() - text2.size() + 1; ++i) {
            i64 val1 = strhash1.getHashValueObverse(i, i + text2.size() - 1);
            if (val1 == val2) {
                return true;
            }
        }
        return false;
    };

    QList<QListWidgetItem*> items;
    for (const auto& item : std::as_const(*m_listitems)) {
        // if (strHashMatch(item->text(), text)) {
        //     items.push_back(item);
        // }
        if (kmp::match(item->text(), text)) {
            items.push_back(item);
        }
    }

    int cnt = ui->listwidget->count();
    for (int i = cnt - 1; i >= 0; --i) {
        ui->listwidget->takeItem(i);
    }

    for (const auto& item : items) {
        ui->listwidget->addItem(item);
    }
}

void AudioPlayerWidget::on_btn_volume_clicked()
{
    static std::pair<bool, int> slidersoundstate = {ui->slider_sound->value() == 0, ui->slider_sound->value()};
    auto& [mute, lastvalue] = slidersoundstate;
    mute = !mute;
    if (mute) {
        ui->btn_volume->setIcon(QIcon(":/images/mute.svg"));
        int lastvalue_ = ui->slider_sound->value();
        lastvalue = lastvalue_;
        ui->slider_sound->setValue(0);
    } else {
        ui->btn_volume->setIcon(QIcon(":/images/audio.svg"));
        ui->slider_sound->setValue(lastvalue);
    }
}
