#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThreadPool>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

protected:
    void incomingConnection(qintptr handle) override;

public:
    void start(QString ip, quint16 port);
    void quit();

private:
    QThreadPool pool;
};

#endif // SERVER_H
