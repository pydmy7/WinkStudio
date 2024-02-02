#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace std {
class mutex;
}

namespace config {

extern std::mutex mtx;

extern const QString url_issues;

extern QString theme;
extern QString fileaddress;

void initConfig();

void switchTheme(const QString& theme);
void readTheme();
void writeTheme(const QString& theme);

void readFileAddress();
void writeFileAddress(const QString& fileaddress);

void readAllConfigs();
void writeAllConfigs();

}

#endif // CONFIG_H
