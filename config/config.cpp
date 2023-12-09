#include "config.h"

#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QSettings>

#include <iostream>

namespace config {

void switchTheme(const QString& theme)
{
    QString path = QString(":/theme/%0/%0style.qss").arg(theme);
    QFile f(path);
    if (!f.exists()) {
        std::cerr << "Unable to set stylesheet, file not found\n";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}

QString readConfigFileTheme()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    QString theme = settings.value("Theme").toString();
    settings.endGroup();
    return theme;
}

void writeConfigFileTheme(const QString& theme)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Config");
    settings.setValue("Theme", theme);
    settings.endGroup();
}

}  // namespace config
