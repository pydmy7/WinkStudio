#include "config.hpp"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QSettings>

#include <iostream>
#include <thread>
#include <mutex>
#include <future>

#include <QDebug>

namespace config {

std::mutex mtx;

const QString url_issues = QStringLiteral("https://github.com/pydmy7/WinkStudio/issues");

QString theme;
QString fileaddress;

void initConfig()
{
    theme = "dark";
    fileaddress = QCoreApplication::applicationDirPath();

    if (!QFile("config.ini").exists()) {
        config::writeAllConfigs();
    } else {
        config::readAllConfigs();
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
    std::future<void> futuretheme = std::async(config::readTheme);
    std::future<void> futurefileaddress = std::async(config::readFileAddress);
    futuretheme.get();
    futurefileaddress.get();
}

void writeAllConfigs()
{
    std::future<void> futuretheme = std::async(config::writeTheme, std::ref(theme));
    std::future<void> futurefileaddress = std::async(config::writeFileAddress, std::ref(fileaddress));
    futuretheme.get();
    futurefileaddress.get();
}

}  // namespace config
