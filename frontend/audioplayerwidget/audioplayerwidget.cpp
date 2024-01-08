#include "audioplayerwidget.hpp"
#include "ui_audioplayerwidget.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMouseEvent>
#include <QDir>
#include <QFileDialog>

#include "global/global.hpp"

AudioPlayerWidget::AudioPlayerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AudioPlayerWidget)
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
    if (QSlider* slider = qobject_cast<QSlider*>(watched); slider != nullptr) {
        if ((slider == ui->slider_play && event->type() == QEvent::MouseButtonRelease) || \
            (slider == ui->slider_sound && event->type() == QEvent::MouseButtonPress)) {
            QMouseEvent* mouseevent = static_cast<QMouseEvent*>(event);
            if (mouseevent->button() == Qt::LeftButton) {
                int value = QStyle::sliderValueFromPosition(slider->minimum(), slider->maximum(), mouseevent->pos().x(), slider->width());
                slider->setValue(value);
            }
        }
    }
    return QObject::eventFilter(watched, event);
}

void AudioPlayerWidget::initMembers()
{
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    ui->slider_play->installEventFilter(this);
    ui->slider_sound->installEventFilter(this);

    m_mediaplayer = new QMediaPlayer(this);
    m_mediaplayer->setAudioOutput(new QAudioOutput(this));
    // m_mediaplayer->setSource(QUrl("file:///D:/音乐/暴躁鸡汤 - HEAVEN.mp3"));
}

void AudioPlayerWidget::initSignalSlots()
{
    connect(m_mediaplayer, &QMediaPlayer::durationChanged, this, [this](int duration) {
        ui->slider_play->setMaximum(duration);
    });
    connect(m_mediaplayer, &QMediaPlayer::positionChanged, this, [this](int position) {
        ui->slider_play->blockSignals(true);
        ui->slider_play->setValue(position);
        ui->slider_play->blockSignals(false);
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
        QStringList fileaddresss = QFileDialog::getOpenFileNames(this, \
            "选择音频文件", QDir::homePath(), "音频文件(*.mp3 *.wav *.wma);;所有文件(*.*)");
        for (QString filename; const auto& fileaddress : fileaddresss) {
            filename = QFileInfo{fileaddress}.fileName();
            QListWidgetItem* item = new QListWidgetItem(filename);
            ui->listwidget->addItem(item);
        }
    });
    connect(ui->btn_delete, &QPushButton::clicked, this, [this]() {
        int idx = ui->listwidget->currentRow();
        QListWidgetItem* item = ui->listwidget->takeItem(idx);
        ui->listwidget->removeItemWidget(item);
    });
    connect(ui->btn_clear, &QPushButton::clicked, this, [this]() {
        ui->listwidget->clear();
    });
}
