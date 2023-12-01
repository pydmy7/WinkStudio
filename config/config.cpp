#include "config.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QApplication>

#include <iostream>

void switchTheme(const QString& theme) {
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
