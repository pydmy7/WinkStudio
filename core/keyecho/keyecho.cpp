#include "keyecho.hpp"

#include <QApplication>
#include <QString>

KeyEcho::KeyEcho()
{
    QString program = QApplication::applicationDirPath() + "/Carnac/Carnac.exe";
    this->setProgram(program);
    this->start();
}

KeyEcho::~KeyEcho()
{
    this->terminate();
    this->kill();
}
