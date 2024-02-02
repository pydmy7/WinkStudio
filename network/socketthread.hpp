#ifndef SOCKETTHREAD_HPP
#define SOCKETTHREAD_HPP

#include <QThread>
#include <QVariant>
#include <QTcpSocket>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    explicit SocketThread(const QVariant& info);

protected:
    virtual void run() override;

signals:
    void loginResult(bool flag);
    void signupResult(bool flag);

private:
    QVariant info_;

    void login(QTcpSocket& socket);
    void signup(QTcpSocket& socket);
};

#endif // SOCKETTHREAD_HPP
