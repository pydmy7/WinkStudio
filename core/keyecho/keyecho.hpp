#ifndef KEYECHO_HPP
#define KEYECHO_HPP

#include <QProcess>

class KeyEcho : public QProcess
{
    Q_OBJECT
public:
    KeyEcho();
    ~KeyEcho();
};

#endif // KEYECHO_HPP
