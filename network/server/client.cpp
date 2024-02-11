#include "client.hpp"

#include "dataformat.hpp"
#include "database.hpp"

#include <QThread>
#include <QDebug>

#include <iostream>

Client::Client(qintptr handle)
    : QObject{nullptr}
{
    handle_ = handle;
}

void Client::run()
{
    qInfo() << "handle:" << handle_ << "run on thread:" << QThread::currentThread();

    QTcpSocket* socket = new QTcpSocket{};
    if (!socket->setSocketDescriptor(handle_)) {
        qCritical() << socket->errorString();
        delete socket;
        return;
    }

    socket->waitForReadyRead();
    QByteArray request = socket->readAll();

    qint8 type = request.at(0);
    if (type == DataFormat::LoginClient::type) {
        login(socket, request);
    } else if (type == DataFormat::SignupClient::type) {
        signup(socket, request);
    } else {
        ddosSiege(socket);
    }

    socket->waitForBytesWritten();
    socket->close();
    socket->deleteLater();

    qInfo() << "handle:" << handle_ << "done on thread:" << QThread::currentThread();
}

void Client::ddosSiege(QTcpSocket *socket)
{
    std::cerr << "ddos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    socket->write("?");
}

void Client::login(QTcpSocket* socket, QByteArray &bytes)
{
    DataFormat::LoginClient info = DataFormat::deSerialize<DataFormat::LoginClient>(bytes);
    bool flag = DataBase::getInstance().login(info.username, info.password);
    socket->write(DataFormat::serialize(DataFormat::LoginServer{flag}));

    qDebug() << "Client::login";
    qDebug() << "username:" << info.username << "password:" << info.password;
    qDebug() << "result:" << flag;
}

void Client::signup(QTcpSocket* socket, QByteArray &bytes)
{
    DataFormat::SignupClient info = DataFormat::deSerialize<DataFormat::SignupClient>(bytes);
    bool flag = DataBase::getInstance().signup(info.username, info.password);
    socket->write(DataFormat::serialize(DataFormat::SignupServer{flag}));

    qDebug() << "Client::signup";
    qDebug() << "username:" << info.username << "password:" << info.password;
    qDebug() << "result:" << flag;
}
