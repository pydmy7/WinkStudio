#include "screenrecoderwidget.hpp"
#include "ui_screenrecoderwidget.h"

#include "utility/config/config.hpp"
#include "core/keyecho/keyecho.hpp"

#include <QDateTime>
#include <QTimer>
#include <QLCDNumber>
#include <QDesktopServices>
#include <QScreen>

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

    delete m_timer;
}

void ScreenRecoderWidget::initMembers()
{
    ui->btn_pausecontinue->setVisible(false);

    m_totseconds = 0;
    m_timer = new QTimer(this);

    keyecho_ = std::make_unique<KeyEcho>();

    //
    // m_timer->start(1000 / 24);
    // connect(m_timer, &QTimer::timeout, this, [this]() {
    //     QScreen *screen = QApplication::primaryScreen();
    //     QPixmap pixmap = screen->grabWindow();
    //     ui->openglwidget->receivePixmap(pixmap);
    // });
    //
}

void ScreenRecoderWidget::initSignalSlots()
{
    connect(m_timer, &QTimer::timeout, this, [this]() {
        ++m_totseconds;
        ui->lcdnumber->display(m_totseconds);
    });
}

void ScreenRecoderWidget::on_btn_opendir_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(config::fileaddress));
}

void ScreenRecoderWidget::on_btn_playstop_clicked()
{
    QString text = ui->btn_playstop->text();
    if (text == "开始录制") {
        text = "停止录制";
        ui->btn_pausecontinue->setVisible(true);
        // play();
    } else {
        text = "开始录制";
        ui->btn_pausecontinue->setVisible(false);
        // stop();
    }
    ui->btn_playstop->setText(text);
}

void ScreenRecoderWidget::on_btn_pausecontinue_clicked()
{
    QString text = ui->btn_pausecontinue->text();
    QIcon icon;
    if (text == "pause") {
        text = "continue";
        icon = QIcon{":/images/pause.svg"};
        // pause();
    } else {
        text = "pause";
        icon = QIcon{":/images/play.svg"};
        // pause();
    }
    ui->btn_pausecontinue->setIcon(icon);
    ui->btn_pausecontinue->setText(text);
}
