#include "keyecho.hpp"

KeyEcho::KeyEcho(QProcess *parent) : QProcess(parent)
{
    QString program = R"(C:\Users\pydmy7\AppData\Local\carnac\Carnac.exe)";
    QStringList arguments;
    this->setProgram(program);
    this->setArguments(arguments);
    // 隐藏任务栏图标
}

KeyEcho::~KeyEcho()
{
    this->kill();
    this->waitForFinished();
    // kill不起作用
}

KeyEcho& KeyEcho::getInstance()
{
    static KeyEcho instance;
    return instance;
}

void KeyEcho::silentMode()
{
    std::lock_guard<std::mutex> guard(m_lock);
    // 启用静音模式:如果您想停止Carnac记录某些按键，可以按进入静音模式Ctrl+Alt+P。要退出静音模式，只需再按Ctrl+Alt+P一次即可。
    // 全局发射按键事件ctrl+alt+p
}
