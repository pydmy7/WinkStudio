#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace config {

// 加const会warning，不加const会error，好好好
const QString url_issues = "https://github.com/pydmy7/WinkStudio/issues";

void switchTheme(const QString& theme);

QString readConfigFileTheme();
void writeConfigFileTheme(const QString& theme);

}

#endif // CONFIG_H
