#include "audioplayerwidget.hpp"
#include "ui_audioplayerwidget.h"

#include <QMediaPlayer>
#include <QAudioOutput>

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

void AudioPlayerWidget::initMembers()
{
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    m_mediaplayer = new QMediaPlayer(this);
    QAudioOutput* audiooutput = new QAudioOutput(this);
    m_mediaplayer->setAudioOutput(audiooutput);
    m_mediaplayer->setSource(QUrl("file:///D:/音乐/暴躁鸡汤 - HEAVEN.mp3"));
}

void AudioPlayerWidget::initSignalSlots()
{
    connect(ui->btn_startpause, &QPushButton::clicked, this, [this]() {
        QString curtext = ui->btn_startpause->text();
        if (curtext == "start") {
            m_mediaplayer->play();
            ui->btn_startpause->setText("pause");
            ui->btn_stop->setEnabled(true);
        } else if (curtext == "pause") {
            m_mediaplayer->pause();
            ui->btn_startpause->setText("continue");
        } else {
            assert(curtext == "continue");
            m_mediaplayer->play();
            ui->btn_startpause->setText("pause");
        }
    });
    connect(ui->btn_stop, &QPushButton::clicked, this, [this]() {
        m_mediaplayer->stop();
        ui->btn_stop->setEnabled(false);
        ui->btn_startpause->setText("start");
    });
}
