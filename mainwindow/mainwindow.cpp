#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config/config.h"
#include "dialogabout/dialogabout.h"
#include "dialogset/dialogset.h"

#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMembers();
    initSignalSlots();
    initConfig();
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_timer != nullptr) {
        delete m_timer;
        m_timer = nullptr;
    }

    if (m_lcdnumber != nullptr) {
        delete m_lcdnumber;
        m_lcdnumber = nullptr;
    }
}

void MainWindow::initMembers()
{
    m_totseconds = 0;
    m_timer = new QTimer(this);
    m_lcdnumber = new QLCDNumber(this);
    ui->statusbar->addPermanentWidget(m_lcdnumber);
}

void MainWindow::initSignalSlots()
{
    connect(ui->btn_start, &QPushButton::clicked, this, [this]() {
        ui->btn_start->setEnabled(false);
        ui->btn_pausecontinue->setEnabled(true);
        ui->btn_pausecontinue->setText("pause");
        ui->btn_stop->setEnabled(true);
        m_timer->start(1E3);
        m_totseconds = 0;
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
        m_lcdnumber->display(0);
        QString text = QString("共用时%0秒").arg(m_totseconds);
        ui->statusbar->showMessage(text, 5E3);
    });
    connect(m_timer, &QTimer::timeout, this, [this]() {
        ++m_totseconds;
        m_lcdnumber->display(m_totseconds);
    });
    connect(ui->action_dark, &QAction::triggered, this, &MainWindow::switchDarkTheme);
    connect(ui->action_light, &QAction::triggered, this, &MainWindow::switchLightTheme);
    connect(ui->action_feedback, &QAction::triggered, []() {
        QDesktopServices::openUrl(QUrl(config::url_issues));
    });
    connect(ui->action_about, &QAction::triggered, this, [this]() {
        DialogAbout about(this);
        about.exec();
    });
    connect(ui->action_set, &QAction::triggered, this, [this]() {
        DialogSet set(this);
        set.exec();
    });
}

void MainWindow::initConfig()
{
    config::initConfig();
}

void MainWindow::switchDarkTheme()
{
    if (config::theme == "dark") {
        return;
    }
    config::switchTheme("dark");
}

void MainWindow::switchLightTheme()
{
    if (config::theme == "light") {
        return;
    }
    config::switchTheme("light");
}
