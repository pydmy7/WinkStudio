#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config/config.h"
#include "dialogabout/dialogabout.h"

#include <QDesktopServices>
#include <QUrl>

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
}

void MainWindow::initConfig()
{
    themestyle = "dark";  // read config file get
    config::switchTheme(themestyle);
}

void MainWindow::switchDarkTheme()
{
    if (themestyle == "dark") {
        return;
    }
    themestyle = "dark";
    // write config file
    config::switchTheme(themestyle);
}

void MainWindow::switchLightTheme()
{
    if (themestyle == "light") {
        return;
    }
    themestyle = "light";
    // write config file
    config::switchTheme(themestyle);
}
