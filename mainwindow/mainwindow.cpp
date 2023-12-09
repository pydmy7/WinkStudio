#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config/config.h"
#include "dialogabout/dialogabout.h"
#include "dialogset/dialogset.h"

#include <QDesktopServices>
#include <QUrl>
#include <QFile>

#include <thread>
#include <future>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMember();
    initSignalSlots();
    initConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMember()
{
    m_themestyle = "dark";
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
}

void MainWindow::initConfig()
{
    if (!QFile("config.ini").exists()) {
        std::thread(config::writeConfigFileTheme, std::ref(m_themestyle)).detach();
    } else {
        std::future<QString> futureres = std::async(config::readConfigFileTheme);
        m_themestyle = futureres.get();
    }
    config::switchTheme(m_themestyle);
}

void MainWindow::switchDarkTheme()
{
    if (m_themestyle == "dark") {
        return;
    }
    m_themestyle = "dark";
    config::switchTheme(m_themestyle);
    std::thread(config::writeConfigFileTheme, std::ref(m_themestyle)).detach();
}

void MainWindow::switchLightTheme()
{
    if (m_themestyle == "light") {
        return;
    }
    m_themestyle = "light";
    config::switchTheme(m_themestyle);
    std::thread(config::writeConfigFileTheme, std::ref(m_themestyle)).detach();
}
