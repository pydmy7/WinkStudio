#include "server.hpp"

#include "client.hpp"

Server::Server(QObject *parent)
    : QTcpServer{parent}
{
    pool.setMaxThreadCount(200);
    qInfo() << "thread pool max count:" << pool.maxThreadCount();
}

Server::~Server()
{
    quit();
}

void Server::incomingConnection(qintptr handle)
{
    // Not version friendly!!!
    qInfo() << "Incomming Connection" << handle;
    Client* client = new Client{handle};
    client->setAutoDelete(true);
    pool.start(client);
}

void Server::start(QString ip, quint16 port)
{
    if (this->listen(QHostAddress{ip}, port)) {
        qInfo() << "server listen on port:" << port << "success";
    } else {
        qCritical() << "server listen fail";
        qCritical() << this->errorString();
    }
}

void Server::quit()
{
    this->close();
    qInfo() << "server stopped!";
}
