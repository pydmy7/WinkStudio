#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "config/config.hpp"
#include "frontend/dialogabout/dialogabout.hpp"
#include "frontend/dialogset/dialogset.hpp"
#include "frontend/screenrecoderwidget/screenrecoderwidget.hpp"
#include "frontend/videoplayerwidget/videoplayerwidget.hpp"
#include "frontend/audioplayerwidget/audioplayerwidget.hpp"

#include <QDesktopServices>
#include <QUrl>
#include <QScreen>
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

    if (m_screenrecoderwidget != nullptr) {
        delete m_screenrecoderwidget;
        m_screenrecoderwidget = nullptr;
    }
    if (m_videoplayerwidget != nullptr) {
        delete m_videoplayerwidget;
        m_videoplayerwidget = nullptr;
    }
    if (m_audioplayerwidget != nullptr) {
        delete m_audioplayerwidget;
        m_audioplayerwidget = nullptr;
    }
}

void MainWindow::initMembers()
{
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    this->resize(rect.width() / 2, rect.height() / 2);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 2);

    m_screenrecoderwidget = new ScreenRecoderWidget(this);
    m_videoplayerwidget = new VideoPlayerWidget(this);
    m_audioplayerwidget = new AudioPlayerWidget(this);

    // ui->stackedwidget->clear();
    for (int i = ui->stackedwidget->count() - 1; i >= 0; --i) {
        QWidget* widget = ui->stackedwidget->widget(i);
        ui->stackedwidget->removeWidget(widget);
        widget->deleteLater();
    }
    // ui->stackedwidget->clear();
    ui->stackedwidget->addWidget(m_screenrecoderwidget);
    ui->stackedwidget->addWidget(m_videoplayerwidget);
    ui->stackedwidget->addWidget(m_audioplayerwidget);
}

void MainWindow::initSignalSlots()
{
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

    connect(ui->btn_screenrecorder, &QPushButton::clicked, this, [this]() {
        ui->stackedwidget->setCurrentIndex(0);
    });
    connect(ui->btn_videoplayer, &QPushButton::clicked, this, [this]() {
        ui->stackedwidget->setCurrentIndex(1);
    });
    connect(ui->btn_audioplayer, &QPushButton::clicked, this, [this]() {
        ui->stackedwidget->setCurrentIndex(2);
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
