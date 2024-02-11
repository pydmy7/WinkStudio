#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "utils/config/config.hpp"
#include "frontend/dialogabout/dialogabout.hpp"
#include "frontend/dialogset/dialogset.hpp"
#include "frontend/screenrecoderwidget/screenrecoderwidget.hpp"
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
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_screenrecoderwidget;
    delete m_audioplayerwidget;
}

void MainWindow::initMembers()
{
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    this->setMinimumSize(rect.size() / 2);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1);

    m_screenrecoderwidget = new ScreenRecoderWidget(this);
    m_audioplayerwidget = new AudioPlayerWidget(this);

    ui->stackedwidget->addWidget(m_screenrecoderwidget);
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
    connect(ui->btn_audioplayer, &QPushButton::clicked, this, [this]() {
        ui->stackedwidget->setCurrentIndex(1);
    });
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
