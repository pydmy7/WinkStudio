#ifndef KEYECHO_HPP
#define KEYECHO_HPP

#include <QObject>
#include <QProcess>

#include <mutex>

class KeyEcho : public QProcess
{
    Q_OBJECT

private:
    explicit KeyEcho(QProcess* parent = nullptr);
    ~KeyEcho();
    KeyEcho(const KeyEcho&) = delete;
    KeyEcho& operator=(const KeyEcho&) = delete;

public:
    static KeyEcho& getInstance();

private:
    std::mutex m_lock;

public:
    void silentMode();
};

#endif // KEYECHO_HPP
