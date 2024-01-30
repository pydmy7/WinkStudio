#include "screenrecoderwidget.hpp"
#include "ui_screenrecoderwidget.h"

#include "config/config.hpp"
// #include "plugin/keyecho.hpp"
#include "Record/SingletonUtils.h"
#include <QDateTime>

#include <QTimer>
#include <QLCDNumber>
#include <QDesktopServices>

ScreenRecoderWidget::ScreenRecoderWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScreenRecoderWidget)
{
    ui->setupUi(this);

    initMembers();
    initSignalSlots();
}

ScreenRecoderWidget::~ScreenRecoderWidget()
{
    delete ui;

    if (m_timer != nullptr) {
        delete m_timer;
        m_timer = nullptr;
    }

    if (m_recorder != nullptr) {
        delete m_recorder;
        m_recorder = nullptr;
    }
}

void ScreenRecoderWidget::initMembers()
{
    m_totseconds = 0;
    m_timer = new QTimer(this);

    m_recorder = new Recorder(this);
}

void ScreenRecoderWidget::initSignalSlots()
{
    connect(ui->btn_startpause, &QPushButton::clicked, this, [this]() {
        QString curtext = ui->btn_startpause->text();
        if (curtext == "start") {
            // recoder->start();
            CaptureVideoDevice *videoDevice = new CaptureVideoDevice(true,false,"系统屏幕(DXGI)","DXGI",60);
            CaptureAudioDevice *audioDevice = new CaptureAudioDevice(true,"系统声音","SOUNDCARD");
            // QString url = QString("%1/%2.mp4").arg(SingletonUtils::getInstance()->getRecordDir()).arg(QDateTime::currentDateTime().toLocalTime().toString("yyyy-MM-dd-hh-mm-ss"));
            QString url = QString("%1/%2.mp4").arg(config::fileaddress).arg(QDateTime::currentDateTime().toLocalTime().toString("yyyy-MM-dd-hh-mm-ss"));
            qDebug() << "url ==" << url;
            m_recorder->start(videoDevice, audioDevice, url);
            // recoder->start();
            ui->btn_startpause->setText("pause");
            ui->btn_stop->setEnabled(true);
            m_timer->start(1E3);
            m_totseconds = 0;
            ui->label->setText("正在录制屏幕中...");
        } else if (curtext == "pause") {
            // recoder->pause();
            ui->btn_startpause->setText("continue");
            m_timer->stop();
            ui->label->setText("录制屏幕已暂停~~~");
        } else {
            // recoder->continue();
            assert(curtext == "continue");
            ui->btn_startpause->setText("pause");
            m_timer->start(1E3);
            ui->label->setText("正在录制屏幕中...");
        }
    });
    connect(ui->btn_stop, &QPushButton::clicked, this, [this]() {
        // recoder->stop();
        m_recorder->stop();
        // recoder->stop();
        ui->btn_stop->setEnabled(false);
        ui->btn_startpause->setText("start");
        m_timer->stop();
        ui->lcdnumber->display(0);
        QString text = QString("共用时%0秒").arg(m_totseconds);
        ui->label->setText(text);
    });

    connect(m_recorder, &Recorder::setImage, ui->openglwidget, &OpenGLWidget::receiveImage);

    connect(m_timer, &QTimer::timeout, this, [this]() {
        ++m_totseconds;
        ui->lcdnumber->display(m_totseconds);
    });
}

void ScreenRecoderWidget::on_btn_opendir_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(config::fileaddress));
}

void ScreenRecoderWidget::on_checkbox_keyecho_stateChanged(int state)
{
    Q_UNUSED(state)
    // KeyEcho::getInstance().silentMode();
}
