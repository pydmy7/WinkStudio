#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

class Client : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Client(qintptr handle);

public:
    virtual void run() override;

private:
    qintptr handle_;

    void login(QTcpSocket* socket, QByteArray& bytes);
    void signup(QTcpSocket* socket, QByteArray& bytes);
};

#endif // CLIENT_H
