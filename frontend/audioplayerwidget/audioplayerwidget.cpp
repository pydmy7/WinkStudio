#include "audioplayerwidget.hpp"
#include "ui_audioplayerwidget.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QRandomGenerator>

#include "global/global.hpp"

AudioPlayerWidget::AudioPlayerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AudioPlayerWidget)
    , m_playmodetext({"单曲循环", "列表循环", "随机播放"})
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
    connect(m_mediaplayer, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            listWidgetCurrentRowIncrement(m_playmodetype);
        }
    });
    connect(ui->slider_play, &QSlider::valueChanged, this, [this](int value) {
        m_mediaplayer->setPosition(value);
    });
    connect(ui->slider_sound, &QSlider::valueChanged, this, [this](int value) {
        m_mediaplayer->audioOutput()->setVolume(value / 100.0);
    });
    connect(ui->btn_playpause, &QPushButton::clicked, this, [this]() {
        QString curtext = ui->btn_playpause->text();
        if (curtext == "play") {
            m_mediaplayer->play();
            ui->btn_playpause->setText("pause");
        } else if (curtext == "pause") {
            m_mediaplayer->pause();
            ui->btn_playpause->setText("play");
        } else {
            // std::unreachable();  // Since C++23
            unreachable();
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
        m_mediaplayer->setSource(item->data(Qt::UserRole).value<QUrl>());
        ui->btn_playpause->setText("play");
        ui->btn_playpause->click();
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
    QMenu* menu = new QMenu{this};
    menu->addActions(QList<QAction*>{m_actiondeletecurrentitem, m_actionclearlistwidget});
    menu->exec(QCursor::pos());
    delete menu;  // smart pointer. 所有权问题(应该使用哪种指针). qt中的smart pointer与cpp中smart pointer的区别.
}

void AudioPlayerWidget::listWidgetCurrentRowIncrement(int increment)
{
    int cnt = ui->listwidget->count();
    if (cnt == 0) {
        return;
    }
    int currow = ui->listwidget->currentRow();
    if (m_playmodetype == 2) {
        currow = QRandomGenerator::global()->bounded(0, cnt);
    } else {
        if (currow == -1) {
            currow = 0;
        } else {
            currow = (currow + increment + cnt) % cnt;
        }
    }
    QListWidgetItem* item = ui->listwidget->item(currow);
    emit ui->listwidget->itemDoubleClicked(item);
    ui->listwidget->setCurrentRow(currow);
}

void AudioPlayerWidget::on_btn_up_clicked()
{
    listWidgetCurrentRowIncrement(-1);
}

void AudioPlayerWidget::on_btn_down_clicked()
{
    listWidgetCurrentRowIncrement(1);
}

void AudioPlayerWidget::on_btn_playmode_clicked()
{
    m_playmodetype = (m_playmodetype + 1) % 3;
    ui->btn_playmode->setText(m_playmodetext.at(m_playmodetype));
}

void AudioPlayerWidget::on_lineedit_search_textChanged(const QString& text)
{
    auto isMatch = [](const QString& text1, const QString& text2) -> bool {
        return text1.contains(text2, Qt::CaseInsensitive);
    };

    QList<QListWidgetItem*> items;
    for (const auto& item : qAsConst(*m_listitems)) {
        if (isMatch(item->text(), text)) {
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
