#include "screenrecoderwidget.hpp"
#include "ui_screenrecoderwidget.h"

#include "config/config.hpp"

#include <QTimer>
#include <QLCDNumber>
#include <QDesktopServices>
#include <QLabel>
#include <QScreen>
#include <QStyleHints>
#include <QKeyEvent>

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
    if (m_keyecholabel != nullptr) {
        delete m_timer;
        m_timer = nullptr;
    }
}

bool ScreenRecoderWidget::eventFilter(QObject *watched, QEvent *event)
{
    static int screencnt = 0;
    qDebug() << "ScreenRecoderWidget::eventFilter" << screencnt++;

    if (QLabel* label = qobject_cast<QLabel*>(watched); label != nullptr) {
        if (label == m_keyecholabel && event->type() == QEvent::KeyPress) {
            QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
            QString text = keyevent->text();
            label->setText("Get a key:" + text);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ScreenRecoderWidget::initMembers()
{
    m_totseconds = 0;
    m_timer = new QTimer(this);

    m_keyecholabel = new QLabel();
    m_keyecholabel->setText("hhhhhhh");
    m_keyecholabel->setAttribute(Qt::WA_DeleteOnClose);
    m_keyecholabel->setWindowModality(Qt::NonModal);
    m_keyecholabel->setWindowFlags(Qt::FramelessWindowHint \
                                 | Qt::SplashScreen \
                                 | Qt::WindowStaysOnTopHint \
                                 | Qt::WindowTransparentForInput);
    m_keyecholabel->setAttribute(Qt::WA_TranslucentBackground);
    QFont font;
    font.setPointSize(30);
    m_keyecholabel->setFont(font);
    m_keyecholabel->resize(270, 80);
    QRect availabdesktoprect = QGuiApplication::primaryScreen()->availableGeometry();
    int right = availabdesktoprect.right(), bottom = availabdesktoprect.bottom();
    int labelwidth = m_keyecholabel->width(), labelheight = m_keyecholabel->height();
    m_keyecholabel->move(right - labelwidth, bottom - labelheight);
    m_keyecholabel->show();
    m_keyecholabel->installEventFilter(this);
}

void ScreenRecoderWidget::initSignalSlots()
{
    connect(ui->btn_startpause, &QPushButton::clicked, this, [this]() {
        QString curtext = ui->btn_startpause->text();
        if (curtext == "start") {
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
        ui->btn_stop->setEnabled(false);
        ui->btn_startpause->setText("start");
        m_timer->stop();
        ui->lcdnumber->display(0);
        QString text = QString("共用时%0秒").arg(m_totseconds);
        ui->label->setText(text);
    });

    connect(m_timer, &QTimer::timeout, this, [this]() {
        ++m_totseconds;
        ui->lcdnumber->display(m_totseconds);
    });
}

void ScreenRecoderWidget::on_btn_opendir_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(config::fileaddress));
}
