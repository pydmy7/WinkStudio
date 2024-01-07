#include "screenrecoderwidget.hpp"
#include "ui_screenrecoderwidget.h"

#include <QTimer>
#include <QLCDNumber>
#include <QDebug>

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
}

void ScreenRecoderWidget::initMembers()
{
    m_totseconds = 0;
    m_timer = new QTimer(this);
}

void ScreenRecoderWidget::initSignalSlots()
{
    connect(ui->btn_start, &QPushButton::clicked, this, [this]() {
        ui->btn_start->setEnabled(false);
        ui->btn_pausecontinue->setEnabled(true);
        ui->btn_pausecontinue->setText("pause");
        ui->btn_stop->setEnabled(true);
        m_timer->start(1E3);
        m_totseconds = 0;
        ui->label->clear();
    });
    connect(ui->btn_pausecontinue, &QPushButton::clicked, this, [this]() {
        QString curtext = ui->btn_pausecontinue->text();
        curtext = curtext == "pause" ? "continue" : "pause";
        ui->btn_pausecontinue->setText(curtext);
    });
    connect(ui->btn_stop, &QPushButton::clicked, this, [this]() {
        ui->btn_start->setEnabled(true);
        ui->btn_pausecontinue->setEnabled(false);
        ui->btn_pausecontinue->setText("pause/continue");
        ui->btn_stop->setEnabled(false);
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
