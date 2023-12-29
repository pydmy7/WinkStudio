#include "config.hpp"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QSettings>

#include <iostream>
#include <thread>
#include <mutex>

#include <QDebug>

namespace config {

std::mutex mtx;

const QString url_issues = "https://github.com/pydmy7/WinkStudio/issues";

QString theme;
QString fileaddress;

void initConfig()
{
    theme = "dark";
    fileaddress = QCoreApplication::applicationDirPath();

    if (!QFile("config.ini").exists()) {
        std::thread(config::writeAllConfigs).join();
    } else {
        std::thread(config::readAllConfigs).join();
    }
    config::switchTheme(config::theme);
}

void switchTheme(const QString& theme)
{
    QString path = QString(":/themes/%0/%0style.qss").arg(theme);
    QFile f(path);
    if (!f.exists()) {
        std::cerr << "Unable to set stylesheet, file not found.\n";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    std::thread(config::writeTheme, std::ref(theme)).join();
}

void readTheme()
{
    std::lock_guard<std::mutex> lock(mtx);

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    config::theme = settings.value("Theme").toString();
    settings.endGroup();
}

void writeTheme(const QString& theme)
{
    std::lock_guard<std::mutex> lock(mtx);

    config::theme = theme;

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    settings.setValue("Theme", theme);
    settings.endGroup();
}

void readFileAddress()
{
    std::lock_guard<std::mutex> lock(mtx);

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    config::fileaddress = settings.value("FileAddress").toString();
    settings.endGroup();
}

void writeFileAddress(const QString &fileaddress)
{
    std::lock_guard<std::mutex> lock(mtx);

    config::fileaddress = fileaddress;

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    settings.setValue("FileAddress", fileaddress);
    settings.endGroup();
}

void readAllConfigs()
{
    readTheme();
    readFileAddress();
}

void writeAllConfigs()
{
    writeTheme(theme);
    writeFileAddress(fileaddress);
}

}  // namespace config
