#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config/config.h"
#include "dialogabout/dialogabout.h"
#include "dialogset/dialogset.h"

#include <QDesktopServices>
#include <QUrl>

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
}

void MainWindow::initMembers()
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
